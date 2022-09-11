// 2022/09/05 08:53:11 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Data/PoolSensors.h"
#pragma warning(push, 0)
#include <wx/wx.h>
#pragma warning(pop)


/*
*   Виджет с графиком
*/


class Diagram : public wxPanel
{
public:

    Diagram(wxWindow *parant);
};


class DiagramPool : public wxPanel
{
public:
    DiagramPool(wxWindow *parent);

private:

    Diagram *pool[TypeMeasure::Count];
};

