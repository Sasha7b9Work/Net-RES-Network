#pragma once


namespace BME280
{
    void Init();
    void GetMeasure(char buffer[128]);
}
