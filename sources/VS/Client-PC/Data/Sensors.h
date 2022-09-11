// 2022/08/24 14:56:11 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


struct TypeMeasure
{
    enum E
    {
        Pressure,           // Давление
        Illumination,       // Освещённость
        Temperature,        // Температура
        Humidity,           // Влажность
        Velocity,           // Скорость
        Count
    };

    static pchar GetTitle(TypeMeasure::E);
    static pchar GetUnits(TypeMeasure::E);
};


class Sensor
{
public:

    Sensor(uint _id) : id(_id) {};

    void AppendMeasure(uint8 type, float value);

private:

    const uint id;

    std::vector<float> measures[TypeMeasure::Count];
};


namespace PoolSensors
{
    void AppendMeasure(uint id, uint8 type, float value);
};
