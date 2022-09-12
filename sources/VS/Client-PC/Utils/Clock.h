// 2022/09/12 14:12:37 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


struct Time
{
    int sec;
    int min;
    int hour;
};


namespace Clock
{
    void Update();

    Time &CurrentTime();
}
