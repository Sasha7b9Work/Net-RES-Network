// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once

#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
    #pragma clang diagnostic ignored "-Winvalid-utf8"
    #pragma clang diagnostic ignored "-Wunsafe-buffer-usage"
    #pragma clang diagnostic ignored "-Wpadded"
    #pragma clang diagnostic ignored "-Wc++98-compat-pedantic"
    #pragma clang diagnostic ignored "-Wold-style-cast"
    #pragma clang diagnostic ignored "-Wcast-align"
    #pragma clang diagnostic ignored "-Wglobal-constructors"
    #pragma clang diagnostic ignored "-Wcast-qual"
    #pragma clang diagnostic ignored "-Wweak-vtables"
    #pragma clang diagnostic ignored "-Wundefined-func-template"
    #pragma clang diagnostic ignored "-Wmissing-variable-declarations"
    #pragma clang diagnostic ignored "-Winvalid-source-encoding"
    #pragma clang diagnostic ignored "-Wmissing-prototypes"
    #pragma clang diagnostic ignored "-Wexit-time-destructors"
#endif


#include <stm32f1xx_hal.h>


typedef unsigned char uint8;
typedef signed char int8;
typedef unsigned short uint16;
typedef signed short int16;
typedef unsigned int uint;
typedef const char *pchar;
typedef unsigned char uchar;


// Промежуток между измерениями
#define TIME_MEASURE  500U


#ifdef WIN32
//    #define IN_MODE_TEST
    #undef asm
#else
//    #define nullptr 0 //-V1059
#endif


#define TYPE_1          // Присутствуют все датчики
//#define TYPE_2          // Отсутствует датчик скорости воздуха

#ifdef TYPE_1
    #ifdef TYPE_2
        static_assert(0, "Нельзя оба типа определять");
    #endif
#endif

#ifndef TYPE_1
    #ifndef TYPE_2
        static_assert(0, "Определите тип - 1 или 2");
    #endif
#endif


union BitSet32
{
    uint   word;
    uint16 half_word[2];
    uint8  byte[4];
};


#define _GET_BIT(value, bit)   (((value) >> (bit)) & 0x01)
#define _SET_BIT(value, bit)   ((value) |= (1 << (bit)))
#define _CLEAR_BIT(value, bit) ((value) &= (~(1 << (bit))))


#define ERROR_VALUE_FLOAT   1.111e29f


#include "Log.h"
