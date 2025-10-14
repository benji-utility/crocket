#include <stdio.h>
#include <stdlib.h>

#include "../src/crocket.h"

int main(void) {
    #ifdef CROCKET_WINDOWS
        winsock_init();
    #endif

    socket_t server_socket;

    if (!crocket_socket_init(&server_socket, AF_INET, SOCK_STREAM, CROCKET_SOCKET_PROTOCOL_ANY)) {
        printf("Failed to init server socket\n");

        #ifdef CROCKET_WINDOWS
            winsock_cleanup();
        #endif

        return EXIT_FAILURE;
    }

    if (!crocket_socket_set_address(&server_socket, AF_INET, "127.0.0.1", CROCKET_PORT_ANY)) {
        printf("Failed to set server socket address\n");

        #ifdef CROCKET_WINDOWS
            winsock_cleanup();
        #endif

        return EXIT_FAILURE;
    }

    if (!crocket_socket_bind(&server_socket)) {
        printf("Failed to bind server socket to internal address\n");

        #ifdef CROCKET_WINDOWS
            winsock_cleanup();
        #endif

        return EXIT_FAILURE;
    }

    if (!crocket_socket_listen(&server_socket, 5)) {
        printf("Failed to put server socket into listening mode\n");

        #ifdef CROCKET_WINDOWS
            winsock_cleanup();
        #endif

        return EXIT_FAILURE;
    }

    char ip[CROCKET_IP_STRING_LENGTH];
    unsigned short port;

    if (!crocket_socket_get_ip(server_socket, AF_INET, ip, sizeof(ip))) {
        printf("Failed to get server socket IP\n");

        crocket_socket_close(&server_socket);

        #ifdef CROCKET_WINDOWS
            winsock_cleanup();
        #endif

        return EXIT_FAILURE;
    }

    if (!crocket_socket_get_port(server_socket, &port)) {
        printf("Failed to get server socket port\n");

        crocket_socket_close(&server_socket);

        #ifdef CROCKET_WINDOWS
            winsock_cleanup();
        #endif

        return EXIT_FAILURE;
    }

    printf("Server listening on %s:%u\n", ip, port);

    socket_t client_socket;

    if (!crocket_socket_accept(&server_socket, &client_socket)) {
        printf("Failed to accept client socket connection\n");

        crocket_socket_close(&server_socket);

        #ifdef CROCKET_WINDOWS
            winsock_cleanup();
        #endif

        return EXIT_FAILURE;
    }

    printf("Client connected (handle=0x%04x)\n", client_socket.handle);

    size_t capacity = 1024;
    char* data = malloc(capacity);

    size_t bytes_received;

    if (crocket_socket_receive(&client_socket, &data, &capacity, &bytes_received, CROCKET_NO_FLAGS)) {
        printf("Received data from client: ");

        for (size_t i = 0; i < bytes_received; i++) {
            printf("%02x ", (unsigned char) data[i]);
        }

        printf("\n");
    }
    else {
        printf("Failed to receive data from client\n");

        crocket_socket_close(&client_socket);
        crocket_socket_close(&server_socket);

        #ifdef CROCKET_WINDOWS
            winsock_cleanup();
        #endif

        return EXIT_FAILURE;
    }

    free(data);

    crocket_socket_close(&client_socket);
    crocket_socket_close(&server_socket);

    #ifdef CROCKET_WINDOWS
        winsock_cleanup();
    #endif

    return EXIT_SUCCESS;
}
