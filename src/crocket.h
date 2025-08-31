#ifndef __CROCKET_H
#define __CROCKET_H

#include "socket.h"

#if defined(CROCKET_WINDOWS)
    CROCKET_API bool winsock_init();
    CROCKET_API bool winsock_cleanup();
#endif

#endif