#ifndef __CROCKET_BASE_H
#define __CROCKET_BASE_H

#include <stdint.h>
#include <stdbool.h>

#include "platform.h"

#if defined(CROCKET_WINDOWS)
    #ifndef WIN32_LEAN_AND_MEAN
        #define WIN32_LEAN_AND_MEAN
    #endif

    #include <winsock2.h>

    #ifndef CROCKET_API
        #define CROCKET_API WINAPI
    #endif

    typedef SOCKET socket_t;
#endif

#endif