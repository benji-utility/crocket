#include <stdlib.h>
#include <stdio.h>

#include "../src/crocket.h"

int main(void) {
    #ifdef CROCKET_WINDOWS
        winsock_init();
    #endif
    
    socket_t server_socket;

    if (!crocket_socket_init(&server_socket, AF_INET, SOCK_STREAM, 0)) {
        printf("Server socket creation failed\n");

        return EXIT_FAILURE;
    }

    if (!crocket_socket_set_address(&server_socket, AF_INET, "127.0.0.1", CROCKET_PORT_ANY)) {
        printf("Unable to assign address to server socket\n");
        
        return EXIT_FAILURE;
    }

    if (!crocket_socket_bind(&server_socket)) {
        printf("Failed to bind server socket to assigned address\n");

        return EXIT_FAILURE;
    }

    if (!crocket_socket_listen(&server_socket, 5)) {
        printf("Failed to put server socket into listening mode\n");

        return EXIT_FAILURE;
    }

    char ip[CROCKET_IP_STRING_LENGTH];

    crocket_socket_get_ip(server_socket, AF_INET, ip, sizeof(ip));

    printf("Server socket listening on %s:%u ...\n", ip, crocket_socket_get_port(server_socket));

    socket_t client_socket;

    if (crocket_socket_accept(&server_socket, &client_socket)) {
        printf("Client connected (handle=0x%x)\n", client_socket.handle);

        crocket_socket_close(&client_socket);
    }
    else {
        printf("Failed to maintain client connection\n");
    }

    crocket_socket_close(&server_socket);

    #ifdef CROCKET_WINDOWS
        winsock_cleanup();
    #endif

    return EXIT_SUCCESS;
}
