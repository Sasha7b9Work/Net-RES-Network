// 2022/03/12 09:24:36 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Modules/ST7735/Colors.h"


namespace Display
{
    static const int WIDTH = 160;
    static const int HEIGHT = 128;

    void Init();

    void Update();

    void BeginScene(Color::E);

    void EndScene();

    void SetMeasure(pchar measure);
}


struct Rectangle
{
    Rectangle(int w, int h) : width(w), height(h) { }

    void Fill(int x, int y, Color::E = Color::Count);

    void Draw(int x, int y, Color::E = Color::Count);

private:

    int width;
    int height;
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
