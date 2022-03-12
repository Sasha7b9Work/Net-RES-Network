// 2022/03/12 09:24:36 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Modules/ST7735/Colors.h"


namespace Display
{
    static const int WIDTH = 160;
    static const int HEIGHT = 128;

    void Init();
    void Update();

    void BeginScene(Color);
}


struct Rectangle
{
    int width;
    int height;

    Rectangle(int w, int h) : width(w), height(h) { }

    void Fill(int x, int y, Color);
};
