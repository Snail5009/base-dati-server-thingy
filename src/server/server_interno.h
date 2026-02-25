#ifndef _CLIENTE_INTERNO_H
#define _CLIENTE_INTERNO_H

struct Richiesta
{
    int desc;
    char *buffer; // 'vuoto' quando e' NULL, e liberato dopo aver ricevuto eseguito l'richiesta
    size_t lunghezza_buffer;
    size_t capacita_buffer;
    uint32_t lunghezza_richiesta;
};

struct Server
{
    Richiesta *richieste_parziali; // tabella a hash, la chiave e' il desc
    int capacita_richieste;
    int numero_richieste; // per il ridimensionamento quando raggiunge tipo capacita / 2
};

Richiesta *_cliente_nuovo(int desc);
void _cliente_elimina(Richiesta *richiesta);
void _cliente_imposta_lunghezza_richiesta(Richiesta *richiesta, uint32_t lunghezza_richiesta);
void _cliente_nuovi_dati(Richiesta *richiesta, char *dati, int lunghezza_dati);

void _server_nuovo_cliente(Server *server, int desc); // aggiunge un nuovo cliente alla tabella a hash.

#endif
