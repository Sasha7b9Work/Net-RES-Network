// 2022/08/24 14:56:11 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include <map>


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

    const std::vector<float> &GetMeasures(TypeMeasure::E type) const { return measures[type]; }

private:

    const uint id;

    std::vector<float> measures[TypeMeasure::Count];

public:

    struct Pool
    {
        static void AppendMeasure(uint id, uint8 type, float value);

        static const std::map<uint, Sensor> &GetPool() { return pool; };

        static int CountSensors() { return pool.size(); };

    private:

        static std::map<uint, Sensor> pool;
    };
};
