// 2022/04/20 08:53:49 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Display/Colors.h"
#include "Utils/Text/String.h"
#include "Storage/Measures.h"


namespace Display
{
    static const int WIDTH = 160;
    const int HEIGHT = 128;

    // Столько измерений помещается на одном экране
    static const int MEAS_ON_DISPLAY = 5;

    extern bool need_redraw;

    void SetMeasure(const Measure &, uint timeMS);

    void Update(uint timeMS);

    void BeginScene(Color::E);

    void EndScene();

    namespace Buffer
    {
        // Возвращает указатель на строку
        uint8 *GetLine(int x, int y);
    }

    namespace Mode
    {
        // Включить/отключть режим отображения компаса
        void EnableCompass(bool enable);

        bool IsEnabledCompass();
    }
}


struct Rectangle
{
    Rectangle(int w, int h) : width(w), height(h) { }

    void Fill(int x, int y, Color::E = Color::Count);

    void Draw(int x, int y, Color::E = Color::Count);

    void DrawFilled(int x, int y, Color::E fill, Color::E draw);

private:

    int width;
    int height;
};


struct Line
{
    void Draw(int x1, int y1, int x2, int y2, Color::E = Color::Count);
};


struct HLine
{
    HLine(int w) : width(w) {}

    void Draw(int x, int y, Color::E = Color::Count);

private:

    int width;
};


struct VLine
{
    VLine(int h) : height(h) {}

    void Draw(int x, int y, Color::E = Color::Count);

private:

    int height;
};


struct Point
{
    void Set(int x, int y, Color::E color = Color::Count);
};


struct Circle
{
    Circle(int r) : radius(r) {}

    void Draw(int, int, Color::E = Color::Count);

private:

    int radius;
};
