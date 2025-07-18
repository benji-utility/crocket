#include <stdio.h>

#include "../src/crocket.h"

int main(void) {
    crocket_winsock_init();

    crocket_socket_t sock;

    if (!crocket_socket_init(&sock)) {
        fprintf(
            stderr,
            "Error: %s (error code %i)\n",
            crocket_get_last_error_message(),
            crocket_get_last_error_code()
        );

        return EXIT_FAILURE;
    }

    printf("Socket created\n");

    if (!crocket_socket_bind_any(&sock)) {
        fprintf(
            stderr,
            "Error: %s (error code %i)\n",
            crocket_get_last_error_message(),
            crocket_get_last_error_code()
        );

        return EXIT_FAILURE;
    }

    printf("Socket binded to port %u\n", sock.port);

    if (!crocket_socket_close(&sock)) {
        fprintf(
            stderr,
            "Error: %s (error code %i)\n",
            crocket_get_last_error_message(),
            crocket_get_last_error_code()
        );

        return EXIT_FAILURE;
    }

    printf("Socket closed\n");

    crocket_winsock_cleanup();

    return EXIT_SUCCESS;
}