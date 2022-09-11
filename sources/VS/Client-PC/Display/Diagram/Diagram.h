// 2022/09/05 08:53:11 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Data/PoolSensors.h"
#include "Display/Diagram/Canvas.h"
#pragma warning(push, 0)
#include <wx/wx.h>
#pragma warning(pop)


/*
*   Виджет с графиком
*/


class Diagram : public wxPanel
{
public:

    Diagram(wxWindow *parant, TypeMeasure::E);

    void SetWidthArea(int);

private:

    Canvas *canvas = nullptr;
};


class DiagramPool : public wxPanel
{
public:
    DiagramPool(wxWindow *parent);

    void SetSizeArea(int width, int height);

private:

    Diagram *pool[TypeMeasure::Count];
};

