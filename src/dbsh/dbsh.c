#include <unistd.h>
#include <sys/socket.h>
#include <linux/in.h>
#include <endian.h>
#include <stdlib.h>
#include <stdio.h>

#include <cliente/cliente.h>

void messaggio(Cliente *cliente)
{
    int lunghezza_messaggio = htobe32(4);
    cliente_invia(cliente, (const uint8_t *)&lunghezza_messaggio, 4);
    sleep(1);
    cliente_invia(cliente, "ciao", 4);
}

int main(void)
{
    Cliente *cliente;
    cliente = cliente_connetti(INDIRIZZO_LOCALHOST, PORT_TCP(12345));
    
    messaggio(cliente);
    
    cliente_chiudi(cliente);
    return 0;
}
