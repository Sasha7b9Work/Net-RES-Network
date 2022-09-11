// 2022/09/05 08:47:51 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Data/PoolSensors.h"


/*
*   Здесь непосредственно отрисовка
*/


class Canvas : public wxPanel
{
public:
    Canvas(wxWindow *parent, TypeMeasure::E);
private:
    void OnPaint(wxPaintEvent &);
    TypeMeasure::E type;
};
