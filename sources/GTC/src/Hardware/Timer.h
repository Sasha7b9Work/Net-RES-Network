#pragma once
#include "defines.h"


#define TIME_MS Timer::CurrentTime()


namespace Timer
{
    uint CurrentTime();
}



// Структура для отсчёта времени
struct TimeMeterMS
{
    TimeMeterMS();

    // Установить момент отсчёта
    void Reset();

    void Pause();

    void Continue();

    // Столько миллисекунд прошло с момента вызова Reset()
    uint ElapsedTime();

    void WaitMS(uint);

    // Через ms миллисекунд IsFinished() становится равным true
    void FinishAfter(uint ms);

    bool IsFinished() const;

private:

    uint time_reset;        // От этого времени отсчитывается ElapsedTime()
    uint time_pause;        // В этот момент поставили на паузу
    uint time_finished;     // В это время IsFinished() становится равным true
};
