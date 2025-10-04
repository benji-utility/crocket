#include "socket.h"

CROCKET_API bool crocket_socket_init(socket_t* sock, int address_family, int type, int protocol) {
    // todo: check if WSAStartup has been called
    
    sock->handle = socket(address_family, type, protocol);

    if (sock->handle == CROCKET_INVALID_SOCKET) {
        // todo: collect error info

        return false;
    }

    return true;
}

CROCKET_API bool crocket_socket_close(socket_t* sock) {
    // todo: check if WSAStartup has been called

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
    // todo: check if WSAStartup has been called

    if (!sock) {
        return false;
    }

    memset(&sock->address, 0, sizeof(sock->address));

    sock->address.sin_family = address_family;
    sock->address.sin_port = htons(port);

    if (inet_pton(address_family, ip, &sock->address.sin_addr) != CROCKET_INET_PTON_SUCCESS) {
        // todo: collect error info

        return false;
    }

    return true;
}

CROCKET_API bool crocket_socket_bind(socket_t* sock) {
    // todo: check if WSAStartup has been called

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
    // todo: check if WSAStartup has been called

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
    // todo: check if WSAStartup has been called
    
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
