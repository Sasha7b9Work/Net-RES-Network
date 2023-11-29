// 2023/11/21 21:27:47 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


struct Measure
{
    struct Type
    {
        enum E
        {
            Double,     // Всё, кроме времени
            Uint,       // Время в секундах после 2000 г
            Count
        };
    };

    struct Name
    {
        enum E
        {
            Temperature,    // Температура
            Pressure,       // Давление
            Humidity,       // Влажность
            DewPoint,       // Точка росы
            Illumination,   // Освещёность
            Velocity,       // Скорость воздуха
            Latitude,       // Широта
            Longitude,      // Долгота
            Altitude,       // Высота
            MagneticX,
            MagneticY,
            MagneticZ,
            Time,
            Count
        };
    };

    union
    {
        double value_d;
        uint   value_32;
    };

    void Clear()
    {
        type = Type::Count;
        name = Name::Count;
    }

    bool IsDouble() const
    {
        return type == Type::Double;
    }

    double GetDouble() const
    {
        return value_d;
    }

    Name::E GetName() const
    {
        return name;
    }

    Type::E GetType() const
    {
        return type;
    }

    void Set(Name::E _name, float value)
    {
        Set(_name, (double)value);
    }

    void Set(Name::E _name, double value)
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
        type = Type::Double;
        value_d = value;
    }

    Type::E type;

    Name::E name;
};
