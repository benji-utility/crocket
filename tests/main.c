#include <stdlib.h>
#include <stdio.h>

#include "../src/crocket.h"

int main(void) {
    socket_t server;

    if (!crocket_socket_init(&server, AF_INET, SOCK_STREAM, 0)) {
        printf("Server socket creation failed\n");

        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
