#include "error.h"

void _update_error_context(const int error_code, const char* error_message) {
    _error_context.error_code = error_code;
    _error_context.error_message = error_message;
}

int crocket_get_last_error_code() {
    return _error_context.error_code;
}

const char* crocket_get_last_error_message() {
    return _error_context.error_message;
}