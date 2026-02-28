#include <tipi/hashmap.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

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
    uint64_t nuovo_indice;
    HMQ_Entry *dati_nuovi;
    dati_nuovi = calloc(hm->capacita, sizeof *dati_nuovi);
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
            while (dati_nuovi[nuovo_indice].esiste)
            {
                nuovo_indice++;
            }
            dati_nuovi[nuovo_indice] = hm->dati[i];
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
        capacita_prec = hm->capacita;
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
    hm->dati = calloc(hm->capacita, sizeof *hm->dati);
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
    int indice;
    HMQ_Entry *voce;
    
    if (hmq_estrai_valore(hm, chiave) != -1)
    {
        fprintf(stderr, "chiave %d esiste già\n", chiave);
        exit(1);
    }

    hm->nvoci++;
    _hmq_controlla_dimensioni(hm);

    indice = chiave % hm->capacita;
    voce = &hm->dati[indice];
    
    
    
    while (voce->esiste)
    {
        indice++;
        indice %= hm->capacita;
        voce = &hm->dati[indice];
    }
    
    voce->esiste = 1;
    voce->valore = dati;
    voce->chiave = chiave;
}

int hmq_rimuovi(HMQ *hm, uint64_t chiave)
{
    int indice, indice_prec;
    HMQ_Entry *voce;
    
    indice = chiave % hm->capacita;
    voce = &hm->dati[indice];

    while (voce->esiste && voce->chiave != chiave)
    {
        indice_prec = indice;
        indice++;
        indice %= hm->capacita;
        voce = &hm->dati[indice];
        memcpy(&hm->dati[indice_prec], voce, sizeof(*voce));
    }

    voce->esiste = 0;

    return 0;
}
uint64_t hmq_estrai_valore(HMQ *hm, uint64_t chiave)
{
    int indice;
    HMQ_Entry *voce;

    indice = chiave % hm->capacita;
    voce = &hm->dati[indice];

    while (voce->esiste && voce->chiave != chiave)
    {
        indice++;
        indice %= hm->capacita;
        voce = &hm->dati[indice];
    }

    if (voce->chiave != chiave || voce->esiste == 0) return -1;

    return voce->valore;
}
