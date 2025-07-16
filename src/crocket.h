#ifndef __CROCKET_H
#define __CROCKET_H

#include <stdint.h>
#include <stdbool.h>

#include "platform.h"
#include "error.h"

#if defined(CROCKET_WINDOWS)
    #pragma comment(lib, "ws2_32.lib")

    #ifndef WIN32_LEAN_AND_MEAN
        #define WIN32_LEAN_AND_MEAN
    #endif

    #include <winsock2.h>
    #include <ws2tcpip.h>

    #ifndef CROCKET_API
        #define CROCKET_API WINAPI
    #endif

    #ifndef CROCKET_SOCKET_ERROR
        #define CROCKET_SOCKET_ERROR SOCKET_ERROR
    #endif

    #ifndef CROCKET_INVALID_SOCKET
        #define CROCKET_INVALID_SOCKET INVALID_SOCKET
    #endif
#elif defined(CROCKET_LINUX)
    #include <errno.h>

    #ifndef CROCKET_API
        #define CROCKET_API
    #endif

    // linux does not have a default socket type so we rollin' our own
    typedef unsigned long long SOCKET;

    #ifndef CROCKET_SOCKET_ERROR
        #define CROCKET_SOCKET_ERROR (-1)
    #endif

    #ifndef CROCKET_INVALID_SOCKET
        #define CROCKET_INVALID_SOCKET (CROCKET_SOCKET)(~0)
    #endif
#endif

#ifndef CROCKET_SOCKET_PLACEHOLDER_VALUE
    #define CROCKET_SOCKET_PLACEHOLDER_VALUE (UINT16_MAX)
#endif

typedef struct _CROCKET_SOCKET {
    SOCKET self;
    uint16_t port;
} crocket_socket_t;

static bool _crocket_is_winsock_initialized = false;

#ifdef CROCKET_WINDOWS
    CROCKET_API bool winsock_init();
    CROCKET_API bool winsock_cleanup();
#endif

CROCKET_API bool crocket_socket_init(crocket_socket_t* sock);

CROCKET_API bool crocket_socket_close(crocket_socket_t* sock);

#endif