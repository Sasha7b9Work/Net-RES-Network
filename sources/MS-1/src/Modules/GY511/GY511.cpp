// 2023/01/30 16:45:08 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Modules/GY511/GY511.h"
#include "Hardware/HAL/HAL.h"
#include <stm32f3xx_hal.h>
#include <cmath>


#define ADDR_ACCE   0x19
#define ADDR_MAGN   0x1E

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

#define GY511_OUT_X_H_M     0x03
#define GY511_OUT_X_L_M     0x04
#define GY511_OUT_Y_H_M     0x07
#define GY511_OUT_Y_L_M     0x08
#define GY511_OUT_Z_H_M     0x05
#define GY511_OUT_Z_L_M     0x06

#define GY511_CRA_REG_M     0x00
#define GY511_MR_REG_M      0x02
#define GY511_SR_REG_M      0x09


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

    static bool is_ready_acce = false;
    static bool is_ready_magn = false;

    static float CalculateAzimuth();

    static void Update();
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

    Write(ADDR_MAGN, GY511_CRA_REG_M, 0x14);    // CRA_REG_M

    Write(ADDR_MAGN, GY511_MR_REG_M, 0x00);     // MR_REG_M
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

        is_ready_acce = true;
    }

    if (Read(ADDR_MAGN, GY511_SR_REG_M) & (0x01))
    {
        raw_magn_x.byte[0] = Read(ADDR_MAGN, GY511_OUT_X_L_M);
        raw_magn_x.byte[1] = Read(ADDR_MAGN, GY511_OUT_X_H_M);

        raw_magn_y.byte[0] = Read(ADDR_MAGN, GY511_OUT_Y_L_M);
        raw_magn_y.byte[1] = Read(ADDR_MAGN, GY511_OUT_Y_H_M);

        raw_magn_z.byte[0] = Read(ADDR_MAGN, GY511_OUT_Z_L_M);
        raw_magn_z.byte[1] = Read(ADDR_MAGN, GY511_OUT_Z_H_M);

        is_ready_magn = true;
    }
}


bool GY511::GetMagnetic(Measure *azimuth)
{
    Update();

#ifdef IN_MODE_TEST

    azimuth->Set(Measure::Azimuth, CalculateAzimuth());

    return true;

#else
    if (is_ready_acce)
    {
        is_ready_acce = false;

        azimuth->Set(Measure::Azimuth, CalculateAzimuth());

        return true;
    }

    return false;
#endif
}


float GY511::CalculateAzimuth()
{
    return 0.0f;
}
