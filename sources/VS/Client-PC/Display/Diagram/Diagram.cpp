// 2022/09/05 08:52:55 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Display/Diagram/Diagram.h"
#include "Display/Diagram/Canvas.h"


Diagram::Diagram(wxWindow *parent, TypeMeasure::E type) : wxPanel(parent, wxID_ANY)
{
    wxBoxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);

    canvas = new Canvas(this, type);

    sizer->Add(canvas);

    SetSizer(sizer);
}


void Diagram::SetWidthArea(int width)
{
    canvas->SetWidthArea(width);
}


DiagramPool::DiagramPool(wxWindow *parent) : wxPanel(parent, wxID_ANY)
{
    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);

    for (int i = 0; i < TypeMeasure::Count; i++)
    {
        pool[i] = new Diagram(this, (TypeMeasure::E)i);

        sizer->Add(pool[i]);
    }

    SetSizer(sizer);
}


void DiagramPool::SetSizeArea(int width, int)
{
    for (Diagram *diagram : pool)
    {
        diagram->SetWidthArea(width);
    }
}
