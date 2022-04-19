// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "Modules/HC12/HC12.h"
#include "Hardware/HAL/HAL.h"
#include "Modules/BME280/BME280.h"
#include "Modules/CG-Anem/CG-Anem.h"
#include "Modules/BH1750/BH1750.h"
#include "Hardware/CDC/CDC.h"
#include "Modules/ST7735/ST7735.h"
#include "Hardware/Timer.h"
#include "Hardware/InterCom.h"
#include "Display/Display.h"


int main(void)
{
    HAL::Init();

    ST7735::Init();

    BME280::Init();

    HC12::Init();

    CG_Anem::Init();

    BH1750::Init();

    InterCom::SetDirection((Direction::E)(Direction::CDC | Direction::HC12 | Direction::Display));

    while (1)
    {
        pchar measure = BME280::GetMeasure(1000);           // Температура, давление, влажность

        InterCom::Send(measure);

        measure = CG_Anem::GetMeasure(1000);                // Скорость

        InterCom::Send(measure);

        measure = BH1750::GetMeasure(1000);                 // Освещённость

        InterCom::Send(measure);

        Display::Update();
   }
}
