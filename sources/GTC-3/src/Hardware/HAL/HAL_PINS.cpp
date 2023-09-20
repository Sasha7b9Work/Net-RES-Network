// 2023/06/15 14:13:18 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Hardware/HAL/HAL.h"
#include <stm32f3xx_hal.h>


Pin pinWP(GPIOB, GPIO_PIN_0, GPIO_MODE_OUTPUT_PP, GPIO_PULLUP);


void Pin::Init()
{
    GPIO_InitTypeDef is =
    {
        pin,
        mode,
        pull,
        GPIO_SPEED_HIGH
    };

    HAL_GPIO_Init(gpio, &is);
}


void Pin::ToLow()
{
    HAL_GPIO_WritePin(gpio, pin, GPIO_PIN_RESET);
}


void Pin::ToHi()
{
    HAL_GPIO_WritePin(gpio, pin, GPIO_PIN_SET);
}


void Pin::Set(bool hi)
{
    HAL_GPIO_WritePin(gpio, pin, hi ? GPIO_PIN_SET : GPIO_PIN_RESET);
}


bool Pin::IsHi()
{
    return HAL_GPIO_ReadPin(gpio, pin) == GPIO_PIN_SET;
}


void HAL_PINS::Init()
{
    pinWP.Init();
    pinWP.ToLow();
}
