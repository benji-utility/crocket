#include "error_context.h"

typedef struct _CROCKET_ERROR_CONTEXT {
    char message[CROCKET_ERROR_MESSAGE_LENGTH];
    int code;
} error_context_t;

static error_context_t _crocket_error_context;

char* crocket_get_last_error_message() {
    return _crocket_error_context.message[0] ? _crocket_error_context.message : "???";
}

int crocket_get_last_error_code() {
    return _crocket_error_context.code;
}

void crocket_clear_last_error() {
    _crocket_error_context.message[0] = '\0';
    _crocket_error_context.code = 0;
}

void _crocket_update_error_context(const char* message, int code) {
    _crocket_error_context.code = code;

    if (message) {
        size_t context_message_length = strlen(_crocket_error_context.message);

        strncpy(
            _crocket_error_context.message,
            message,
            context_message_length - 1
        );

        _crocket_error_context.message[context_message_length] = '\0';
    }
    else {
        _crocket_error_context.message[0] = '\0';
    }
}
