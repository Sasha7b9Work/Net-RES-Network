// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
//#define int8_t signed char
//#define uint8_t unsigned char
//#define int32_t int
//#define uint32_t unsigned int


namespace BME280
{
    void Init();

    const char *GetMeasure(unsigned int dT);
}
