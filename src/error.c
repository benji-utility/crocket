#include "error.h"

void _crocket_update_error_context(const int error_code, const char* error_message) {
    _crocket_error_context.error_code = error_code;
    _crocket_error_context.error_message = error_message;
}

int crocket_get_last_error_code() {
    return _crocket_error_context.error_code;
}

const char* crocket_get_last_error_message() {
    return _crocket_error_context.error_message;
}