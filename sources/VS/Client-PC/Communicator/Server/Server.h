// 2024/04/29 08:36:43 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Data/Sensors.h"


// —юда будем посылать измерени€
namespace ServerMeasures
{
    void Init();

    void Update();

    void Send(TypeMeasure::E, float value);

    void CallbackOnSocketEvent(wxSocketEvent &);
}
