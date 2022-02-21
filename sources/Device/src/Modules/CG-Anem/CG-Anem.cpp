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


pchar CG_Anem::GetMeasure(unsigned int dT)
{
    static char buffer[1024];

    while (HAL_GetTick() < timeNext)
    {
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
        sprintf(buffer, "CG-Anem : velocity:%0.2f m/s, t:%0.2f *C",
            (float)velocity.half_word[0] * 0.1,
            (float)temp_cold.half_word[0] * 0.1);
    }
    else
    {
        sprintf(buffer, "CG-Anem : !!! Error communication");
    }

    return buffer;
}
