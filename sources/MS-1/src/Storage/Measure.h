// 2023/11/21 21:27:47 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


struct Measure
{
    enum E
    {
        Temperature,    // Температура
        Pressure,       // Давление
        Humidity,       // Влажность
        DewPoint,       // Точка росы
        Velocity,       // Скорость воздуха
        Latitude,       // Широта
        Longitude,      // Долгота
        Altitude,       // Высота
        Azimuth,        // Азимут - угол от направления на север
        Count
    };

    union
    {
        double value_d;
        uint   value_32;
    };

    void Clear()
    {
        name = E::Count;
    }

    double GetDouble() const
    {
        return value_d;
    }

    E GetName() const
    {
        return name;
    }

    void Set(E _name, float value)
    {
        Set(_name, (double)value);
    }

    void Set(E _name, double value)
    {
        name = _name;
        SetDouble(value);
    }


private:

    void SetDouble(float value)
    {
        SetDouble((double)value);
    }

    void SetDouble(double value)
    {
        value_d = value;
    }

    E name;
};
