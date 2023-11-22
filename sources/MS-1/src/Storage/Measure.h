// 2023/11/21 21:27:47 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


struct Measure
{
    struct Type
    {
        enum E
        {
            None,
            Double,
            String
        };
    };

    union
    {
        double value_d;
        char   str[32];
    };

    bool IsDouble() const
    {
        return (type == Type::Double);
    }

    bool IsString() const
    {
        return type == Type::String;
    }

    void Clear()
    {
        type = Type::None;
    }

    void SetDouble(double value)
    {
        type = Type::Double;
        value_d = value;
    }

    void SetDouble(float value)
    {
        SetDouble((double)value);
    }

    double GetDouble() const
    {
        return value_d;
    }

private:

    Type::E type;
};
