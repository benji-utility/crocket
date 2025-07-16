#include <stdio.h>

#include "../src/crocket.h"

int main(void) {
    winsock_init();

    crocket_socket_t sock;

    if (!crocket_socket_init(&sock)) {
        fprintf(
            stderr,
            "Error: %s (error code %i)\n",
            crocket_get_last_error_message(),
            crocket_get_last_error_code()
        );
    }

    printf("Socket created\n", sock.port);

    if (!crocket_socket_close(&sock)) {
        fprintf(
            stderr,
            "Error: %s (error code %i)\n",
            crocket_get_last_error_message(),
            crocket_get_last_error_code()
        );
    }

    printf("Socket closed\n");

    winsock_cleanup();
}