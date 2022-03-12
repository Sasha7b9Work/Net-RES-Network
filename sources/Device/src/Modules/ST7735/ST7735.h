// 2022/03/12 09:24:36 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Modules/ST7735/Colors.h"


namespace ST7735
{
    void Init();
    void Update();

    void BeginScene(Color);
    void EndScene();
}
