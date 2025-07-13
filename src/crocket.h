#ifndef __CROCKET_H
#define __CROCKET_H

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

    typedef SOCKET CROCKET_SOCKET;
#elif defined(CROCKET_LINUX)
    #ifndef CROCKET_API
        #define CROCKET_API
    #endif

    #ifndef CROCKET_SOCKET_ERROR
        #define CROCKET_SOCKET_ERROR (-1)
    #endif

    #ifndef CROCKET_INVALID_SOCKET
        #define CROCKET_INVALID_SOCKET (unsigned long long)(~0)
    #endif

    typedef unsigned long long CROCKET_SOCKET;
#endif

typedef CROCKET_SOCKET socket_t;

#ifdef _WIN32
    CROCKET_API static inline bool winsock_init() {
        struct WSAData wsa_data;

        if (WSAStartup(WINSOCK_VERSION, &wsa_data) != CROCKET_ERROR_NONE) {
            _update_error_context(GetLastError(), "WSAStartup() failed");

            return false;
        }

        return true;
    }

    CROCKET_API static inline bool winsock_cleanup() {
        if (WSACleanup() != CROCKET_ERROR_NONE) {
            _update_error_context(GetLastError(), "WSACleanup() failed");

            return false;
        }

        return true;
    }
#endif

#endif