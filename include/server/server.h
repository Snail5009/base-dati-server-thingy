#ifndef _SERVER_H
#define _SERVER_H

typedef struct Server Server;

Server server_inizializza(int indirizzo, int port);
void server_chiudi(Server *server);

void server_inizia(Server *server);

#endif
