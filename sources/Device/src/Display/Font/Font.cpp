// 2022/02/11 15:58:35 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Font.h"
#include "Display/Display.h"

#include "font8.inc"
#include "font12_10.inc"



namespace Font
{
    TypeFont::E current = TypeFont::Count;

    const Font8 *fonts[TypeFont::Count] = { &font8 };
    const Font8 *font = &font8;
}


int Font::Text::Length(pchar text)
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


int Font::Symbol::Draw(int eX, int eY, char s)
{
    uint8 symbol = (uint8)s;

    int8 width = Font::Symbol::Width(symbol);
    int8 height = Font::Height();

    for (int b = 0; b < height; b++)
    {
        if (Font::Symbol::LineNotEmpty(symbol, b))
        {
            int x = eX;
            int y = eY + b + 9 - height;
            int endBit = 8 - width;
            for (int bit = 7; bit >= endBit; bit--)
            {
                if (Font::Symbol::BitInLineIsExist(symbol, b, bit))
                {
                    Point().Set(x, y);
                }
                x++;
            }
        }
    }

    return eX + width;
}


int Font::Symbol::DrawBig(int eX, int eY, int size, char s)
{
    uint8 symbol = (uint8)s;

    int8 width = Font::Symbol::Width(symbol);
    int8 height = Font::Height();

    for (int b = 0; b < height; b++)
    {
        if (Font::Symbol::LineNotEmpty(symbol, b))
        {
            int x = eX;
            int y = eY + b * size + 9 - height;
            int endBit = 8 - width;
            for (int bit = 7; bit >= endBit; bit--)
            {
                if (Font::Symbol::BitInLineIsExist(symbol, b, bit))
                {
                    for (int i = 0; i < size; i++)
                    {
                        for (int j = 0; j < size; j++)
                        {
                            Point().Set(x + i, y + j);
                        }
                    }
                }
                x += size;
            }
        }
    }

    return eX + width * size;
}
