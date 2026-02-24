#include <unistd.h>
#include <sys/socket.h>
#include <linux/in.h>
#include <endian.h>
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    int descrittore_server;
    struct sockaddr_in indirizzo_server;

    indirizzo_server.sin_family = AF_INET;
    indirizzo_server.sin_port = htobe16(12345);
    indirizzo_server.sin_addr.s_addr = htobe32((127 << 24) | 1);

    descrittore_server = socket(AF_INET, SOCK_STREAM, 0);

    if (descrittore_server < 0)
    {
        perror("socket");
        exit(1);

    }

    if (connect (descrittore_server,
                (const struct sockaddr *)&indirizzo_server,
                (socklen_t)sizeof indirizzo_server
                ) < 0)
    {
        perror("connect");
        close(descrittore_server);
        exit(1);
    }

    send(descrittore_server, "ciaooo", 5, 0);


    close(descrittore_server);

    return 0;
}
