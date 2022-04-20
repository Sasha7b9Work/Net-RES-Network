// 2022/03/12 09:37:38 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "main.h"
#include "Display/Colors.h"


Color::E Color::current = Color::Count;


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
