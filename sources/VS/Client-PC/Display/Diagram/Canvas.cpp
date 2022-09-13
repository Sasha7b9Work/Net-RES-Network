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
    wxBitmap bitmap(GetClientSize());
    wxMemoryDC memDC;

    memDC.SelectObject(bitmap);

    memDC.SetBrush(*wxWHITE_BRUSH);
    memDC.SetPen(wxPen(wxColor(0, 0, 0)));

    memDC.DrawRectangle(GetClientRect());

    DrawTimeScale(memDC);

    DrawAllSensors(memDC);

    memDC.SetPen(wxPen(wxColor(0, 0, 0)));

    static const wxString labels[TypeMeasure::Count] =
    {
        "Давление",
        "Освещённость",
        "Температура",
        "Влажность",
        "Скорость"
    };

    memDC.DrawText(labels[type], 1, 0);

    memDC.SelectObject(wxNullBitmap);

    wxPaintDC dc(this);

    dc.DrawBitmap(bitmap, 0, 0);

    Update();
}


void Canvas::DrawTimeScale(wxMemoryDC &dc)
{
    int dx = 60;

    Time time = Clock::CurrentTime();

    int x = GetClientSize().GetWidth() - time.sec % dx;

    time.sec = 0;

    int y = GetClientSize().GetHeight();

    dc.SetPen(wxPen(wxColor(200, 200, 200)));

    while (x > 0)
    {
        dc.DrawLine(x, 0, x, y);

        dc.DrawText(time.ToString().c_str(), { x + 1, y - 15 });

        time.SubMin(1);

        x -= dx;
    }
}


int Canvas::TimeToX(const Time &time)
{
    int width = GetClientSize().GetWidth();

    Time current_time = Clock::CurrentTime();

    return width - (current_time - time).ToSec();
}


void Canvas::SetSizeArea(int width, int height)
{
    SetMinClientSize({ width, height } );
    SetClientSize({ width, height });
}


void Canvas::DrawAllSensors(wxMemoryDC &dc)
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

        if (measures.Size() > 1)
        {
            DrawSensor(dc, measures);
        }
    }
}


void Canvas::DrawSensor(wxMemoryDC &dc, const DataArray &array)
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

    do
    {
        int x_end = TimeToX(point->time);
        int x_start = TimeToX((point - 1)->time);

        int y_end = height - 10 - (int)((point->value - min) * scale);
        int y_start = height - 10 - (int)(((point - 1)->value - min) * scale);

        dc.DrawLine({ x_start, y_start }, { x_end, y_end });

    } while (point > array.array.begin());

    dc.SetPen(wxPen(wxColor(0, 0, 0)));

    DrawTextOnBackground(dc, wxString::Format("%10.2f", max).c_str(), width - 50, 0, 50, 15);
    DrawTextOnBackground(dc, wxString::Format("%10.2f", min).c_str(), width - 50, height - 30, 50, 15);
}


void Canvas::DrawTextOnBackground(wxMemoryDC &dc, pchar text, int x, int y, int width, int height)
{
    dc.DrawRectangle({ x, y }, { width, height });
    dc.DrawText(text, { x + 1, y + 1 });
}
