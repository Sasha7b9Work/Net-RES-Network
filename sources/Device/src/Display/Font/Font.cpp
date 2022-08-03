// 2022/02/11 15:58:35 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Font.h"

#include "font5.inc"
#include "font8.inc"
#include "font12_10.inc"



namespace Font
{
    TypeFont::E current = TypeFont::Count;

    const Font8 *fonts[TypeFont::Count] = { &font5, &font8 };
    const Font8 *font = &font8;
}


int Font8::GetLengthText(pchar text)
{
    int retValue = 0;
    while (*text)
    {
        retValue += Font::Symbol::Width((uint8)*text) + Font::GetSpacing();
        text++;
    }
    return retValue;
}


int Font::Symbol::Height(char)
{
    return 9;
}


int Font::GetSpacing()
{
    return 1;
}


void Font::Set(TypeFont::E typeFont)
{
    if (typeFont == Font::current)
    {
        return;
    }

    Font::font = Font::fonts[typeFont];
}


int8 Font::Symbol::Width(uint8 symbol)
{
    return (int8)font->symbol[symbol].width;
}


int8 Font::Height()
{
    return (int8)font->height;
}


bool Font::Symbol::LineNotEmpty(uint eChar, int line)
{
    static const uint8 *bytes = 0;
    static uint prevChar = (uint)(-1);

    if (eChar != prevChar)
    {
        prevChar = eChar;
        bytes = font->symbol[prevChar].bytes;
    }

    return bytes[line] != 0;
}


bool Font::Symbol::BitInLineIsExist(uint eChar, int numByte, int bit)
{
    static uint8 prevByte = 0;      // WARN здесь точно статики нужны?
    static uint prevChar = (uint)(-1);
    static int prevNumByte = -1;

    if (prevNumByte != numByte || prevChar != eChar)
    {
        prevByte = font->symbol[eChar].bytes[numByte];
        prevChar = eChar;
        prevNumByte = numByte;
    }

    return prevByte & (1 << bit);
}
