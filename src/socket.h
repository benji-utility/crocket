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

#ifndef _CROCKET_INET_PTON_SUCCESS
    #define _CROCKET_INET_PTON_SUCCESS (1)
#endif

#ifndef _CROCKET_INET_PTON_INVALID_IP
    #define _CROCKET_INET_PTON_INVALID_IP (0)
#endif

#ifndef _CROCKET_INET_PTON_UNSUPPORTED_ADDRESS_FAMILY
    #define _CROCKET_INET_PTON_UNSUPPORTED_ADDRESS_FAMILY (-1)
#endif

#if defined(CROCKET_WINDOWS)
    #ifndef _CROCKET_SOCKADDR_IN_ADDRESS
        #define _CROCKET_SOCKADDR_IN_ADDRESS(_sockaddr_in) (_sockaddr_in.sin_addr.S_un.S_addr)
    #endif
#elif defined(CROCKET_LINUX)
    #ifndef _CROCKET_SOCKADDR_IN_ADDRESS
        #define _CROCKET_SOCKADDR_IN_ADDRESS(_sockaddr_in) (_sockaddr_in.sin_addr.s_addr)
    #endif
#endif

#ifndef CROCKET_IP_STRING_LENGTH
    #define CROCKET_IP_STRING_LENGTH INET_ADDRSTRLEN
#endif

#ifndef CROCKET_IP_ANY
    #define CROCKET_IP_ANY NULL
#endif

#ifndef CROCKET_PORT_ANY
    #define CROCKET_PORT_ANY (0) /* ephemeral port */
#endif

typedef struct _CROCKET_SOCKET {
    socket_handle_t handle;
    struct sockaddr_in address;
} socket_t;

CROCKET_API bool crocket_socket_init(socket_t* sock, int address_family, int type, int protocol);
CROCKET_API bool crocket_socket_close(socket_t* sock);

CROCKET_API bool crocket_socket_set_address(socket_t* sock, int address_family, const char* ip, unsigned short port);
CROCKET_API bool crocket_socket_set_address_any(socket_t* sock, int address_family);

CROCKET_API bool crocket_socket_bind(socket_t* sock); // bind to its internal address
CROCKET_API bool crocket_socket_listen(socket_t* sock, size_t backlog);
CROCKET_API bool crocket_socket_accept(socket_t* server_socket, socket_t* client_socket);
CROCKET_API bool crocket_socket_connect(socket_t* sock); // connect to internal address

CROCKET_API bool crocket_socket_send(socket_t* sock, void* data, size_t data_length, int flags);

CROCKET_API bool crocket_socket_get_ip(const socket_t sock, int address_family, char* buffer, size_t buffer_size);
CROCKET_API unsigned short crocket_socket_get_port(const socket_t sock);

#endif
