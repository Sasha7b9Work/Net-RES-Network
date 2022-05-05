// 2022/04/29 16:45:45 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "Display/Display.h"
#include "Display/Colors.h"
#include "Frame.h"
#include "Hardware/Timer.h"
#include "Utils/Text/String.h"
#include "Display/Font.h"


namespace Display
{
    struct Measure
    {
        bool show;
        bool valid;
        float value;

        Measure() : show(true), valid(false), value(1.0f) {}
    };

    Measure measures[TypeMeasure::Count];

    // Çäåñü íàğèñîâàííàÿ êàğòèíêà
    wxBitmap bitmap(Display::WIDTH, Display::HEIGHT);

    // Çäåñü áóäåì ğèñîâàòü
    wxMemoryDC memDC;

    wxPen pen = *wxWHITE_PEN;
    wxBrush brush = *wxWHITE_BRUSH;

    void BeginScene(Color);

    void EndScene();
}


void Display::Update()
{
    TimeMeterMS meter_fps;

    BeginScene(Color::BLACK);

    int x0 = 10;
    int dX = 250;
    int y0 = 15;
    int dY = 30;

    Font::SetSize(13);

    COLOR_1.SetAsCurrent();

    if (measures[TypeMeasure::Pressure].show)
    {
        String<>("ÄÀÂËÅÍÈÅ :").Draw(x0, y0);     String<>("ÌÏà").Draw(x0 + dX, y0);
    }

    if (measures[TypeMeasure::Illumination].show)
    {
        String<>("ÎÑÂÅÙÅÍÍÎÑÒÜ :").Draw(x0, y0 + dY);       String<>("ëê").Draw(x0 + dX, y0 + dY);
    }

    if (measures[TypeMeasure::Humidity].show)
    {
        String<>("ÂËÀÆÍÎÑÒÜ :").Draw(x0, y0 + 4 * dY);      String<>("%%").Draw(x0 + dX, y0 + 4 * dY);
    }

    if (measures[TypeMeasure::Velocity].show)
    {
        String<>("ÑÊÎĞÎÑÒÜ :").Draw(x0, y0 + 2 * dY);       String<>("ì/ñ").Draw(x0 + dX, y0 + 2 * dY);
    }

    if (measures[TypeMeasure::Temperature].show)
    {
        String<>("ÒÅÌÏÅĞÀÒÓĞÀ :").Draw(x0, y0 + 3 * dY);    String<>("¨Ñ").Draw(x0 + dX, y0 + 3 * dY);
    }

//    DrawMeasures();

//    DrawZones();

//    zoneFPS.string.SetFormat("%02d ms", meter_fps.ElapsedTime());

    EndScene();
}


void Display::BeginScene(Color color)
{
    memDC.SelectObject(bitmap);

    color.SetAsCurrent();

    memDC.DrawRectangle(0, 0, WIDTH, HEIGHT);
}


void Display::EndScene()
{
    memDC.SelectObject(wxNullBitmap);

    if (Frame::Self())
    {
        Frame::Self()->Refresh();
    }
}


void Display::SetMeasure(TypeMeasure::E type, float value)
{
    measures[type].valid = true;
    measures[type].value = value;
}


void Display::SwitchMeasure(TypeMeasure::E type)
{
    measures[type].show = !measures[type].show;
}
