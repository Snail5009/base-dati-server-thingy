#include <rete/protocollo.h>
#include <endian.h>
#include <unistd.h>

void invia_messaggio(int desc, uint32_t lunghezza, uint32_t commando, uint8_t *parametri)
{
    lunghezza = htobe32(lunghezza);
    commando = htobe32(commando);

    write(desc, (char *)&lunghezza, sizeof lunghezza);
    for (int i = 0; i < 10000; i++) {
        printf("%d\n", i);
    }
    write(desc, (char *)&commando, sizeof commando);
    if (lunghezza > 0)
    {
        write(desc, parametri, lunghezza);
    }
}
