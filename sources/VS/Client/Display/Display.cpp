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

    void DrawMeasure(TypeMeasure::E);
}


pchar TypeMeasure::GetTitle(TypeMeasure::E type)
{
    static const pchar titles[Count] =
    {
        "ÄÀÂËÅÍÈÅ",
        "ÎÑÂÅÙÅÍÍÎÑÒÜ",
        "ÑÊÎĞÎÑÒÜ",
        "ÒÅÌÏÅĞÀÒÓĞÀ",
        "ÂËÀÆÍÎÑÒÜ"
    };

    return titles[type];
}


pchar TypeMeasure::GetUnits(TypeMeasure::E type)
{
    static const pchar units[Count] =
    {
        "ÌÏà",
        "ëê",
        "ì/ñ",
        "Ö",
        "%%"
    };

    return units[type];
}


void Display::Update()
{
    BeginScene(Color::BLACK);

    for (int i = 0; i < TypeMeasure::Count; i++)
    {
        DrawMeasure((TypeMeasure::E)i);
    }

    EndScene();
}


void Display::DrawMeasure(TypeMeasure::E type)
{
    if (!measures[type].show)
    {
        return;
    }

    Font::SetSize(13);

    int x0 = 10;
    int dX = 250;
    int y0 = 15;
    int dY = 30;

    int y = y0 + dY * type;

    String<>(TypeMeasure::GetTitle(type)).Draw(x0, y, COLOR_1);

    String<>(TypeMeasure::GetUnits(type)).Draw(x0 + dX, y);

    if (measures[type].valid)
    {
        String<>("%.4f", measures[type].value).Draw(x0 + dX - 90, y, Color::WHITE);
    }
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
