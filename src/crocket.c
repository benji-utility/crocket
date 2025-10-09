#include "crocket.h"

#if defined(CROCKET_WINDOWS)
    static bool _crocket_is_winsock_initialized = false;

    CROCKET_API bool winsock_init() {
        if (_crocket_is_winsock_initialized) return true;

        struct WSAData wsa_data;

        if (!WSAStartup(WINSOCK_VERSION, &wsa_data)) {
            // todo: collect error info

            return false;
        }

        _crocket_is_winsock_initialized = true;

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
