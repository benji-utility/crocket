#ifndef __CROCKET_SOCKET_H
#define __CROCKET_SOCKET_H

#include <stdint.h>

#include "crocket_base.h"

#ifndef CROCKET_SOCKET_PORT_PLACEHOLDER_VALUE
    #define CROCKET_SOCKET_PORT_PLACEHOLDER_VALUE (UINT16_MAX)
#endif

#ifndef CROCKET_SOCKET_EPHEMERAL_PORT
    #define CROCKET_SOCKET_EPHEMERAL_PORT (0)
#endif

typedef struct _CROCKET_SOCKET {
    SOCKET self;
    uint16_t port;
} crocket_socket_t;

CROCKET_API bool crocket_socket_init(crocket_socket_t* sock);

CROCKET_API bool crocket_socket_bind_any(crocket_socket_t* sock);
CROCKET_API bool crocket_socket_bind_to(crocket_socket_t* sock, const char* address, const uint16_t port);

CROCKET_API bool crocket_socket_close(crocket_socket_t* sock);

#endif