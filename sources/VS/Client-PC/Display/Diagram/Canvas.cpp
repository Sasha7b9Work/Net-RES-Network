// 2022/09/05 08:47:32 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Display/Diagram/Canvas.h"
#include "Data/Sensors.h"
#include "Utils/Clock.h"
#include <map>


using namespace std;


Canvas::Canvas(wxWindow *parent, TypeMeasure::E _type) : wxPanel(parent, wxID_ANY),
    type(_type)
{
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

    int dx = 60;

    int x = GetClientSize().GetWidth() - Clock::CurrentTime().sec % dx;

    int y = GetClientSize().GetHeight();

    dc.SetPen(wxPen(wxColor(200, 200, 200)));

    while (x > 0)
    {
        dc.DrawLine(x, 0, x, y);

        x -= dx;
    }

    DrawAllSensors(dc);

    dc.SetPen(wxPen(wxColor(0, 0, 0)));

    static const wxString labels[TypeMeasure::Count] =
    {
        "Давление",
        "Освещённость",
        "Температура",
        "Влажность",
        "Скорость"
    };

    dc.DrawText(labels[type], 1, 0);

    Update();
}


void Canvas::SetSizeArea(int width, int height)
{
    SetMinClientSize({ width, height } );
    SetClientSize({ width, height });
}


void Canvas::DrawAllSensors(wxClientDC &dc)
{
    const map<uint, Sensor> &pool = Sensor::Pool::GetPool();

    if (pool.empty())
    {
        return;
    }

    for (auto element : pool)
    {
        const Sensor &sensor = element.second;

        const DataArray &measures = sensor.GetMeasures(type);

        if (measures.Size())
        {
            DrawSensor(dc, measures);
        }
    }
}


void Canvas::DrawSensor(wxClientDC &dc, const DataArray &array)
{
    dc.SetPen(wxPen(wxColor(0, 0, 255)));

    auto point = array.array.end() - 1;

    int width = GetClientSize().GetWidth();
    int height = GetClientSize().GetHeight();

    float min = array.Min(width);
    float max = array.Max(width);

    if (fabsf(min - max) < 0.0001f)
    {
        return;
    }

    float scale = ((float)height - 20.0f) / (max - min);

    int x = width;

    int prev_y = -100;

    do
    {
        int y = (int)((point->value - min) * scale + 10.0f);

        if (prev_y == -100)
        {
            dc.DrawPoint({ x, y });
        }
        else
        {
            dc.DrawLine(x, y, x, prev_y);
        }

        prev_y = y;

        point--;
        x--;

    } while (point > array.array.begin());
}
