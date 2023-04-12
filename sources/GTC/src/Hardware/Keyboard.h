// 2022/05/06 11:30:06 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


struct Key
{
    enum E
    {
        _1,
        _2,
        Count
    };
};

namespace Keyboard
{
    void Init();

    void Update();
}
