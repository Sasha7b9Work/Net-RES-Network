// 2022/04/29 17:13:31 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#define WIN32_LEAN_AND_MEAN
#include <wx/wx.h>


struct Color
{
    static Color BLACK;
    static Color WHITE;
    static Color _1;
    static Color NONE;

    wxColour value;

    Color(wxColour v) : value(v) {}

    static void SetCurrent(Color);
};
