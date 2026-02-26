#include <tipi/hashmap.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef struct HMQ_Entry HMQ_Entry;

struct HMQ_Entry
{
    uint64_t chiave;
    uint64_t valore;
    int esiste;
};

struct HMQ
{
    HMQ_Entry *dati;
    uint64_t capacita;
    uint64_t nvoci;
};

static void _hmq_ridimensiona(HMQ *hm, uint64_t capacita_prec)
{
    int i;
    uint64_t nuovi_indice;
    HMQ_Entry *dati_nuovi;
    dati_nuovi = malloc(hm->capacita * sizeof *dati_nuovi);
    if (!dati_nuovi)
    {
        fprintf(stderr, "error di allocazione\n");
        exit(1);
    }

    for (i = 0; i < capacita_prec; i++)
    {
        nuovo_indice = hm->dati[i].chiave % hm->capacita;
        if (hm->dati[i].esiste)
        {
            dati_nuovi[nuovo_indice] = hm->dati[i];
        }
        else
        {
            dati_nuovi[nuovo_indice].esiste = 0;
        }
    }

    free(hm->dati);
    hm->dati = dati_nuovi;
}

static void _hmq_controlla_dimensioni(HMQ *hm)
{
    int capacita_prec;
    if (hm->nvoci >= hm->capacita / 2)
    {
        capacita_prec = hm->capacita
        hm->capacita *= 2;
        _hmq_ridimensiona(hm, capacita_prec);
    }
}


HMQ *hmq_nuova(uint64_t capacita_iniziale)
{
    HMQ *hm;
    hm = malloc(sizeof *hm);
    hm->nvoci = 0;
    hm->capacita = capacita_iniziale;
    hm->dati = malloc(hm->capacita * sizeof *hm->dati);
    if (!hm->dati)
    {
        fprintf(stderr, "error di allocazione\n");
        exit(1);
    }
    return hm;
}

void hmq_chiudi(HMQ *hm)
{
    assert(hm != NULL);
    free(hm->dati);
    free(hm);
}

void hmq_inserisci(HMQ *hm, uint32_t chiave, uint64_t dati)
{
    HMQ_Entry *voce = &hm->dati[chiave % hm->capacita];
    voce->esiste = 1;
    voce->
}
void hmq_rimuovi(HMQ *hm, uint64_t chiave)
{

}
uint64_t hmq_estrai_valore(HMQ *hm, uint64_t chiave)
{

}
