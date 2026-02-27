#include <cliente/cliente.h>
#include <unistd.h>

struct Cliente
{
    int desc;
};

Cliente *cliente_connetti(int indirizzo, int port)
{
    Cliente *cliente;

    cliente = malloc(sizeof *cliente);
    cliente->desc = crea_socket();

    connetti_a_server(cliente->desc, indirizzo, port);
    return cliente;
}

void cliente_chiudi(Cliente *cliente)
{
    close(cliente->desc);
}

int cliente_invia(Cliente *cliente, const uint8_t *messaggio, uint32_t len)
{
    write(cliente->desc, messaggio, len);
}

int cliente_chiedi_prop_bool(Cliente *cliente, PropServerBool proprieta)
{
    int32_t proprieta_be = htobe32(proprieta);
    invia_messaggio(cliente->desc, 4, CMD_CHIEDI_PROP_BOOL, (uint8_t *)&proprieta_be);
}
