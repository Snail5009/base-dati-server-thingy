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

#define NUM_DI_EVENTI (10)

typedef struct
{
    int desc;
    int epoll;

    struct epoll_event eventi[NUM_DI_EVENTI];
} Server;

static void _server_elabora_notifica(Server *s, int fd, uint32_t eventi)
{
    if (eventi & EPOLLIN)
    {
        read(s->desc, j);
    }

    if (eventi & EPOLLRDHUP)
    {
        printf("cliente disconnesso (%d)\n", s->eventi[i].data.fd);
        epoll_elimina_desc(s->epoll, s->eventi[i].data.fd);
    }
}

int main(void)
{
    int ndesc, i;
    struct epoll_event ev;
    Server s;

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
        ndesc = server_epoll_aspetta(s.desc, s.eventi, NUM_DI_EVENTI);
        for (i = 0; i < ndesc; i++)
        {
            if (s.eventi[i].data.fd == s.desc)
            {
                server_accetti_cliente_e_configura(s.epoll, s.desc, 1);
            }
            else
            {
                _server_elabora_notifica()
            }
        }
    }
    
    close(s.desc);
    close(s.epoll);
    return 0;
}
