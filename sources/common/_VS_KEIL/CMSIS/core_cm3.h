#pragma once

#ifdef GUI
    typedef unsigned int uint32_t;
    typedef unsigned char uint8_t;

    #define __IO volatile
    #define __I volatile

#else
    #include <integer.h>
#endif
