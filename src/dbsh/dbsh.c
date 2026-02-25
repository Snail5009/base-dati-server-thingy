#include <unistd.h>
#include <sys/socket.h>
#include <linux/in.h>
#include <endian.h>
#include <stdlib.h>
#include <stdio.h>

#include <cliente/cliente.h>

int main(void)
{
    int pass;
    Cliente *cliente;
    cliente = cliente_connetti(INDIRIZZO_LOCALHOST, PORT_TCP(12345));
    pass = cliente_chiedi_prop_bool(cliente, PROP_SERVER_BOOL_PASSWORD_RICHIESTA);
    printf("%s\n", pass ? "password richiesta" : "password non richiesta");
    cliente_chiudi(cliente);
    return 0;
}
