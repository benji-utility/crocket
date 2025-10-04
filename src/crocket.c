#include "crocket.h"

#if defined(CROCKET_WINDOWS)
    CROCKET_API bool winsock_init() {
        struct WSAData wsa_data;

        if (!WSAStartup(WINSOCK_VERSION, &wsa_data)) {
            // todo: collect error info

            return false;
        }

        return true;
    }

    CROCKET_API bool winsock_cleanup() {
        if (!WSACleanup()) {
            // todo: collect error info

            return false;
        }

        return false;
    }
#endif
