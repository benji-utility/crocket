#ifndef __CROCKET_SOCKET_H
#define __CROCKET_SOCKET_H

#include "crocket_base.h"

#if defined(CROCKET_WINDOWS)
    #ifndef CROCKET_INVALID_SOCKET
        #define CROCKET_INVALID_SOCKET (INVALID_SOCKET)
    #endif
#elif defined(CROCKET_LINUX)
    #ifndef CROCKET_INVALID_SOCKET
        #define CROCKET_INVALID_SOCKET (-1)
    #endif
#endif

#ifndef CROCKET_INET_PTON_SUCCESS
    #define CROCKET_INET_PTON_SUCCESS (1)
#endif

#ifndef CROCKET_INET_PTON_INVALID_IP
    #define CROCKET_INET_PTON_INVALID_IP (0)
#endif

#ifndef CROCKET_INET_PTON_UNSUPPORTED_ADDRESS_FAMILY
    #define CROCKET_INET_PTON_UNSUPPORTED_ADDRESS_FAMILY (-1)
#endif

typedef struct _CROCKET_SOCKET {
    socket_handle_t handle;
    struct sockaddr_in address;
} socket_t;

CROCKET_API bool crocket_socket_init(socket_t* sock, int address_family, int type, int protocol);
CROCKET_API bool crocket_socket_close(socket_t* sock);

CROCKET_API bool crocket_socket_set_address(socket_t* sock, int address_family, const char* ip, unsigned short port);

CROCKET_API bool crocket_socket_bind(socket_t* sock); // bind to its internal address
CROCKET_API bool crocket_socket_listen(socket_t* sock, size_t backlog);
CROCKET_API bool crocket_socket_accept(socket_t* server_socket, socket_t* client_socket);

#endif
