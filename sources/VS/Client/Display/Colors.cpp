// 2022/04/29 17:13:25 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "Display/Colors.h"


wxColour colors[Color::Count] =
{
    wxColour(0, 0, 0),
    wxColour(255, 255, 255),
    wxColour(100, 100, 100)
};


namespace Display
{
    // Здесь будем рисовать
    extern wxMemoryDC memDC;

    extern wxPen pen;
    extern wxBrush brush;
}


void Color::SetAsCurrent()
{
    if (value == Count)
    {
        return;
    }

    Display::pen.SetColour(colors[value]);
    Display::brush.SetColour(colors[value]);

    Display::memDC.SetBrush(Display::brush);
    Display::memDC.SetPen(Display::pen);

    Display::memDC.SetTextForeground(colors[value]);
}
