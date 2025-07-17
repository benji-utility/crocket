#include "crocket_base.h"

#ifdef CROCKET_WINDOWS
    CROCKET_API bool crocket_winsock_init() {
        struct WSAData wsa_data;

        if (WSAStartup(WINSOCK_VERSION, &wsa_data) != CROCKET_ERROR_NONE) {
            _crocket_update_error_context(
                WSAGetLastError(),
                "WSAStartup() failed"
            );

            return false;
        }

        return true;
    }

    CROCKET_API bool crocket_winsock_cleanup() {
        if (WSACleanup() != CROCKET_ERROR_NONE) {
            int error_code = WSAGetLastError();

            if (error_code == WSANOTINITIALISED) {
                _crocket_update_error_context(
                    CROCKET_ERROR_WINSOCK_NOT_INITIALIZED,
                    "Operation not permitted, Winsock not initialized"
                );
            }
            else {
                _crocket_update_error_context(
                    error_code,
                    "Failed to cleanup Winsock"
                );
            }

            return false;
        }

        return true;
    }
#endif