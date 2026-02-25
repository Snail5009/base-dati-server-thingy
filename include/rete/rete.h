#ifndef _RETE_H
#define _RETE_H
#include <endian.h>
#include <stdint.h>

#define INDIRIZZO_IPV4(x3, x2, x1, x0) \
    htobe32(((x3) << 24) | ((x2) << 16) | ((x1) << 8) | (x0))

#define PORT_TCP(x) htobe16(x)

int crea_socket(void);
void connetti_a_server(int desc, uint32_t indirizzo, uint16_t port);
void assegna_indirizzo_a_server(int desc, uint32_t indirizzo_ipv4, uint16_t port);
void epoll_nuovo_desc(int edesc, int desc, int eventi);
void epoll_elimina_desc(int edesc, int desc); // anche chiude il desc
int server_accetti_cliente(int server);
void server_accetti_cliente_e_configura(int epoll, int server, int mostra_log);
void server_recv(int cliente, char *buffer, int lunghezza_buffer);

#endif
