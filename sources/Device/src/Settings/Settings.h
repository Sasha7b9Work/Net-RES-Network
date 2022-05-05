// 2022/05/05 15:22:56 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Display/Display.h"



struct SettingsDisplay
{
    uint8 show_measure[TypeMeasure::Count];
};



struct Settings
{
    SettingsDisplay display;
};


extern Settings gset;
