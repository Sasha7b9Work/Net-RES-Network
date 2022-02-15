// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "Modules/HC12/HC12.h"
#include "Hardware/HAL/HAL.h"
#include "Modules/BME280/BME280.h"
#include "Modules/CG-Anem/CG-Anem.h"
#include "Hardware/CDC/CDC.h"


int main(void)
{
    HAL::Init();

    BME280::Init();

//    HC12::Init();

    CG_Anem::Init();

    while (1)
    {
        const char *measure = BME280::GetMeasure(1000);

        CDC::Transmit(measure);

//        HC12::Transmit(measure);

//        measure = CG_Anem::GetMeasure(1000);
//
//        CDC::Transmit(measure);
//
//        HC12::Transmit(measure);
    }
}
