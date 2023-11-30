// 2023/01/30 16:45:08 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Modules/GY511/GY511.h"
#include "Hardware/HAL/HAL.h"
#include <stm32f3xx_hal.h>


#define ADDR_ACCE   0x19
#define ADDR_MAGN   0x1F

#define GY511_CTRL_REG1     0x20U
#define GY511_CTRL_REG3     0x22U
#define GY511_CTRL_REG4     0x23U
#define GY511_STATUS_REG    0x27U

#define GY511_OUT_X_L_A     0x28U
#define GY511_OUT_X_H_A     0x29U
#define GY511_OUT_Y_L_A     0x2AU
#define GY511_OUT_Y_H_A     0x2BU
#define GY511_OUT_Z_L_A     0x2CU
#define GY511_OUT_Z_H_A     0x2DU


namespace GY511
{
    static StructDataRaw raw_acce_x;
    static StructDataRaw raw_acce_y;
    static StructDataRaw raw_acce_z;

    static StructDataRaw raw_magn_x;
    static StructDataRaw raw_magn_y;
    static StructDataRaw raw_magn_z;

    static void Write(uint8 addr, uint8 reg, uint8 data)
    {
        HAL_I2C1::Write(addr, reg, &data, 1);
    }

    static uint8 Read(uint8 addr, uint8 reg)
    {
        uint8 result = 0;
        HAL_I2C1::Read(addr, reg, &result, 1);
        return result;
    }

    static bool is_reading = false;
}


void GY511::Init()
{
    uint8 data = 0;
    _SET_BIT(data, 4);                              // I1_ZYXDA = 1 - разрешаем прерывания INT1 по полученным измерениям
    Write(ADDR_ACCE, GY511_CTRL_REG3, data);

    // Enable Block Data Update.
    data = Read(ADDR_ACCE, GY511_CTRL_REG4);
    data |= (1 << 7);                               // BDU = 1
    Write(ADDR_ACCE, GY511_CTRL_REG4, data);

    // Set Output Data Rate to 1Hz.
    HAL_I2C1::Read(ADDR_ACCE, GY511_CTRL_REG1, &data, 1);
    data |= (1 << 4);                               // ODR = 0b0001, 1Hz
    HAL_I2C1::Write(ADDR_ACCE, GY511_CTRL_REG1, &data, 1);

    // Set device in continuous mode with 12 bit resol.
    HAL_I2C1::Read(ADDR_ACCE, GY511_CTRL_REG4, &data, 1);
    data |= (1 << 3);                                           // HR = 1, (LPen = 0 - High resolution mode)
    Write(ADDR_ACCE, GY511_CTRL_REG4, data);
}


void GY511::Update()
{
    if (Read(ADDR_ACCE, GY511_STATUS_REG) & (1 << 3))
    {
        raw_acce_x.byte[0] = Read(ADDR_ACCE, GY511_OUT_X_L_A);
        raw_acce_x.byte[1] = Read(ADDR_ACCE, GY511_OUT_X_H_A);

        raw_acce_y.byte[0] = Read(ADDR_ACCE, GY511_OUT_Y_L_A);
        raw_acce_y.byte[1] = Read(ADDR_ACCE, GY511_OUT_Y_H_A);

        raw_acce_z.byte[0] = Read(ADDR_ACCE, GY511_OUT_Z_L_A);
        raw_acce_z.byte[1] = Read(ADDR_ACCE, GY511_OUT_Z_H_A);

        is_reading = true;
    }
}


bool GY511::GetMagnetic(Measure *magneticX, Measure *magneticY, Measure *magneticZ)
{
#ifdef IN_MODE_TEST

    magneticX->Set(Measure::Name::MagneticX, raw_acce_x.ToAccelerate());
    magneticY->Set(Measure::Name::MagneticY, raw_acce_y.ToAccelerate());
    magneticZ->Set(Measure::Name::MagneticZ, raw_acce_z.ToAccelerate());

    return true;

#else
    if (is_reading)
    {
        is_reading = false;

        magneticX->Set(Measure::Name::MagneticX, raw_acce_x.ToAccelerate());
        magneticY->Set(Measure::Name::MagneticY, raw_acce_y.ToAccelerate());
        magneticZ->Set(Measure::Name::MagneticZ, raw_acce_z.ToAccelerate());

        return true;
    }

    return false;
#endif
}
