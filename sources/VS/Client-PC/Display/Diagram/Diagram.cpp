// 2022/09/05 08:52:55 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Display/Diagram/Diagram.h"
#include "Display/Diagram/Canvas.h"


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


Diagram::Diagram(wxWindow *parent, TypeMeasure::E type) : wxPanel(parent, wxID_ANY)
{
    wxBoxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);

    sizer->Add(new Canvas(this, type));

    SetSizer(sizer);
}
