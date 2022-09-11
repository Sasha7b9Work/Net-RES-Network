// 2022/09/05 08:53:11 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Data/Sensors.h"
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

    void SetSizeArea(int, int);

private:

    Canvas *canvas = nullptr;
};


class DiagramPool : public wxPanel
{
public:

    static DiagramPool *Create(wxWindow *);

    static DiagramPool *self;

    void SetSizeArea(int width, int height);

    // Данные изменились и нужно перерисовать
    void NeedRefresh(TypeMeasure::E);

private:

    DiagramPool(wxWindow *parent);

    Diagram *pool[TypeMeasure::Count];
};

