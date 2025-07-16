#ifndef __CROCKET_ERROR_H
#define __CROCKET_ERROR_H

#ifndef CROCKET_ERROR_NONE
    #define CROCKET_ERROR_NONE (0)
#endif

#ifndef CROCKET_ERROR_WINSOCK_NOT_INITIALIZED
    #define CROCKET_ERROR_WINSOCK_NOT_INITIALIZED (-1)
#endif

static struct _CROCKET_ERROR_CONTEXT {
    int error_code;
    const char* error_message;
} _error_context;

void _update_error_context(int error_code, const char* error_message);

int crocket_get_last_error_code();
const char* crocket_get_last_error_message();

#endif