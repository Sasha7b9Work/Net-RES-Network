// 2022/8/3 15:35:11 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


struct Symbol22
{
    uint8 width;
    int16 words[12];
};


// Ўрифт макимальными размерам 2х2 байта
struct Font22
{
    int height;
    int width;

    Symbol22 symbol[256];
};
