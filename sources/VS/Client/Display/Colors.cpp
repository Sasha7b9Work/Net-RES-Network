// 2022/04/29 17:13:25 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "Display/Colors.h"


namespace Display
{
    // Здесь будем рисовать
    extern wxMemoryDC memDC;

    extern wxPen pen;
    extern wxBrush brush;
}


Color Color::WHITE(wxColour(255, 255, 255));
Color Color::BLACK(wxColour(0, 0, 0));
Color Color::_1(wxColour(100, 100, 100));
Color Color::NONE(wxColour(0, 0, 0));


void Color::SetAsCurrent()
{
    if (this == &Color::NONE)
    {
        return;
    }

    Display::pen.SetColour(value);
    Display::brush.SetColour(value);

    Display::memDC.SetBrush(Display::brush);
    Display::memDC.SetPen(Display::pen);

    Display::memDC.SetTextForeground(value);
}
