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
#include <tipi/hashmap.h>

#define NUM_DI_EVENTI (10)

typedef struct
{
    int desc;
    int epoll;

    struct epoll_event eventi[NUM_DI_EVENTI];
    char buffer[512];
} Server;

static void _server_interpreta_blocco(const uint8_t *buffer, int lunghezza, int fd)
{
    if (lunghezza == 0) return;
    int lunghezza_desiderata;
    lunghezza_desiderata = be32toh(*(uint32_t *)buffer);
    if (lunghezza_desiderata + 4 != lunghezza)
    {
        printf("noooo (%d)\n", lunghezza);
    }
    else
    {
        printf("yayyyyy (%d)\n", lunghezza);
    }
}

static void _server_leggi_blocco(Server *s, int fd)
{
    int byte_letti;
    byte_letti = read(fd, s->buffer, 511);
    if (byte_letti < 0)
    {
        perror("read");
        exit(1);
    }
    s->buffer[byte_letti] = 0;
    _server_interpreta_blocco(s->buffer, byte_letti, fd);
}

static void _server_elabora_notifica(Server *s, int fd, uint32_t eventi)
{
    if (eventi & EPOLLIN)
    {
        _server_leggi_blocco(s, fd);
    }

    if (eventi & EPOLLRDHUP)
    {
        printf("cliente disconnesso (%d)\n", fd);
        epoll_elimina_desc(s->epoll, fd);
    }
}

int main(void)
{
    int ndesc, i;
    struct epoll_event ev;
    Server s;

    HMQ *hm;
    hm = hmq_nuova(8);
    hmq_inserisci(hm, 1234, 1289347);
    assert(hmq_estrai_valore(hm, 1234) == 1289347);
    hmq_rimuovi(hm, 1234);
    assert(hmq_estrai_valore(hm, 1234) == -1);
    hmq_chiudi(hm);

    return 0;

    s.epoll = epoll_crea();
    
    s.desc = crea_socket();
    assegna_indirizzo_a_server(s.desc,
        INDIRIZZO_IPV4(127, 0, 0, 1),
        PORT_TCP(12345)
    );

    server_ascolta(s.desc, 10);
    epoll_nuovo_desc(s.epoll, s.desc, EPOLLIN);

    int finito = 0;
    while (!finito)
    {
        ndesc = server_epoll_aspetta(s.epoll, s.eventi, NUM_DI_EVENTI);
        for (i = 0; i < ndesc; i++)
        {
            if (s.eventi[i].data.fd == s.desc)
            {
                server_accetti_cliente_e_configura(s.epoll, s.desc, 1);
            }
            else
            {
                _server_elabora_notifica(&s, s.eventi[i].data.fd, s.eventi[i].events);
            }
        }
    }
    
    close(s.desc);
    close(s.epoll);
    return 0;
}
