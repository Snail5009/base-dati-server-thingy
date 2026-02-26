#ifndef _CLIENTE_H
#define _CLIENTE_H
#include <rete/rete.h>
#include <rete/protocollo.h>

typedef struct Cliente Cliente;

Cliente *cliente_connetti(int indirizzo, int port);
void cliente_chiudi(Cliente *cliente);
int cliente_invia(Cliente *cliente, const uint8_t *messaggio, uint32_t len);

int cliente_chiedi_prop_bool(Cliente *cliente, PropServerBool proprieta);

#endif
