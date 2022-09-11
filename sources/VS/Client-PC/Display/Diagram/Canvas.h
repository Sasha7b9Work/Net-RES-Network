// 2022/09/05 08:47:51 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


/*
*   Здесь непосредственно отрисовка
*/


class Canvas : public wxPanel
{
public:
    Canvas(wxWindow *parent);
private:
    void OnPaint(wxPaintEvent &);
};
