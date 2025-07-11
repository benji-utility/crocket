#ifndef __CROCKET_H
#define __CROCKET_H

#include "platform.h"

#if defined(CROCKET_WINDOWS)
    #pragma comment(lib, "ws2_32.lib")

    #ifndef WIN32_LEAN_AND_MEAN
        #define WIN32_LEAN_AND_MEAN
    #endif

    #include <winsock2.h>
    #include <ws2tcpip.h>

    #ifndef CROCKET_SOCKET_ERROR
        #define CROCKET_SOCKET_ERROR SOCKET_ERROR
    #endif

    #ifndef CROCKET_INVALID_SOCKET
        #define CROCKET_INVALID_SOCKET INVALID_SOCKET
    #endif

    typedef SOCKET CROCKET_SOCKET;
#elif defined(CROCKET_LINUX)
    #ifndef CROCKET_SOCKET_ERROR
        #define CROCKET_SOCKET_ERROR (-1)
    #endif

    #ifndef CROCKET_INVALID_SOCKET
        #define CROCKET_INVALID_SOCKET (unsigned long long)(~0)
    #endif

    typedef unsigned long long CROCKET_SOCKET;
#endif

typedef CROCKET_SOCKET socket_t;

#endif