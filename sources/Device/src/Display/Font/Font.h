// 2022/02/11 15:58:41 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "defines.h"


struct TypeFont
{
    enum E
    {
        _5,
        _8,
        _12_10,
        Count
    };
};


namespace Font
{
    int GetSpacing();
    int8 Height();
    bool BitInSymbolIsExist(uint symbol, int byte, int bit);
    void Set(TypeFont::E);

    namespace Symbol
    {
        int8 Width(uint8);
        int Height(char symbol);
        bool LineNotEmpty(uint symbol, int line);
    }
};


struct Symbol8
{
    uchar width;
    uchar bytes[8];
};


struct Font8
{
    int height;
    Symbol8 symbol[256];

    static int GetLengthText(pchar text);
};


struct Symbol22
{
    uint8 width;
    int16 words[12];
};


// Ўрифт макимальными размерам 2х2 байта
struct Font22
{
    int height;
    int width;

    Symbol22 symbol[256];
};
