// 2022/02/21 15:41:29 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "main.h"
#include "Modules/BH1750/BH1750.h"
#include "Hardware/I2C/i2c.h"
#include <stm32f1xx_hal.h>


namespace BH1750
{
    static uint timeNext = 1;
}


pchar BH1750::GetMeasure(unsigned int dT)
{
    static char buffer[1024];

    while (HAL_GetTick() < timeNext)
    {
    }

    timeNext += dT;

    if (user_i2c_write8(0x23, 0x01) != 0)
    {
        sprintf(buffer, "BH1750 : !!! Error communication");
    }

    if (user_i2c_write8(0x23, 0x10) != 0)
    {
        sprintf(buffer, "BH1750 : !!! Error communication");
    }

    HAL_Delay(200);

    uint16 result = 0;

    if (user_i2c_read16(0x23, &result) != 0)
    {
        sprintf(buffer, "BH1750 : !!! Error communication");
    }
    else
    {
        sprintf(buffer, "BH170 : %f lx", result / 1.2f);
    }

    return buffer;
}
