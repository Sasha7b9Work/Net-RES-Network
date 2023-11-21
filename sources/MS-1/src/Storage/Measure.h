// 2023/11/21 21:27:47 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


struct Measure
{
    struct Type
    {
        enum E
        {
            None,
            Float,
            Double,
            String
        };
    };

    Type::E type;

    union
    {
        float  value_f;
        double value_d;
        char   str[32];
    };

    void Clear()
    {
        type = Type::None;
    }

    void CreateFloat(float value)
    {
        type = Type::Float;
        value_f = value;
    }
};
