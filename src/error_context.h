#ifndef __CROCKET_ERROR_CONTEXT
#define __CROCKET_ERROR_CONTEXT

#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>

#ifndef CROCKET_ERROR_MESSAGE_LENGTH
    #define CROCKET_ERROR_MESSAGE_LENGTH (256)
#endif

#ifndef CROCKET_ERROR_UNKNOWN_MESSAGE
    #define CROCKET_ERROR_UNKNOWN_MESSAGE "Unrecognized error or invalid error message"
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef enum _CROCKET_ERROR_CODES {
    CROCKET_ERROR_NONE = 0,
    
    #ifdef CROCKET_WINDOWS
        CROCKET_ERROR_WINSOCK_INIT_FAILED = -1,
        CROCKET_ERROR_WINSOCK_CLEANUP_FAILED = -2,
    #endif

    CROCKET_ERROR_SOCKET_INIT_FAILED,
    CROCKET_ERROR_SOCKET_CLOSE_FAILED,
    CROCKET_ERROR_SOCKET_BIND_FAILED,
    CROCKET_ERROR_SOCKET_LISTEN_FAILED,
    CROCKET_ERROR_SOCKET_ACCEPT_FAILED,
    CROCKET_ERROR_SOCKET_CONNECT_FAILED
} error_code_t;

bool crocket_error_context_init();

int crocket_get_last_error_code();
char* crocket_get_last_error_message();

void crocket_clear_last_error();

void _crocket_update_error_context(int code, const char* message, ...);

#ifdef __cplusplus
}
#endif

#endif
