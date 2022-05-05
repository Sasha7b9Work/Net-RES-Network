// 2022/05/05 09:50:56 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#define WIN32_LEAN_AND_MEAN
#include <wx/wx.h>


namespace Font
{
    void Set(wxFont);

    wxFont Get();

    void SetSize(int);
}
