#include <unistd.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <sys/fcntl.h>
#include <sys/errno.h>
#include <linux/in.h>
#include <endian.h>
#include <stdlib.h>
#include <stdio.h>

#include <rete/rete.h>

#define NUM_MASS_DI_EVENTI (10)

void setnonblocking(int socket)
{
    if (fcntl(socket, F_SETFL, fcntl(socket, F_GETFL, 0) | O_NONBLOCK) < 0)
    {
        perror("fcntl");
        exit(1);
    }
}

int main(void)
{
    int descrittore_server, descrittore_cliente, descrittore_epoll;
    int fd; //tmp
    int lunghezza;
    int eventi_bitfield;
    int ndescrittori, i;
    struct sockaddr_in indirizzo_server, indirizzo_cliente;
    struct epoll_event ev, eventi[NUM_MASS_DI_EVENTI];
    socklen_t indirizzo_cliente_len;
    char buffer_dati[512];

    indirizzo_server.sin_family = AF_INET;
    indirizzo_server.sin_port = PORT_TCP(12345);
    indirizzo_server.sin_addr.s_addr = INDIRIZZO_IPV4(127, 0, 0, 1);


    descrittore_epoll = epoll_create1(0);
    if (descrittore_epoll < 0)
    {
        perror("epoll_create1");
        exit(1);
    }

    descrittore_server = socket(AF_INET, SOCK_STREAM, 0);

    if (descrittore_server < 0)
    {
        perror("socket");
        exit(1);
    }

    if (bind (descrittore_server,
                (const struct sockaddr *)&indirizzo_server,
                (socklen_t)sizeof indirizzo_server
                ) < 0)
    {
        perror("bind");
        close(descrittore_epoll);
        close(descrittore_server);
        exit(1);
    }

    if (listen(descrittore_server, 10) < 0)
    {
        perror("listen");
        exit(1);
    }

    
    ev.events = EPOLLIN;
    ev.data.fd = descrittore_server;
    epoll_ctl(descrittore_epoll, EPOLL_CTL_ADD, descrittore_server, &ev);


    int finito = 0;
    while (!finito)
    {
        ndescrittori = epoll_wait(descrittore_epoll, eventi, NUM_MASS_DI_EVENTI, -1);
        if (ndescrittori < 0)
        {
            perror("epoll_wait");
            exit(1);
        }


        for (i = 0; i < ndescrittori; i++)
        {
            // printf("elaborando l'evento %d\n", i);
            fd = eventi[i].data.fd;
            eventi_bitfield = eventi[i].events;

            if (fd == descrittore_server)
            {
                indirizzo_cliente_len = (socklen_t)sizeof(struct sockaddr_in);
                descrittore_cliente = accept(
                    descrittore_server,
                    (struct sockaddr *)&indirizzo_cliente,
                    &indirizzo_cliente_len
                );
                if (descrittore_cliente < 0)
                {
                    perror("accept");
                    close(descrittore_server);
                    close(descrittore_epoll);
                    exit(1);
                }
                setnonblocking(descrittore_cliente);
                ev.data.fd = descrittore_cliente;
                ev.events = EPOLLIN | EPOLLRDHUP;
                epoll_ctl(descrittore_epoll, EPOLL_CTL_ADD, descrittore_cliente, &ev);
                fprintf(stderr, "cliente connesso (%d)\n", descrittore_cliente);
            }
            else
            {
                if (!(eventi_bitfield & EPOLLHUP))
                {
                    lunghezza = read(fd, buffer_dati, 511);
                    if (lunghezza < 0)
                    {
                        perror("read");
                        exit(1);
                    }
                    buffer_dati[lunghezza] = 0;
                    printf("%s\n", buffer_dati);
                }

                if (eventi_bitfield & EPOLLRDHUP)
                {
                    printf("cliente disconnesso (%d)\n", fd);
                    epoll_ctl(descrittore_epoll, EPOLL_CTL_DEL, fd, NULL);
                    close(fd);
                }
            }
        }
    }
    
    close(descrittore_server);
    close(descrittore_epoll);

    return 0;
}
