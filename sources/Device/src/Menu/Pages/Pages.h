// 2022/05/05 12:27:08 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Menu/MenuItems.h"


struct PageMain
{
    static const Page *self;
};


struct PageDisplay
{
    static const Page *self;

    struct PageMeasures
    {
        static const Page *self;
    };
};


struct PageHC12
{
    static const Page *self;
};
