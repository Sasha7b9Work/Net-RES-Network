// Sasha7b9@tut.by (c)
#include "main.h"
#include "Display/Display.h"
#include "Hardware/Timer.h"
#include "Display/Colors.h"
#include "Modules/ST7735/ST7735.h"
#include "Display/Font/Font.h"
#include "Utils/Text/String.h"
#include <cstdlib>


namespace Display
{
    namespace Buffer
    {
        static uint8 buffer[WIDTH * HEIGHT / 2];       // Четырёхбитный цвет

        static uint8* FirstPixels()
        {
            return &buffer[0];
        }

        static void SetPoint(int x, int y)
        {
            if (x < 0) { return; }
            if (y < 0) { return; }
            if (x >= WIDTH) { return; }
            if (y >= HEIGHT) { return; }

            uint8* pixels = &buffer[(y * WIDTH + x) / 2];

            uint8 value = *pixels;

            if (x % 2)
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


void Display::Update()
{
    TimeMeterMS meter;
    static uint time = 0;

    Color::E color2 = Color::WHITE;
    Color::E color1 = Color::BLACK;

    BeginScene(Color::GRAY_25);

    Rectangle(140, 30).Fill(10, 5, Color::BLUE);

    static int y0 = 40;

    HLine(20).Draw(5, y0, color2);

    y0++;

    if (y0 == HEIGHT)
    {
        y0 = 40;
    }

    Font::Set(TypeFont::_8);

    String<>("Тестовая строка").Draw(40, 10, color1);

    int y = 45;
    int x = 30;
    int dY = 15;

    String<>("Давление : 100 МПa").Draw(x, y, Color::GREEN);
    String<>("Освещённость : 100 люкс").Draw(x, y + dY);
    String<>("Скорость : 10 км/сек").Draw(x, y + 2 * dY);
    String<>("Температура : 23 С").Draw(x, y + 3 * dY);
    String<>("Влажность : 100%%").Draw(x, y + 4 * dY);

    String<>("%d ms", time).Draw(125, 25, color1);

    EndScene();

    time = meter.ElapsedTime();
}


void Display::BeginScene(Color::E color)
{
    Buffer::Fill(color);
}


void Display::EndScene()
{
    ST7735::WriteData(Buffer::FirstPixels());
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


void Rectangle::Draw(int x, int y, Color::E color)
{
    HLine(width).Draw(x, y, color);
    HLine(width).Draw(x, y + height);
    VLine(height).Draw(x, y);
    VLine(height).Draw(x + width, y);
}


void Display::SetMeasure(TypeMeasure::E, pchar)
{

}
