#include "socket.h"

CROCKET_API bool crocket_socket_init(socket_t* sock, int address_family, int type, int protocol) {
    #ifdef CROCKET_WINDOWS
        if (!winsock_init()) {
            // todo: collect error info

            return false;
        }
    #endif

    sock->handle = socket(address_family, type, protocol);

    if (sock->handle == CROCKET_INVALID_SOCKET) {
        // todo: collect error info

        return false;
    }

    return true;
}

CROCKET_API bool crocket_socket_close(socket_t* sock) {
    #ifdef CROCKET_WINDOWS
        if (!winsock_init()) {
            // todo: collect error info

            return false;
        }
    #endif

    if (!sock) {
        return false;
    }

    #if defined(CROCKET_WINDOWS)
        closesocket(sock->handle);
    #elif defined(CROCKET_LINUX)
        if (close(sock->handle) != CROCKET_SUCCESS) {
            // todo: collect error info

            return false;
        }
    #endif

    sock->handle = CROCKET_INVALID_SOCKET;

    return true;
}

CROCKET_API bool crocket_socket_set_address(socket_t* sock, int address_family, const char* ip, unsigned short port) {
    #ifdef CROCKET_WINDOWS
        if (!winsock_init()) {
            // todo: collect error info

            return false;
        }
    #endif

    if (!sock) {
        return false;
    }

    memset(&sock->address, 0, sizeof(sock->address));

    sock->address.sin_family = address_family;
    sock->address.sin_port = port == CROCKET_PORT_ANY ? 0 : htons(port);

    if (ip == CROCKET_IP_ANY) {
        _CROCKET_SOCKADDR_IN_ADDRESS(sock->address) = INADDR_ANY;
    }
    else if (inet_pton(address_family, ip, &sock->address.sin_addr) != _CROCKET_INET_PTON_SUCCESS) {
        // todo: collect error info

        return false;
    }

    return true;
}

CROCKET_API bool crocket_socket_set_address_any(socket_t* sock, int address_family) {
    return crocket_socket_set_address(sock, address_family, CROCKET_IP_ANY, CROCKET_PORT_ANY);
}

CROCKET_API bool crocket_socket_bind(socket_t* sock) {
    #ifdef CROCKET_WINDOWS
        if (!winsock_init()) {
            // todo: collect error info

            return false;
        }
    #endif

    if (!sock) {
        // todo: collect error info

        return false;
    }

    if (bind(sock->handle, (struct sockaddr*) &sock->address, sizeof(sock->address)) != CROCKET_SUCCESS) {
        // todo: collect error info

        return false;
    }

    return true;
}

CROCKET_API bool crocket_socket_listen(socket_t* sock, size_t backlog) {
    #ifdef CROCKET_WINDOWS
        if (!winsock_init()) {
            // todo: collect error info

            return false;
        }
    #endif

    if (!sock) {
        // todo: collect error info

        return false;
    }

    if (backlog > SOMAXCONN) {
        // todo: collect error info

        return false;
    }

    if (listen(sock->handle, backlog) != CROCKET_SUCCESS) {
        // todo: collect error info

        return false;
    }

    return true;
}

CROCKET_API bool crocket_socket_accept(socket_t* server_socket, socket_t* client_socket) {
    #ifdef CROCKET_WINDOWS
        if (!winsock_init()) {
            // todo: collect error info

            return false;
        }
    #endif

    if (!server_socket || !client_socket) {
        // todo: collect error info

        return false;
    }

    struct sockaddr_in client_address;

    socklen_t address_length = sizeof(client_address);

    socket_handle_t client_handle = accept(
        server_socket->handle,
        (struct sockaddr*) &client_address,
        &address_length
    );

    if (client_handle == CROCKET_INVALID_SOCKET) {
        // todo: collect error info

        return false;
    }

    client_socket->handle = client_handle;
    client_socket->address = client_address;

    return true;
}

CROCKET_API bool crocket_socket_connect(socket_t* sock) {
    #ifdef CROCKET_WINDOWS
        if (!winsock_init()) {
            // todo: collect error info

            return false;
        }
    #endif

    if (!sock) {
        // todo: collect error info

        return false;
    }

    if (connect(sock->handle, (struct sockaddr*) &sock->address, sizeof(sock->address)) != CROCKET_SUCCESS) {
        // todo: collect error info

        return false;
    }

    return true;
}

CROCKET_API bool crocket_socket_send(socket_t* sock, void* data, size_t data_length, int flags) {
    #ifdef CROCKET_WINDOWS
        if (!winsock_init()) {
            // todo: collect error info

            return false;
        }
    #endif

    if (!sock || !data || data_length == 0) {
        // todo: collect error info

        return false;
    }

    size_t bytes_sent = send(sock->handle, data, data_length, flags);

    if (bytes_sent == -1) {
        // todo: collect error info

        return false;
    }

    return true;
}

CROCKET_API bool crocket_socket_receive(socket_t* sock, char** data_buffer, size_t* buffer_capacity, size_t* bytes_received, int flags) {
    #ifdef CROCKET_WINDOWS
        if (!winsock_init()) {
            // todo: collect error info

            return false;
        }
    #endif

    if (!sock || *buffer_capacity == 0) {
        // todo: collect error info

        return false;
    }

    *bytes_received = 0;

    while (true) {
        char chunk[_CROCKET_RECV_CHUNK_SIZE];

        ssize_t received = recv(sock->handle, chunk, sizeof(chunk), flags);

        if (received < 0) {
            // todo: collect error info

            return false;
        }

        if (received == 0) break; // connection closed

        if (*bytes_received + received > *buffer_capacity) {
            size_t new_size = *buffer_capacity * 2;

            while (*bytes_received + received > new_size) {
                new_size *= 2;
            }

            char* new_buffer = realloc(*data_buffer, new_size);

            if (!new_buffer) {
                // todo: collect error info

                return false;
            }

            *data_buffer = new_buffer;

            *buffer_capacity = new_size;
        }

        memcpy(*data_buffer + *bytes_received, chunk, received);

        *bytes_received += received;

        if ((size_t) received < sizeof(chunk)) break;
    }

    return true;
}

CROCKET_API bool crocket_socket_get_ip(const socket_t sock, int address_family, char* buffer, size_t buffer_size) {
    #ifdef CROCKET_WINDOWS
        if (!winsock_init()) {
            // todo: collect error info

            return false;
        }
    #endif

    if (!buffer || buffer_size == 0) {
        // todo: collect error info

        return false;
    }

    struct sockaddr_in address;

    socklen_t address_length = sizeof(address);

    if (getsockname(sock.handle, (struct sockaddr*) &address, &address_length) != CROCKET_SUCCESS) {
        // todo: collect error info

        return false;
    }

    if (!inet_ntop(address_family, &address.sin_addr, buffer, (socklen_t) buffer_size)) {
        // todo: collect error info

        return false;
    }

    return true;
}

CROCKET_API bool crocket_socket_get_port(const socket_t sock, unsigned short* port) {
    #ifdef CROCKET_WINDOWS
        if (!winsock_init()) {
            // todo: collect error info

            return false;
        }
    #endif

    struct sockaddr_in address;

    socklen_t address_length = sizeof(address);

    if (getsockname(sock.handle, (struct sockaddr*) &address, &address_length) != CROCKET_SUCCESS) {
        // todo: collect error info

        return false;
    }

    *port = ntohs(address.sin_port);

    return true;
}
