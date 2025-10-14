#include <stdio.h>
#include <string.h>

#include "../src/crocket.h"

int main(void) {
     #ifdef CROCKET_WINDOWS
        winsock_init();
    #endif

    socket_t client_socket;

    if (!crocket_socket_init(&client_socket, AF_INET, SOCK_STREAM, CROCKET_SOCKET_PROTOCOL_ANY)) {
        printf("Failed to init client socket\n");

        #ifdef CROCKET_WINDOWS
            winsock_cleanup();
        #endif

        return EXIT_FAILURE;
    }

    unsigned short port;

    printf("Enter server port: ");
    scanf("%hu", &port);

    if (!crocket_socket_set_address(&client_socket, AF_INET, "127.0.0.1", port)) {
        printf("Failed to set client socket address\n");

        #ifdef CROCKET_WINDOWS
            winsock_cleanup();
        #endif

        return EXIT_FAILURE;
    }

    if (!crocket_socket_connect(&client_socket)) {
        printf("Failed to connect client socket to server\n");

        crocket_socket_close(&client_socket);

        #ifdef CROCKET_WINDOWS
            winsock_cleanup();
        #endif

        return EXIT_FAILURE;
    }

    const char* message = "this is a test";

    if (crocket_socket_send(&client_socket, (void*) message, strlen(message), CROCKET_NO_FLAGS)) {
        printf("Sent message bytes to server: ");

        for (size_t i = 0; i < strlen(message); i++) {
            printf("%02x ", (unsigned char) message[i]);
        }

        printf("\n");
    }
    else {
        printf("Failed to send data from client to server\n");

        crocket_socket_close(&client_socket);

        #ifdef CROCKET_WINDOWS
            winsock_cleanup();
        #endif

        return EXIT_FAILURE;
    }

    crocket_socket_close(&client_socket);

    #ifdef CROCKET_WINDOWS
        winsock_cleanup();
    #endif

    return EXIT_SUCCESS;
}
