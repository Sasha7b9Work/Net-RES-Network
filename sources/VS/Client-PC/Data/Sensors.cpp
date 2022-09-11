// 2022/08/24 14:56:17 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Data/Sensors.h"
#include "Display/Grid/Grid.h"


void PoolSensors::AppendMeasure(uint id, uint8 type, float value)
{
    Grid::Self()->SetID(id);

    Grid::Self()->SetParameter(type, value);
}