#ifndef __CROCKET_SOCKET_H
#define __CROCKET_SOCKET_H

#include "crocket_base.h"

typedef struct _CROCKET_SOCKET_ADDRESS {
    const char* ip;
    uint16_t port;
} socket_address_t;

typedef struct _CROCKET_SOCKET {
    socket_t self;
    socket_address_t address;
} crocket_socket_t;

#endif