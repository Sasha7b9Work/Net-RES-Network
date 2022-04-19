#include "main.h"
#include "Hardware/Timer.h"
#include <stm32f1xx_hal.h>


uint Timer::CurrentTime()
{
    return HAL_GetTick();
}
