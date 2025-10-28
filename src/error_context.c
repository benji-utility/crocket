#include "error_context.h"

typedef struct _CROCKET_ERROR_CONTEXT {
    int code;
    char message[CROCKET_ERROR_MESSAGE_LENGTH];
} error_context_t;

static error_context_t _crocket_error_context;

bool crocket_error_context_init() {
    _crocket_error_context.code = CROCKET_ERROR_NONE;
    _crocket_error_context.message[0] = '\0';

    return true; // leave as boolean return for easier error checking later
}

int crocket_get_last_error_code() {
    return _crocket_error_context.code;
}

char* crocket_get_last_error_message() {
    return _crocket_error_context.message[0] ? _crocket_error_context.message : CROCKET_ERROR_UNKNOWN_MESSAGE;
}

void crocket_clear_last_error() {
    // todo: this may not be the best idea, but it gets rid of redundancy soooooo
    crocket_error_context_init();
}

void _crocket_update_error_context(int code, const char* message, ...) {
    _crocket_error_context.code = code;

    if (message) {
        va_list arguments;

        va_start(arguments, message);

        vsnprintf(_crocket_error_context.message, CROCKET_ERROR_MESSAGE_LENGTH, message, arguments);

        va_end(arguments);

        _crocket_error_context.message[CROCKET_ERROR_MESSAGE_LENGTH - 1] = '\0';
    }
    else {
        _crocket_error_context.message[0] = '\0';
    }
}
