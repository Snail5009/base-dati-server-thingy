#include <rete/protocollo.h>
#include <endian.h>
#include <unistd.h>
#include <stdio.h>

void invia_messaggio(int desc, uint32_t lunghezza, uint32_t commando, uint8_t *parametri)
{
    uint32_t lunghezza_be, commando_be;
    lunghezza_be = htobe32(lunghezza);
    commando_be = htobe32(commando);

    if (write(desc, (char *)&lunghezza_be, sizeof lunghezza_be) < 0)
    {
        perror("write");
        exit(1);
    }

    sleep(1); // simula una lunga pausa tra scritture

    if (write(desc, (char *)&commando_be, sizeof commando_be) < 0)
    {
        perror("write");
        exit(1);
    }
    if (lunghezza > 0)
    {
        if (write(desc, parametri, lunghezza) < 0)
        {
            perror("write");
            exit(1);
        }
    }
}
