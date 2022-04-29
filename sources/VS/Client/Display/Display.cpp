// 2022/04/29 16:45:45 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#define WIN32_LEAN_AND_MEAN
#include "Display/Display.h"
#include "Display/Colors.h"
#include <wx/wx.h>


namespace Display
{

    void BeginScene(Color &);

    void DrawText(const wxString &, Color & = Color::NONE);

    void EndScene();
}


void Display::Update()
{
    BeginScene(Color::BLACK);

    DrawText(_("Тестовая строка"), Color::WHITE);

    EndScene();
}


void Display::BeginScene(Color &)
{

}


void Display::DrawText(const wxString &, Color & /* = Color::NONE */)
{

}


void Display::EndScene()
{

}
