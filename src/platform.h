#ifndef __CROCKET_H
    #error "Do not include this file directly, instead use <crocket.h>"
#endif

#ifndef __CROCKET_PLATFORM_H
    #if defined(_WIN32) || defined(_WIN64)
        #ifndef CROCKET_WINDOWS
            #define CROCKET_WINDOWS
        #endif
    #elif defined(__linux__)
        #ifndef CROCKET_LINUX
            #define CROCKET_LINUX
        #endif
    #endif
#endif