// 2022/03/12 09:37:31 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


struct Color
{
    enum E
    {
        WHITE,
        BLACK,
        RED,
        GREEN,
        BLUE,
        Count
    };

    E value;

    Color(E v) : value(v) {}

    static void SetCurrent(E);

    static E GetCurrent();

    static uint16 GetValue();

private:

    static Color::E current;
};


#define COLOR(color)    colors[color]

extern const uint16 colors[Color::Count];

#define MAKE_COLOR(r, g, b)  (uint16)(b + (g << 5) + (r << 11))
