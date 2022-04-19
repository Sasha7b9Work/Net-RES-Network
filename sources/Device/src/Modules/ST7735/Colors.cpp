// 2022/03/12 09:37:38 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "main.h"
#include "Modules/ST7735/Colors.h"



Color::E Color::current = Color::Count;

const uint16 colors[Color::Count] =
{
    0xffff,
    0x0000,
    MAKE_COLOR(31, 0, 0),
    MAKE_COLOR(0, 63, 0),
    MAKE_COLOR(0, 0, 31)
};


void Color::SetCurrent(Color::E color)
{
    if (color != Color::Count)
    {
        current = color;
    }
}


Color::E Color::GetCurrent()
{
    return current;
}


uint16 Color::GetValue()
{
    return colors[current];
}
