// 2022/04/29 16:44:45 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Data/Sensors.h"
#pragma warning(push, 0)
#include <wx/wx.h>
#pragma warning(pop)


namespace Display
{
    void SwitchMeasure(TypeMeasure::E);

    void Reset();
}
