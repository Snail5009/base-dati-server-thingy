#ifndef _PROTOCOLLO_H
#define _PROTOCOLLO_H

#include <stdlib.h>
#include <stdint.h>

#define PING 0x12345678
#define PONG 0x87654321

#define CMD_CHIEDI_PROP_BOOL 0x00000001

typedef enum PropServerBool PropServerBool;
enum PropServerBool
{
    PROP_SERVER_BOOL_PASSWORD_RICHIESTA = 1,
};

void invia_messaggio(int desc, uint32_t lunghezza, uint32_t commando, uint8_t *parametri);

#endif
