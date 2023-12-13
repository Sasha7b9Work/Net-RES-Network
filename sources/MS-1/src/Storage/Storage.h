// 2023/09/08 11:46:53 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Hardware/HAL/HAL.h"
#include "Modules/W25Q80DV/W25Q80DV.h"


struct Measurements
{
    uint  crc32;
    float temperature;
    float pressure;
    float humidity;
    float dev_point;
    float velocity;
    float latitude;
    float longitude;
    float altitude;
    float azimuth;
    PackedTime time;
};


namespace Storage
{
    static const int SIZE = 1024 * 1024 - 2 * W25Q80DV::SIZE_PAGE;        // 8 MBit = 1 MByte

    void Init();

    void Update();

    void AppendMeasure(const Measure &);

    bool GetMeasure(Measure::E, Measure &);
}

