// 2022/09/05 08:47:51 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Data/Sensors.h"


/*
*   Здесь непосредственно отрисовка
*/


class Canvas : public wxPanel
{
public:

    Canvas(wxWindow *parent, TypeMeasure::E);

    void SetSizeArea(int, int);

private:

    TypeMeasure::E type;

    void OnPaint(wxPaintEvent &);

    // Нарисовать измерения со всех датчиков
    void DrawAllSensors(wxClientDC &);
};
