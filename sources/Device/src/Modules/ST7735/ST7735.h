// 2022/03/12 09:24:36 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Display/Colors.h"


namespace Display
{
    void Init();

    void BeginScene(Color::E);

    void EndScene();

    void SetMeasure(pchar measure);
}

