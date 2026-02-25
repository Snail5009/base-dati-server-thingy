#include <unistd.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <sys/fcntl.h>
#include <sys/errno.h>
#include <linux/in.h>
#include <endian.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include <rete/rete.h>
#include "clienti.h"

#define NUM_MASS_DI_EVENTI (10)

int main(void)
{
    int descrittore_server, descrittore_cliente, descrittore_epoll;
    int fd; //tmp
    int lunghezza;
    int eventi_bitfield;
    int ndescrittori, i;
    struct sockaddr_in indirizzo_cliente;
    struct epoll_event ev, eventi[NUM_MASS_DI_EVENTI];
    socklen_t indirizzo_cliente_len;

    Richiesta richiesta;

    richiesta.buffer = NULL;


    descrittore_epoll = epoll_create1(0);
    if (descrittore_epoll < 0)
    {
        perror("epoll_create1");
        exit(1);
    }

    descrittore_server = crea_socket();
    assegna_indirizzo_a_server(descrittore_server,
        INDIRIZZO_IPV4(127, 0, 0, 1),
        PORT_TCP(12345)
    );

    if (listen(descrittore_server, 10) < 0)
    {
        perror("listen");
        exit(1);
    }
    
    epoll_nuovo_desc(descrittore_epoll, descrittore_server, EPOLLIN);

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
            fd = eventi[i].data.fd;
            eventi_bitfield = eventi[i].events;

            if (fd == descrittore_server)
            {
                server_accetti_cliente_e_configura(descrittore_epoll, descrittore_server, 1);
            }
            else
            {
                if (eventi_bitfield & EPOLLIN)
                {
                    printf("EPOLLIN\n");
                }

                if (eventi_bitfield & EPOLLRDHUP)
                {
                    printf("cliente disconnesso (%d)\n", fd);
                    epoll_elimina_desc(descrittore_epoll, fd);
                }
            }
        }
    }
    
    close(descrittore_server);
    close(descrittore_epoll);

    return 0;
}
