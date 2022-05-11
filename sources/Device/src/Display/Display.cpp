// 2022/04/20 08:53:20 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Display/Display.h"
#include "Hardware/Timer.h"
#include "Display/Colors.h"
#include "Modules/ST7735/ST7735.h"
#include "Display/Font/Font.h"
#include "Utils/Text/String.h"
#include "Utils/Text/Text.h"
#include "Display/Zones.h"
#include "Menu/Menu.h"
#include "Settings/Settings.h"
#include <cstdlib>


namespace Display
{
    bool need_redraw = true;

    uint time_prev_redraw = 0;

    static ZoneFPS zoneFPS;

    static Zone *zones[] =
    {
        &zoneFPS,
        nullptr
    };

    static void DrawZones();

    struct Measure
    {
        String<> old;
        String<> current;

        float value;                // Последнее установленное значение
        int position;               // Текущая отрисовываемая позиция
        uint time;                  // Время последнего изменения текущей отрисовываемой позиции

        Measure() : value(0.0f), position(0), time(0) {}

        void Draw(const int x, const int y, int size = 1);
    };

    static Measure measures[TypeMeasure::Count];

    static void DrawMeasures();

    // Вывести одно измерение на весь экран
    static void DrawBigMeasure();

    namespace Buffer
    {
        static uint8 buffer[WIDTH * HEIGHT / 2];       // Четырёхбитный цвет

        uint8 GetPixels(int x, int y)
        {
            return buffer[(y * WIDTH + x) / 2];
        }

        uint8* GetLine(int x, int y)
        {
            return &buffer[(y * WIDTH + x) / 2];
        }

        static void SetPoint(int x, int y)
        {
            if (x < 0) { return; }
            if (y < 0) { return; }
            if (x >= WIDTH) { return; }
            if (y >= HEIGHT) { return; }

            uint8* pixels = &buffer[(y * WIDTH + x) / 2];

            uint8 value = *pixels;

            if (x & 0x1)
            {
                value &= 0x0F;
                value |= (Color::GetCurrent() << 4);
            }
            else
            {
                value &= 0xF0;
                value |= Color::GetCurrent();
            }

            *pixels = value;
        }

        static void Fill(Color::E color)
        {
            uint8 value = (uint8)((int)(color) | (int)(color << 4));

            std::memset(buffer, value, WIDTH * HEIGHT / 2);
        }
    }
}


void HLine::Draw(int x0, int y, Color::E color)
{
    Color::SetCurrent(color);

    for (int x = x0; x < x0 + width; x++)
    {
        Display::Buffer::SetPoint(x, y);
    }
}


void VLine::Draw(int x, int y0, Color::E color)
{
    Color::SetCurrent(color);

    for (int y = y0; y < y0 + height; y++)
    {
        Display::Buffer::SetPoint(x, y);
    }
}


void Point::Set(int x, int y, Color::E color)
{
    Color::SetCurrent(color);

    Display::Buffer::SetPoint(x, y);
}


void Rectangle::Fill(int x0, int y0, Color::E color)
{
    Color::SetCurrent(color);

    for (int x = x0; x < x0 + width; x++)
    {
        VLine(height).Draw(x, y0);
    }
}


void Rectangle::DrawFilled(int x, int y, Color::E fill, Color::E draw)
{
    Rectangle(width, height).Draw(x, y, draw);

    Rectangle(width - 2, height - 2).Fill(x + 1, y + 1, fill);
}


void Rectangle::Draw(int x, int y, Color::E color)
{
    HLine(width).Draw(x, y, color);
    HLine(width).Draw(x, y + height);
    VLine(height).Draw(x, y);
    VLine(height).Draw(x + width, y);
}


void Display::SetMeasure(TypeMeasure::E type, float value)
{
    Measure &measure = measures[type];

    if (value == measure.value)
    {
        return;
    };

    measure.old.SetFormat(measure.current.c_str());

    measure.position = 0;
    measure.time = TIME_MS;
    measure.value = value;

    measure.current.SetFormat("%f", value);
    measure.current[6] = '\0';
}


void Display::DrawMeasures()
{
    int y0 = 15;
    int dY = 22;

    for (int i = 0; i < TypeMeasure::Count; i++)
    {
        if (gset.display.show_measure[i])
        {
            measures[i].Draw(100, y0 + i * dY);
        }
    }
}


void Display::Measure::Draw(const int x0, const int y0, int size)
{
    Rectangle(30, 7).Fill(x0, y0 + 1, Color::BLACK);

    Color::SetCurrent(Color::GREEN);

    if (position >= current.Size())
    {
        current.Draw(x0, y0);
    }
    else
    {
        int x = x0;

        for (int i = 0; i < position; i++)
        {
            x = Char(current[i]).Draw(x, y0) + 1;
        }

        Rectangle(5, 7).Fill(x, y0 + 1, Color::WHITE);

        for (int i = position; i < old.Size(); i++)
        {
            x = Char(old[i]).Draw(x, y0, Color::GREEN) + 1;
        }

        if (TIME_MS > time + 25)
        {
            position++;
            time = TIME_MS;
        }
    }

    ST7735::WriteBuffer(x0, y0 + 1, 30, 7);
}


void Display::DrawZones()
{
    for (int i = 0; true; i++)
    {
        Zone *zone = zones[i];

        if (zone == nullptr)
        {
            break;
        }

        zone->Draw();
    }
}


void Display::BeginScene(Color::E color)
{
    Buffer::Fill(color);
}


void Display::EndScene()
{
    ST7735::WriteBuffer(0, 0, WIDTH, HEIGHT);
}


void Display::Update()
{
    TimeMeterMS meter_fps;

    if (Menu::Opened())
    {
        Menu::Draw();

        need_redraw = true;
    }
    else
    {
        if (gset.display.typeDisplaydInfo.value == TypeDisplayedInformation::AllMeasures)
        {
            if (need_redraw)
            {
                BeginScene(Color::BLACK);

                int x0 = 10;
                int dX = 125;
                int y0 = 15;
                int dY = 22;

                if (gset.display.show_measure[TypeMeasure::Pressure])
                {
                    String<>("%s :", TypeMeasure::Name(TypeMeasure::Pressure)).Draw(x0, y0, Color::_1);
                    String<>(TypeMeasure::Units(TypeMeasure::Pressure)).Draw(x0 + dX, y0);
                }

                if (gset.display.show_measure[TypeMeasure::Illumination])
                {
                    String<>("%s :", TypeMeasure::Name(TypeMeasure::Illumination)).Draw(x0, y0 + dY);
                    String<>(TypeMeasure::Units(TypeMeasure::Illumination)).Draw(x0 + dX, y0 + dY);
                }

                if (gset.display.show_measure[TypeMeasure::Humidity])
                {
                    String<>("%s :", TypeMeasure::Name(TypeMeasure::Humidity)).Draw(x0, y0 + 4 * dY);
                    String<>(TypeMeasure::Units(TypeMeasure::Humidity)).Draw(x0 + dX, y0 + 4 * dY);
                }

                if (gset.display.show_measure[TypeMeasure::Velocity])
                {
                    String<>("%s :", TypeMeasure::Name(TypeMeasure::Velocity)).Draw(x0, y0 + 2 * dY);
                    String<>(TypeMeasure::Units(TypeMeasure::Velocity)).Draw(x0 + dX, y0 + 2 * dY);
                }

                if (gset.display.show_measure[TypeMeasure::Temperature])
                {
                    String<>("%s :", TypeMeasure::Name(TypeMeasure::Temperature)).Draw(x0, y0 + 3 * dY);
                    String<>(TypeMeasure::Units(TypeMeasure::Temperature)).Draw(x0 + dX, y0 + 3 * dY);
                }

                EndScene();

                need_redraw = false;
            }

            DrawMeasures();

            DrawZones();
        }
        else
        {
            DrawBigMeasure();
        }

        zoneFPS.string.SetFormat("%02d ms", meter_fps.ElapsedTime());
    }
}


void Display::DrawBigMeasure()
{
    BeginScene(Color::BLACK);

    Color::SetCurrent(Color::_1);

    TypeMeasure::E measure = (TypeMeasure::E)gset.display.typeDisplaydInfo.value;

    Text::DrawBig(10, 30, 2, TypeMeasure::Name(measure));

    measures[measure].Draw(100, 100);

    EndScene();
}


pchar TypeMeasure::Name(E value)
{
    static const pchar names[Count] =
    {
        "ДАВЛЕНИЕ",
        "ОСВЕЩЕННОСТЬ",
        "СКОРОСТЬ",
        "ТЕМПЕРАТУРА",
        "ВЛАЖНОСТЬ"
    };

    return names[value];
}

pchar TypeMeasure::Units(E value)
{
    static const pchar units[Count] =
    {
        "МПа",
        "лк",
        "м/с",
        "ЁС",
        "%%"
    };

    return units[value];
}
