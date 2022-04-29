// 2022/04/29 16:44:45 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#define WIN32_LEAN_AND_MEAN
#include <wx/wx.h>


namespace Display
{
    static const int WIDTH = 320;
    static const int HEIGHT = 240;

    extern wxBitmap bitmap;

    void Update();
}
