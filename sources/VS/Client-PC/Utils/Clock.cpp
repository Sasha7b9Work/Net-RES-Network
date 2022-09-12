// 2022/09/12 14:15:25 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Utils/Clock.h"
#include <ctime>


using namespace std;


namespace Clock
{
    static Time current;
}


void Clock::Update()
{
    time_t now = time(0);

    tm *time = localtime(&now);

    current.sec = time->tm_sec;
    current.min = time->tm_min;
    current.hour = time->tm_hour;
}


Time &Clock::CurrentTime()
{
    return current;
}


String<> Time::ToString() const
{
    return String<>("%d:%d", hour, min);
}
