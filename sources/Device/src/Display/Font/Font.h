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


struct Font
{
    static int GetSpacing();
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

    static const Font8 *font;
    static const Font8 *fonts[TypeFont::Count];

    static TypeFont::E current;

    static int GetSize();

    static int GetLengthText(pchar text);

    static int GetHeightSymbol(char symbol);

    static int GetLengthSymbol(uchar symbol);

    static void Set(TypeFont::E);
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
