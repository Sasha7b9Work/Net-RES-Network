// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "defines.h"


namespace BME280
{
    void Init();

    bool GetMeasures(unsigned int dT, float *temp, float *pressure, float *humidity);
}
