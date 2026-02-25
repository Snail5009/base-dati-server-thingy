#include <rete/rete.h>

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include <sys/socket.h>
#include <sys/epoll.h>
#include <sys/fcntl.h>
#include <sys/errno.h>
#include <linux/in.h>
#include <unistd.h>
#include <errno.h>


/* UTILITÀ CHE NON VANNO LINKATI O INCLUSI */
static void _nonbloccare(int socket)
{
    if (fcntl(socket, F_SETFL, fcntl(socket, F_GETFL, 0) | O_NONBLOCK) < 0)
    {
        perror("fcntl");
        exit(1);
    }
}



int crea_socket(void)
{
    int desc;

    desc = socket(AF_INET, SOCK_STREAM, 0);
    if (desc < 0)
    {
        perror("socket");
        exit(1);
    }
    return desc;
}

void connetti_a_server(int desc, uint32_t indirizzo_ipv4, uint16_t port)
{
    struct sockaddr_in indirizzo;
    int risultato;

    indirizzo.sin_family = AF_INET;
    indirizzo.sin_port = port;
    indirizzo.sin_addr.s_addr = indirizzo_ipv4;

    risultato = connect(desc,
        (const struct sockaddr *)&indirizzo,
        (socklen_t)sizeof indirizzo
    );

    if (risultato < 0)
    {
        perror("connect");
        close(desc);
        exit(1);
    }
}

void assegna_indirizzo_a_server(int desc, uint32_t indirizzo_ipv4, uint16_t port)
{
    struct sockaddr_in indirizzo;
    int risultato;

    indirizzo.sin_family = AF_INET;
    indirizzo.sin_port = port;
    indirizzo.sin_addr.s_addr = indirizzo_ipv4;

    risultato = bind(desc,
        (const struct sockaddr *)&indirizzo,
        (socklen_t)sizeof indirizzo
    );

    if (risultato < 0)
    {
        perror("connect");
        close(desc);
        exit(1);
    }
}

void epoll_nuovo_desc(int edesc, int desc, int eventi)
{
    struct epoll_event ev;

    ev.events = eventi;
    ev.data.fd = desc;
    epoll_ctl(edesc, EPOLL_CTL_ADD, desc, &ev);
}

void epoll_elimina_desc(int edesc, int desc)
{
    epoll_ctl(edesc, EPOLL_CTL_DEL, desc, NULL);
    close(desc);
}

int server_accetti_cliente(int server)
{
    int cliente;
    struct sockaddr_in indirizzo;
    int lung_indirizzo = sizeof indirizzo;

    cliente = accept(
        server,
        (struct sockaddr *)&indirizzo,
        (socklen_t *)&lung_indirizzo
    );
    if (cliente < 0)
    {
        perror("accept");
        exit(1);
    }
    _nonbloccare(cliente);

    return cliente;
}


void server_accetti_cliente_e_configura(int epoll, int server, int mostra_log)
{
    int cliente;
    cliente = server_accetti_cliente(server);
    epoll_nuovo_desc(epoll, cliente, EPOLLIN | EPOLLRDHUP);
    if (mostra_log)
    {
        fprintf(stderr, "cliente connesso (%d)\n", cliente);
    }
}

int server_recv(int cliente, uint8_t *buffer, int lunghezza)
{
    int lunghezza_reale;
    
    lunghezza_reale = read(cliente, buffer, lunghezza);
    if (lunghezza_reale < 0)
    {
        perror("read");
        exit(1);
    }
    buffer[lunghezza_reale] = 0;
    return lunghezza_reale;
}

void server_ascolta(int server, int nconn)
{
    if (listen(server, 10) < 0)
    {
        perror("listen");
        exit(1);
    }
}

int server_epoll_aspetta(int server, struct epoll_event *eventi, int neventi)
{
    int ndesc;
    ndesc = epoll_wait(server, eventi, neventi, -1);
    if (ndesc < 0)
    {
        perror("epoll_wait");
        exit(1);
    }
    return ndesc;
}

int epoll_crea(void)
{
    int epoll;

    epoll = epoll_create1(0);
    if (epoll < 0)
    {
        perror("epoll_create1");
        exit(1);
    }

    return epoll;
}
