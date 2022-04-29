// 2022/04/29 13:56:43 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#define WIN32_LEAN_AND_MEAN
#include <wx/wx.h>

class Application : public wxApp
{
public:
    virtual bool OnInit() wxOVERRIDE;

private:

    void Init();

    void Update();
};
