// 2022/02/11 15:58:35 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Font.h"

#include "font5.inc"
#include "font8.inc"
#include "font12_10.inc"



const Font8 *Font8::fonts[TypeFont::Count] = {&font5, &font8};
const Font8 *Font8::font = &font8;

TypeFont::E Font8::current = TypeFont::Count;


int Font8::GetSize()
{
    return Font8::font->height;
}


int Font8::GetLengthText(pchar text)
{
    int retValue = 0;
    while (*text)
    {
        retValue += Font8::GetLengthSymbol((uint8)*text) + GetSpacing();
        text++;
    }
    return retValue;
}


int Font8::GetHeightSymbol(char)
{
    return 9;
}


int Font8::GetLengthSymbol(uchar symbol)
{
    return Font8::font->symbol[symbol].width;
}


int Font8::GetSpacing()
{
    return 1;
}
