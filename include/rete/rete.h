#ifndef _RETE_H
#define _RETE_H
#include <endian.h>
#include <stdint.h>

#define INDIRIZZO_IPV4(x3, x2, x1, x0) \
    htobe32(((x3) << 24) | ((x2) << 16) | ((x1) << 8) | (x0))

#define PORT_TCP(x) htobe16(x)

int crea_socket(void);
void connetti_a_server(int desc, uint32_t indirizzo, uint16_t port);

#endif
