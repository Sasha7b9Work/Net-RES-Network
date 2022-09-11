// 2022/09/05 08:52:55 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Display/Diagram/Diagram.h"
#include "Display/Diagram/Canvas.h"


DiagramPool *DiagramPool::self = nullptr;


Diagram::Diagram(wxWindow *parent, TypeMeasure::E type) : wxPanel(parent, wxID_ANY)
{
    wxBoxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);

    canvas = new Canvas(this, type);

    sizer->Add(canvas);

    SetSizer(sizer);
}


void Diagram::SetSizeArea(int width, int height)
{
    canvas->SetSizeArea(width, height);
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


DiagramPool *DiagramPool::Create(wxWindow *parent)
{
    self = new DiagramPool(parent);

    return self;
}


void DiagramPool::SetSizeArea(int width, int height)
{
    int dy = height / TypeMeasure::Count;

    for (Diagram *diagram : pool)
    {
        diagram->SetSizeArea(width, dy);
    }
}


void DiagramPool::NeedRefresh(TypeMeasure::E)
{

}
