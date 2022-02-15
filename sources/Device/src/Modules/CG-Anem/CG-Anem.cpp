// 2022/02/14 11:59:20 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "main.h"
#include "Modules/CG-Anem/CG-Anem.h"
#include "Hardware/I2C/i2c.h"
#include <stm32f1xx_hal.h>
#include <stdlib.h>


namespace CG_Anem
{
    static unsigned int timeNext = 1;
}


void CG_Anem::Init()
{

}


const char *CG_Anem::GetMeasure(unsigned int dT)
{
    static char buffer[1024];

    while (HAL_GetTick() < timeNext)
    {
    }

    timeNext += dT;

    uint8 id;
    user_i2c_read(0x11, 0x05, &id, 1);

    uint8 input_voltage = 0;
    user_i2c_read(0x11, 0x0d, &input_voltage, 1);

    BitSet32 adc_cold;
    user_i2c_read(0x11, 0x09, (uint8 *)&adc_cold.byte[1], 1);
    user_i2c_read(0x11, 0x0a, (uint8 *)&adc_cold.byte[0], 1);

    BitSet32 temp_cold;
    user_i2c_read(0x11, 0x10, &temp_cold.byte[1], 1);
    user_i2c_read(0x11, 0x11, &temp_cold.byte[0], 1);

    BitSet32 temp_hot;
    user_i2c_read(0x11, 0x12, &temp_hot.byte[1], 1);
    user_i2c_read(0x11, 0x13, &temp_hot.byte[0], 1);

    BitSet32 deltaT;
    user_i2c_read(0x11, 0x14, &deltaT.byte[1], 1);
    user_i2c_read(0x11, 0x15, &deltaT.byte[0], 1);

    uint8 status;
    user_i2c_read(0x11, 0x06, &status, 1);

    BitSet32 velocity;
    user_i2c_read(0x11, 0x07, &velocity.byte[1], 1);
    user_i2c_read(0x11, 0x08, &velocity.byte[0], 1);

//    sprintf(buffer, "CG-Anem : id:0x%X, status:0x%X, velocity:%f m/s, in_voltage:%f V, adc_cold:%d, cold_T:%f *C, hot_T:%f *C, dT:%f*C",
//        id,
//        status,
//        (float)velocity.half_word[0] * 0.1,
//        (float)input_voltage * 0.1,
//        adc_cold.half_word[0],
//
//        (float)temp_cold.half_word[0] * 0.1,
//        (float)temp_hot.half_word[0] * 0.1,
//        (float)deltaT.half_word[0] * 0.1);

    sprintf(buffer, "CG-Anem : velocity:%0.2f m/s, t:%0.2f *C",
        (float)velocity.half_word[0] * 0.1,
        (float)temp_cold.half_word[0] * 0.1);

    return buffer;
}
