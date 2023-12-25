// 2023/09/08 11:46:53 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Hardware/HAL/HAL.h"
#include "Modules/W25Q80DV/W25Q80DV.h"
#include "Hardware/HAL/HAL.h"


struct Measurements
{
public:
    Measurements(float temp = 0.0f, float press = 0.0f, float hum = 0.0f, float dew = 0.0f, float vel = 0.0f, PackedTime _time = PackedTime()) :
        temperature(temp),
        pressure(press),
        humidity(hum),
        dew_point(dew),
        velocity(vel),
        time(_time),
        control_field(0)
    {
        crc = CalculateCRC();
    }

    float GetTemperature() const { return temperature; }
    float GetPressure()    const { return pressure; }
    float GetHumidity()    const { return humidity; }
    float GetDewPoint()    const { return dew_point; }
    float GetVelocity()    const { return velocity; }
    PackedTime GetTime()   const { return time; }

    uint CalculateCRC();

    uint GetCRC() { return crc; }

    int number;

private:

    float temperature;
    float pressure;
    float humidity;
    float dew_point;
    float velocity;
    PackedTime time;
    uint crc;

public:

    uint control_field;
};


namespace Storage
{
    static const int SIZE = 1024 * 1024 - 2 * W25Q80DV::SIZE_PAGE;        // 8 MBit = 1 MByte

    void Init();

    void Update();

    void AppendMeasure(const Measure &);

    bool GetMeasure(Measure::E, Measure &);

    Measurements GetLastMeasurements();

    bool Test();
}
