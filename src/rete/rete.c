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
