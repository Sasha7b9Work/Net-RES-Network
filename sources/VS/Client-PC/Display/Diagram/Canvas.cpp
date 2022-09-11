// 2022/09/05 08:47:32 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Display/Diagram/Canvas.h"
#include "Data/Sensors.h"
#include <map>


using namespace std;


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

    DrawAllSensors(dc);
}


void Canvas::SetSizeArea(int width, int height)
{
    SetMinClientSize({ width, height } );
    SetClientSize({ width, height });
}


void Canvas::DrawAllSensors(wxClientDC &)
{
    const map<uint, Sensor> &pool = Sensor::Pool::GetPool();

    if (pool.empty())
    {
        return;
    }

    for (auto element : pool)
    {
        const Sensor &sensor = element.second;

        const std::vector<float> &measures = sensor.GetMeasures(type);

        if (measures.size())
        {

        }
    }
}
