#include <stdio.h>

#include "crocket.h"

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

    print("Socket created\n");

    winsock_cleanup();
}