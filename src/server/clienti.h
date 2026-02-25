#ifndef _CLIENTI_H
#define _CLIENTI_H

#include <stdint.h>

typedef struct Richiesta Richiesta;
struct Richiesta
{
    uint8_t *buffer;
    uint64_t lunghezza_buffer;
    uint32_t lunghezza_desiderata;
};

Richiesta crea_richiesta(uint32_t lunghezza_desiderata);
void libera_richiesta(Richiesta *r);
int richiesta_vuota(Richiesta *r);

#endif
