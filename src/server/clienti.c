#include "clienti.h"
#include <stdlib.h>

Richiesta crea_richiesta(uint32_t lunghezza_desiderata)
{
    Richiesta r;
    r.lunghezza_desiderata = lunghezza_desiderata;
    r.lunghezza_buffer = 0;
    r.buffer = malloc(r.lunghezza_desiderata);
    return r;
}

void libera_richiesta(Richiesta *r)
{
    free(r->buffer);
    r->buffer = NULL;
    r->lunghezza_buffer = 0;
    r->lunghezza_desiderata = 0;
}

int richiesta_vuota(Richiesta *r)
{
    return r->buffer == NULL;
}
