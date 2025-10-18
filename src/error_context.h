#ifndef __CROCKET_ERROR_CONTEXT
#define __CROCKET_ERROR_CONTEXT

#include "crocket_base.h"

#ifndef CROCKET_ERROR_MESSAGE_LENGTH
    #define CROCKET_ERROR_MESSAGE_LENGTH (256)
#endif

#ifdef __cplusplus
extern "C" {
#endif

char* crocket_get_last_error_message();
int crocket_get_last_error_code();

void crocket_clear_last_error();

void _crocket_update_error_context(const char* message, int code);

#ifdef __cplusplus
}
#endif

#endif
