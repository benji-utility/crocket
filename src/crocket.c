#include "crocket.h"

#ifdef CROCKET_WINDOWS
    CROCKET_API bool winsock_init() {
        struct WSAData wsa_data;

        if (WSAStartup(WINSOCK_VERSION, &wsa_data) != CROCKET_ERROR_NONE) {
            _update_error_context(
                WSAGetLastError(),
                "WSAStartup() failed"
            );

            return false;
        }

        _crocket_is_winsock_initialized = true;

        return true;
    }

    CROCKET_API bool winsock_cleanup() {
        if (!_crocket_is_winsock_initialized) {
            _update_error_context(
                CROCKET_ERROR_WINSOCK_NOT_INITIALIZED,
                "Winsock not initialized"
            );

            return false;
        }

        if (WSACleanup() != CROCKET_ERROR_NONE) {
            _update_error_context(
                WSAGetLastError(),
                "WSACleanup() failed"
            );

            return false;
        }

        _crocket_is_winsock_initialized = false;

        return true;
    }
#endif

CROCKET_API bool crocket_socket_init(crocket_socket_t* sock) {
    #ifdef CROCKET_WINDOWS
        if (!_crocket_is_winsock_initialized) {
            _update_error_context(
                CROCKET_ERROR_WINSOCK_NOT_INITIALIZED,
                "Operation not permitted, Winsock not initialized"
            );

            return false;
        }
    #endif

    sock->self = socket(AF_INET, SOCK_STREAM, 0);

    if (sock->self == CROCKET_INVALID_SOCKET) {
        #if defined(CROCKET_WINDOWS)
            _update_error_context(
                WSAGetLastError(),
                "Failed to create socket"
            );
        #elif defined(CROCKET_LINUX)
            _update_error_context(errno, strerror(errno));
        #endif

        return false;
    }

    // set to placeholder value till true assignment during binding
    sock->port = CROCKET_SOCKET_PLACEHOLDER_VALUE;

    return true;
}

CROCKET_API bool crocket_socket_close(crocket_socket_t* sock) {
    #ifdef CROCKET_WINDOWS
        if (!_crocket_is_winsock_initialized) {
            _update_error_context(
                CROCKET_ERROR_WINSOCK_NOT_INITIALIZED,
                "Operation not permitted, Winsock not initialized"
            );

            return false;
        }
    #endif

    #if defined(CROCKET_WINDOWS)
        int return_code = closesocket(sock->self);
    #elif defined(CROCKET_LINUX)
        int return_code = close(sock->self);
    #endif

    if (return_code == SOCKET_ERROR) {
        #if defined(CROCKET_WINDOWS)
            _update_error_context(
                WSAGetLastError(),
                "Failed to close socket"
            );
        #elif defined(CROCKET_LINUX)
            _update_error_context(errno, strerror(errno));
        #endif

        return false;
    }

    return true;
}