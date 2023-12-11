// 2022/04/20 08:53:20 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Modules/ST7735/ST7735.h"
#include "Display/Font/Font.h"
#include "Utils/Text/String.h"
#include "Display/Zones.h"
#include "Menu/Menu.h"
#include "Settings/Settings.h"
#include "Storage/Measures.h"
#include "Hardware/Timer.h"
#include "Hardware/Beeper.h"


namespace Display
{
    struct DMeasure
    {
        String<> str_value;

        Measure::E name;
        Measure value;              // Последнее установленное значение
        int position;               // Текущая отрисовываемая позиция
        uint time;                  // Время последнего изменения текущей отрисовываемой позиции

        DMeasure(Measure::E n) : name(n), position(0), time(0) {}

        void Draw(const int x, const int y, int size = 1);

        String<> Name();

        String<> Units();
    };

    static DMeasure measures[Measure::Count] =
    {
        DMeasure(Measure::Temperature),
        DMeasure(Measure::Pressure),
        DMeasure(Measure::Humidity),
        DMeasure(Measure::DewPoint),
        DMeasure(Measure::Velocity),
        DMeasure(Measure::Latitude),
        DMeasure(Measure::Longitude),
        DMeasure(Measure::Altitude),
        DMeasure(Measure::Azimuth)
    };

    namespace Buffer
    {
        static uint8 buffer[WIDTH * HEIGHT / 2];       // Четырёхбитный цвет

        uint8 GetPixels(int x, int y)
        {
            return buffer[(y * WIDTH + x) / 2];
        }

        uint8 *GetLine(int x, int y)
        {
            return &buffer[(y * WIDTH + x) / 2];
        }

        static void SetPoint(int x, int y)
        {
            if (x < 0) { return; }
            if (y < 0) { return; }
            if (x >= WIDTH) { return; }
            if (y >= HEIGHT) { return; }

            uint8 *pixels = &buffer[(y * WIDTH + x) / 2];

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

        static void DrawHLine(int y, int x1, int x2)
        {
            if ((x1 % 2) == 0 && (x2 % 2) == 0)
            {
                uint8 *first_byte = &buffer[y * Display::WIDTH / 2 + x1 / 2];

                uint8 value = (uint8)((uint8)(Color::GetCurrent()) + (Color::GetCurrent() << 4));

                std::memset(first_byte, value, (uint)(x2 - x1) / 2U);
            }
            else
            {
                for (int x = x1; x < x2; x++)
                {
                    Display::Buffer::SetPoint(x, y);
                }
            }
        }

        static void Fill(Color::E color)
        {
            uint8 value = (uint8)((int)(color) | (int)(color << 4));

            std::memset(buffer, value, WIDTH * HEIGHT / 2);
        }
    }
}


namespace Display
{
    bool need_redraw = true;

    static bool mode_compass = false;        // Если true - рисуем компас

    static ZoneFPS zoneFPS;

    static Zone *zones[] =
    {
        &zoneFPS,
        nullptr
    };

    void DrawZones();

    static void DrawMeasures(uint timeMS);

    // Вывести одно измерение на весь экран
    static void DrawBigMeasure();

    static void DrawTime();

    static void DrawStar();

    // Какую страницу измерений сейчас выводить на экран. Т.к. все они одновременно на экран не помещаются,
    // то выводятся по пять штук на одном экране и автоматически переключаются.
    static int PageMeasures(uint timeMS);

    static void DrawCompass();
}


void HLine::Draw(int x0, int y, Color::E color)
{
    Color::SetCurrent(color);

    Display::Buffer::DrawHLine(y, x0, x0 + width);
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


void Circle::Draw(int _x, int _y, Color::E color)
{
    Color::SetCurrent(color);

    int x = radius;
    int y = 0;
    int radiusError = 1 - x;

    int dx = (_x - radius);
    int dy = (_y - radius);

    while (x >= y)
    {
        Display::Buffer::SetPoint(x + radius + dx, y + radius + dy);
        Display::Buffer::SetPoint(y + radius + dx, x + radius + dy);
        Display::Buffer::SetPoint(-x + radius + dx, y + radius + dy);
        Display::Buffer::SetPoint(-y + radius + dx, x + radius + dy);
        Display::Buffer::SetPoint(-x + radius + dx, -y + radius + dy);
        Display::Buffer::SetPoint(-y + radius + dx, -x + radius + dy);
        Display::Buffer::SetPoint(x + radius + dx, -y + radius + dy);
        Display::Buffer::SetPoint(y + radius + dx, -x + radius + dy);
        y++;
        if(radiusError < 0)
        {
            radiusError += 2 * y + 1;
        }
        else
        {
            x--;
            radiusError += 2 * (y - x) + 1;
        }
    }
}


void Rectangle::Draw(int x, int y, Color::E color)
{
    HLine(width).Draw(x, y, color);
    HLine(width).Draw(x, y + height - 1);
    VLine(height).Draw(x, y);
    VLine(height).Draw(x + width - 1, y);
}


void Display::SetMeasure(const Measure &measure, uint timeMS)
{
    DMeasure &value = measures[measure.GetName()];

    if (value.value.GetDouble() == measure.GetDouble()) //-V550
    {
        if (value.str_value.Size())
        {
            return;
        }
    }

    if (!Beeper::IsRunning())
    {
        Settings::SaveMeasure(measure);
    }

    value.position = 0;
    value.time = timeMS;
    value.value = measure;

    pchar format = "%.1f";

    if (value.name == Measure::Longitude || value.name == Measure::Latitude)
    {
        format = "%.7f";
    }

    value.str_value.SetFormat(format, (double)measure.GetDouble());
//    value.current[6] = '\0';
}


void Display::DMeasure::Draw(const int x0, const int y0, int size)
{
    int width_zone = 38;
    int height_zone = 12;
    int y_zone = y0;

    Rectangle(width_zone, height_zone).Fill(x0, y_zone, Color::BLACK);

    Font::Text::DrawBig(x0, y0, size, str_value.c_str(), Color::WHITE);
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
    DrawStar();

    ST7735::WriteBuffer(0, 0, WIDTH, HEIGHT);
}


void Display::Update(uint timeMS)
{
    if (mode_compass)
    {
        DrawCompass();
    }
    else
    {
        TimeMeterMS meter_fps;

        need_redraw = true;

        if (Menu::IsOpened())
        {
            Menu::Draw();

            need_redraw = true;
        }
        else
        {
            if (gset.display.typeDisplaydInfo.IsAllMeasures())
            {
                if (need_redraw)
                {
                    BeginScene(Color::BLACK);
                }

                DrawMeasures(timeMS);

                if (PageMeasures(timeMS) == 1)
                {
                    DrawTime();
                }

                if (need_redraw)
                {
                    EndScene();

                    need_redraw = false;
                }

                //DrawZones();
            }
            else
            {
                DrawBigMeasure();
            }

            zoneFPS.string.SetFormat("%02d ms", meter_fps.ElapsedTime());
        }
    }
}


void Display::DrawCompass()
{
    BeginScene(Color::BLACK);

    int x0 = Display::WIDTH / 2;
    int y0 = Display::HEIGHT / 2;

    Circle(62).Draw(x0, y0, Color::GRAY_50);

    Buffer::SetPoint(x0, y0);

    double x = measures[Measure::Azimuth].value.GetDouble();

    String<>("x=%.3f", x).Draw(0, 10, Color::WHITE);

    EndScene();
}


void Display::DrawMeasures(uint timeMS)
{
    Font::Set(TypeFont::_12_10);

    const int x0 = 3;

    // Пустое место между строками
    const int d_lines = (Display::HEIGHT - 5 * Font::Height()) / (5 + 1);

    const int y0 = d_lines;
    const int dY = d_lines + Font::Height();

    static const Measure::E names[Measure::Count] =
    {
        Measure::Temperature,
        Measure::Pressure,
        Measure::Humidity,
        Measure::DewPoint,
        Measure::Velocity,
        Measure::Latitude,
        Measure::Longitude,
        Measure::Altitude,
        Measure::Azimuth
    };

    int y = y0;

    int page = PageMeasures(timeMS);

    for (int i = page * MEAS_ON_DISPLAY; i < (page + 1) * MEAS_ON_DISPLAY; i++)
    {
        if (i < Measure::Count)
        {
            DMeasure &measure = measures[names[i]];

            if (need_redraw && measure.str_value.Size())
            {
                int x = (page == 0) ? 93 : 69;

                int width = 30;
                int height = 15;

                if (measure.name > Measure::Velocity)
                {
                    if (measure.value.GetDouble() < 10.0)
                    {
                        x += 14;
                    }
                    else if (measure.value.GetDouble() < 100.0)
                    {
                        x += 8;
                    }
                }

                String<>("%s", measure.Name().c_str()).Draw(x0, y, measure.value.InRange() ? Color::WHITE : Color::FLASH_10);
                measure.Units().Draw(((page == 0) ? 134 : 145), y, Color::WHITE);
                measure.Draw(x, y);

                ST7735::WriteBuffer(x - 1, y, width, height);
                y += dY;
            }
        }
    }
}


int Display::PageMeasures(uint timeMS)
{
    const int num_displays = Measure::Count / MEAS_ON_DISPLAY + 1;

    uint secs = timeMS / 1000U;

    uint secs_5 = secs / 5;

    return (int)(secs_5 % num_displays);
}


void Display::DrawTime()
{
    int width = 160;
    int height = 16;
    int y = 105;

    Font::Set(TypeFont::_12_10);

    Rectangle(width, height).Fill(4, y - 1, Color::BLACK);

    PackedTime time = HAL_RTC::GetTime();

    String<>("%02d:%02d:%02d", time.hours, time.minutes, time.seconds).Draw(5, 105, Color::WHITE);

    String<>("%02d:%02d:%04d", time.day, time.month, time.year + 2000).Draw(80, 105);

    ST7735::WriteBuffer(0, y, width, height);
}


void Display::DrawStar()
{
    if (((TIME_MS / 500) % 2) == 0)
    {
        String<>("*").Draw(156, 0, Color::WHITE);
    }
}


void Display::DrawBigMeasure()
{
    Font::Set(TypeFont::_8);

    BeginScene(Color::BLACK);

    static const int x[Measure::Count] =
    {
        30,
        12,
        28,
        10,
        10,
        10,
        10,
        10,
        10
    };

    DMeasure &measure = measures[gset.display.typeDisplaydInfo.value];

    Font::Text::DrawBig(x[measure.value.GetName()], 15, 2, measure.Name().c_str(), Color::_1);

    measures[measure.value.GetName()].Draw(27, 50, 4);

    Font::Text::DrawBig(68, 95, 2, measure.Units().c_str(), Color::_1);

    EndScene();
}


String<> Display::DMeasure::Name()
{
    static const pchar names[Measure::Count] =
    {
        "ТЕМПЕРАТУРА",
        "ДАВЛЕНИЕ",
        "ВЛАЖНОСТЬ",
        "ТОЧКА РОСЫ",
        "СКОРОСТЬ",
        "ШИРОТА",
        "ДОЛГОТА",
        "ВЫСОТА",
        "АЗИМУТ"
    };

    String<> result(names[name]);

    return result;
}

String<> Display::DMeasure::Units()
{
    static const pchar units[Measure::Count] =
    {
        "ЁС",
        "гПа",
        "%%",
        "ЁС",
        "м/с",
        "Ё",
        "Ё",
        "м",
        "Ё"
    };

    return String<>(units[name]);
}


void Display::Mode::EnableCompass(bool enable)
{
    mode_compass = enable;
}


bool Display::Mode::IsEnabledCompass()
{
    return mode_compass;
}
