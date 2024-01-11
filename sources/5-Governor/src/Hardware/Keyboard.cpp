// 2022/05/06 11:30:11 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Hardware/Keyboard.h"
#include "Hardware/Timer.h"
#include "Menu/Menu.h"
#include <stm32f1xx_hal.h>


namespace Keyboard
{
    TimeMeterMS meter;

    bool pressed = false;               // Если true, клавиша нажата
    bool taboo_long = false;            // Если true, запрещено длинное срабатывание

#define STATE_A (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6) == GPIO_PIN_SET)
#define STATE_B (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_7) == GPIO_PIN_SET)

    static bool prev_a = false;
    static bool prev_b = false;

    static const float step_angle = 360.0f / 256.0f;
    static float angle = 0;
}


float Keyboard::GetAngle()
{
    return (float)angle;
}


void Keyboard::Init()
{
    GPIO_InitTypeDef is =
    {
        GPIO_PIN_6 | GPIO_PIN_7,
        GPIO_MODE_INPUT,
        GPIO_PULLUP,
        GPIO_SPEED_FREQ_MEDIUM
    };

    HAL_GPIO_Init(GPIOA, &is);
}


void Keyboard::Update()
{
    static bool first = true;

    if (first)
    {
        first = false;

        prev_a = STATE_A;
        prev_b = STATE_B;

        return;
    }

    bool state_a = STATE_A;
    bool state_b = STATE_B;

    if (state_a && !prev_a)
    {
        if (state_b)
        {
            angle += step_angle;
        }
        else
        {
            angle -= step_angle;
        }
    }

    prev_a = state_a;
    prev_b = state_b;
}
