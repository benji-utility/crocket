#ifndef __CROCKET_BASE_H
#define __CROCKET_BASE_H

#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include "platform.h"

#if defined(CROCKET_WINDOWS)
    #pragma comment(lib, "ws2_32.lib")

    #ifndef WIN32_LEAN_AND_MEAN
        #define WIN32_LEAN_AND_MEAN
    #endif

    #include <winsock2.h>

    #ifndef CROCKET_API
        #define CROCKET_API WSAAPI
    #endif

    typedef SOCKET socket_handle_t;
#elif defined(CROCKET_LINUX)
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #include <errno.h>

    #ifndef CROCKET_API
        #define CROCKET_API
    #endif

    typedef int socket_handle_t;
#endif

#ifndef CROCKET_SUCCESS
    #define CROCKET_SUCCESS (0)
#endif

#endif
