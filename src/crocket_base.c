#include "crocket_base.h"

CROCKET_API bool crocket_init() {
    bool result = false;

    #ifdef CROCKET_WINDOWS
        result |= winsock_init();
    #endif

    result |= crocket_error_context_init();

    return result;
}

#if defined(CROCKET_WINDOWS)
    static bool _crocket_is_winsock_initialized = false;

    CROCKET_API bool winsock_init() {
        if (_crocket_is_winsock_initialized) return true;

        struct WSAData wsa_data;

        if (WSAStartup(WINSOCK_VERSION, &wsa_data) != CROCKET_SUCCESS) {
            // todo: collect error info

            return false;
        }

        _crocket_is_winsock_initialized = true;

        return true;
    }

    CROCKET_API bool winsock_cleanup() {
        if (!_crocket_is_winsock_initialized) {
            // todo: collect error info

            return false;
        }

        if (WSACleanup() != CROCKET_SUCCESS) {
            // todo: collect error info

            return false;
        }

        return true;
    }
#endif
