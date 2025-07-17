#include "crocket.h"

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

        _crocket_is_winsock_initialized = true;

        return true;
    }

    CROCKET_API bool crocket_winsock_cleanup() {
        if (!_crocket_is_winsock_initialized) {
            _crocket_update_error_context(
                CROCKET_ERROR_WINSOCK_NOT_INITIALIZED,
                "Winsock not initialized"
            );

            return false;
        }

        if (WSACleanup() != CROCKET_ERROR_NONE) {
            _crocket_update_error_context(
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
        _check_winsock();
    #endif

    sock->self = socket(AF_INET, SOCK_STREAM, 0);

    if (sock->self == CROCKET_INVALID_SOCKET) {
        #if defined(CROCKET_WINDOWS)
            _crocket_update_error_context(
                WSAGetLastError(),
                "Failed to create socket"
            );
        #elif defined(CROCKET_LINUX)
            _crocket_update_error_context(errno, strerror(errno));
        #endif

        return false;
    }

    // set to placeholder value till true assignment during binding
    sock->port = CROCKET_SOCKET_PORT_PLACEHOLDER_VALUE;

    return true;
}

CROCKET_API bool crocket_socket_bind_any(crocket_socket_t* sock) {
    crocket_socket_bind_to(sock, NULL, CROCKET_SOCKET_EPHEMERAL_PORT);
}

CROCKET_API bool crocket_socket_bind_to(crocket_socket_t* sock, const char* address, const uint16_t port) {
    #if defined(CROCKET_WINDOWS)
        _check_winsock();
    #endif

    struct sockaddr_in socket_address;

    memset(&socket_address, 0, sizeof(socket_address));

    socket_address.sin_family = AF_INET;
    socket_address.sin_port = htons(port);

    _CROCKET_SOCKADDR_IN_ADDRESS(socket_address) = address ? inet_addr(address) : INADDR_ANY;

    if (bind(sock->self, (struct sockaddr*) &socket_address, sizeof(socket_address)) == SOCKET_ERROR) {
        #if defined(CROCKET_WINDOWS)
            _crocket_update_error_context(
                WSAGetLastError(),
                "Failed to bind socket to arbitrary port"
            );
        #elif defined(CROCKET_LINUX)
            _crocket_update_error_context(errno, strerror(errno));
        #endif

        return false;
    }

    if (port == CROCKET_SOCKET_EPHEMERAL_PORT) {
        socklen_t socket_address_length = sizeof(socket_address);

        getsockname(sock->self, (struct sockaddr*) &socket_address, &socket_address_length);

        sock->port = socket_address.sin_port;
    }
    else {
        sock->port = port;
    }

    return true;
}

CROCKET_API bool crocket_socket_close(crocket_socket_t* sock) {
    #ifdef CROCKET_WINDOWS
        _check_winsock();
    #endif

    #if defined(CROCKET_WINDOWS)
        int return_code = closesocket(sock->self);
    #elif defined(CROCKET_LINUX)
        int return_code = close(sock->self);
    #endif

    if (return_code == SOCKET_ERROR) {
        #if defined(CROCKET_WINDOWS)
            _crocket_update_error_context(
                WSAGetLastError(),
                "Failed to close socket"
            );
        #elif defined(CROCKET_LINUX)
            _crocket_update_error_context(errno, strerror(errno));
        #endif

        return false;
    }

    return true;
}