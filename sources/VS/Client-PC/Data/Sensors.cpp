// 2022/08/24 14:56:17 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Data/Sensors.h"
#include "Display/Grid/Grid.h"
#include "Display/Diagram/Diagram.h"
#include <map>
#include <vector>


using namespace std;


map<uint, Sensor> Sensor::Pool::pool;


void Sensor::Pool::AppendMeasure(uint id, uint8 type, float value)
{
    auto sensor = pool.find(id);

    if (sensor == pool.end())
    {
        pool.insert(pair<uint, Sensor>(id, Sensor(id)));
    }

    pool.find(id)->second.AppendMeasure(type, value);

    Grid::self->SetMeasure(id, type, value);

    DiagramPool::self->NeedRefresh((TypeMeasure::E)type);
}


void Sensor::AppendMeasure(uint8 type, float value)
{
    if (type < TypeMeasure::Count)
    {
        measures[type].push_back(value);
    }
    else
    {
        LOG_ERROR_TRACE("Bad type measure %d", type);
    }
}
