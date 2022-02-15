// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#ifndef __MAIN_H
#define __MAIN_H


typedef unsigned char uint8;
typedef signed char int8;
typedef unsigned short uint16;
typedef unsigned int uint;

union BitSet32
{
    uint   word;
    uint16 half_word[2];
    uint8  byte[4];
};


#ifdef __cplusplus
extern "C" {
#endif


void Error_Handler();


#ifdef __cplusplus
}
#endif

#endif
