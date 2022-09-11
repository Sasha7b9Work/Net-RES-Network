// 2022/09/05 08:47:32 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Display/Diagram/Canvas.h"


Canvas::Canvas(wxWindow *parent, TypeMeasure::E _type) : wxPanel(parent, wxID_ANY),
    type(_type)
{
//    SetDoubleBuffered(true);

    Bind(wxEVT_PAINT, &Canvas::OnPaint, this);

    SetMinClientSize({ 100, 100 });
    SetClientSize(100, 100);
}


void Canvas::OnPaint(wxPaintEvent &)
{
    wxClientDC dc(this);

    dc.SetBrush(*wxWHITE_BRUSH);
    dc.SetPen(wxPen(wxColor(0, 0, 0)));

    dc.DrawRectangle(GetClientRect());

    static const wxString labels[TypeMeasure::Count] =
    {
        "Давление",
        "Освещённость",
        "Температура",
        "Влажность",
        "Скорость"
    };

    dc.DrawText(labels[type], 1, 0);
}


void Canvas::SetWidthArea(int width)
{
    wxSize size = GetClientSize();

    size.SetWidth(width);

    SetMinClientSize(size);
    SetClientSize(size);
}
