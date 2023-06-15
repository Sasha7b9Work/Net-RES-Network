// 2022/6/19 6:32:00 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Hardware/Beeper.h"
#include "Hardware/Timer.h"
#include "Hardware/HAL/HAL.h"
#include <stm32f1xx_hal.h>


namespace Beeper
{
    static PinOut pinBEEP(Port::B, Pin::_4, PMode::OUTPUT_PP_PULL_DOWN);
//    static PinOut pinBEEN(Port::B, Pin::_1, PMode::OUTPUT_PP_PULL_DOWN);

    static TIM_HandleTypeDef handle =
    {
        TIM3,
        {
            (uint)(60000 / 2000 - 1),
            TIM_COUNTERMODE_UP,
            999,
            TIM_CLOCKDIVISION_DIV1,
            0,
            TIM_AUTORELOAD_PRELOAD_DISABLE
        }
    };

    void *handleTIM3 = &handle;

    static int frequency = 0;          // Частота звучащего в данное время звука
    static bool running = false;       // Если true, то звук звучит

    static bool level = true;
}


void Beeper::Init()
{
    pinBEEP.Init();
//    pinBEEN.Init();

    pinBEEP.Low();
//    pinBEEN.Low();
}


void Beeper::Beep(int _frequency, uint timeMS)
{
    Start(_frequency);

    Timer::Delay(timeMS);

    Stop();
}


void Beeper::Start(int _frequency)
{
    if (running && (_frequency == frequency))
    {
        return;
    }

    if (running)
    {
        Stop();
    }

    frequency = _frequency;

    __HAL_RCC_TIM3_CLK_ENABLE();

    handle.Init.Prescaler = (uint)(60000 / frequency - 1);

    HAL_NVIC_SetPriority(TIM3_IRQn, 0, 1);
    HAL_NVIC_EnableIRQ(TIM3_IRQn);

    HAL_TIM_Base_Init(&handle);
    HAL_TIM_Base_Start_IT(&handle);

    running = true;
}


void Beeper::Stop()
{
    HAL_TIM_Base_Stop_IT(&handle);
    HAL_TIM_Base_DeInit(&handle);
    HAL_NVIC_DisableIRQ(TIM3_IRQn);

    __HAL_RCC_TIM3_CLK_DISABLE();

    running = false;

//    pinBEEN.Low();
    pinBEEP.Low();
}


bool Beeper::Running()
{
    return running;
}


void Beeper::CallbackOnTimer()
{
//    pinBEEN.Set(level);
    pinBEEP.Set(!level);

    level = !level;
}
