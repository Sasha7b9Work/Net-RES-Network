// 2022/02/21 15:41:29 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "main.h"
#include "Modules/BH1750/BH1750.h"
#include "Hardware/I2C/i2c.h"
#include <stm32f1xx_hal.h>


namespace BH1750
{
    static const uint8 CMD_POWER_ON   = 0x01;
    static const uint8 CMD_RESET      = 0x03;
    static const uint8 CMD_H_RES_MODE = 0x10;

    uint timeNext = 1;

    bool WriteUINT8(uint8);

    bool ReadUINT16(uint8 *);
}


void BH1750::Init()
{
    WriteUINT8(CMD_POWER_ON);
    WriteUINT8(CMD_RESET);
    WriteUINT8(CMD_H_RES_MODE);
}


pchar BH1750::GetMeasure(unsigned int dT)
{
    static char buffer[1024];

    if (HAL_GetTick() < timeNext)
    {
        return nullptr;
    }

    timeNext += dT;

    BitSet32 result;

    if (!ReadUINT16(&result.byte[0]))
    {
        sprintf(buffer, "BH1750 : !!! Error communication");
    }
    else
    {
        sprintf(buffer, "BH170 : %f lx", (float)(result.byte[1] | (result.byte[0] << 8)) / 1.2f);
    }

    return buffer;
}


bool BH1750::WriteUINT8(uint8 byte)
{
    return user_i2c_write8(0x23, byte) == 0;
}


bool BH1750::ReadUINT16(uint8 *buffer)
{
    return user_i2c_read16(0x23, buffer) == 0;
}
