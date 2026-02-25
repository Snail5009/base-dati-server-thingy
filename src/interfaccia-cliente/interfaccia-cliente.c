#include <unistd.h>
#include <sys/socket.h>
#include <linux/in.h>
#include <endian.h>
#include <stdlib.h>
#include <stdio.h>

#include <rete/rete.h>

int main(void)
{
    int server;

    server = crea_socket();
    connetti_a_server(server,
        INDIRIZZO_IPV4(127, 0, 0, 1),
        PORT_TCP(12345)
    );
    send(server, "ciaooo", 5, 0);
    close(server);

    return 0;
}
