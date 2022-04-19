// 2022/02/14 11:59:20 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "main.h"
#include "Modules/CG-Anem/CG-Anem.h"
#include "Hardware/I2C/i2c.h"
#include <stm32f1xx_hal.h>
#include <stdlib.h>
#include <string.h>


namespace CG_Anem
{
    static unsigned int timeNext = 1;
}


void CG_Anem::Init()
{

}


bool CG_Anem::GetMeasure(unsigned int dT, float *velocity_out)
{
    if (HAL_GetTick() < timeNext)
    {
        return false;
    }

    timeNext += dT;

    bool result = true;

    BitSet32 temp_cold;

    if (user_i2c_read(0x11, 0x10, &temp_cold.byte[1], 1) != 0)
    {
        result = false;
    }

    if (user_i2c_read(0x11, 0x11, &temp_cold.byte[0], 1) != 0)
    {
        result = false;
    }

    BitSet32 velocity;
    
    if (user_i2c_read(0x11, 0x07, &velocity.byte[1], 1) != 0)
    {
        result = false;
    }

    if (user_i2c_read(0x11, 0x08, &velocity.byte[0], 1) != 0)
    {
        result = false;
    }

    if (result)
    {
        *velocity_out = velocity.half_word[0] * 0.1f;
    }

    return result;
}
