// 2022/02/14 11:59:20 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "main.h"
#include "Modules/CG-Anem/CG-Anem.h"
#include <stm32f1xx_hal.h>


namespace CG_Anem
{
    static unsigned int timeNext = 1;
}


void CG_Anem::Init()
{

}


const char *CG_Anem::GetMeasure(unsigned int dT)
{
    static char buffer[128];

    while (HAL_GetTick() < timeNext)
    {
    }

    timeNext += dT;

    return buffer;
}
