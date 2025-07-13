#ifndef __CROCKET_ERROR_H
#define __CROCKET_ERROR_H

#ifndef CROCKET_ERROR_NONE
    #define CROCKET_ERROR_NONE (0)
#endif

static struct _CROCKET_ERROR_CONTEXT {
    int error_code;
    const char* error_message;
} _error_context;

static inline void _update_error_context(int error_code, const char* error_message) {
    _error_context.error_code = error_code;
    _error_context.error_message = error_message;
}

static inline int crocket_get_last_error_code() {
    return _error_context.error_code;
}

static inline const char* crocket_get_last_error_message() {
    return _error_context.error_message;
}

#endif