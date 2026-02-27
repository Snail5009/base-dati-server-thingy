#ifndef _HASHMAP_H
#define _HASHMAP_H
#include <stdint.h>

// = HashMap qword
typedef struct HMQ HMQ;

HMQ *hmq_nuova(uint64_t capacita_iniziale);
void hmq_chiudi(HMQ *hm);

void hmq_inserisci(HMQ *hm, uint32_t chiave, uint64_t dati);
void hmq_rimuovi(HMQ *hm, uint64_t chiave);
uint64_t hmq_estrai_valore(HMQ *hm, uint64_t chiave);

#endif
