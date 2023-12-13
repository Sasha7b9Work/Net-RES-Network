// 2023/09/08 11:47:04 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Storage/Storage.h"


/*
*   В первых двух секторах хранится служебная информация
*/


namespace Storage
{
    struct DataInfo
    {
        uint address_first;     // адрес первой записи
        uint address_last;      // адрес последней записи
    };

    static Measure measures[NUM_MEASURES_TO_CONTROL];
}


void Storage::Init()
{
    for (int i = 0; i < NUM_MEASURES_TO_CONTROL; i++)
    {
        measures[i].Set((Measure::E)i, ERROR_VALUE_FLOAT);
        measures[i].correct = false;
    }
}


void Storage::AppendMeasure(const Measure &measure)
{
    if (measure.GetName() < NUM_MEASURES_TO_CONTROL)
    {
        if (measure.correct)
        {
            measures[measure.GetName()] = measure;
        }
    }
}


void Storage::Update()
{

}


bool Storage::GetMeasure(Measure::E name, Measure &measure)
{
    if (((int)name) >= 0 && name < NUM_MEASURES_TO_CONTROL)
    {
        measure = measures[name];

        return measure.correct;
    }

    return false;
}
