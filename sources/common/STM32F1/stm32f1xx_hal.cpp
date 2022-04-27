#include "defines.h"
#include <stm32f1xx_hal.h>
#include <ctime>


uint HAL_GetTick()
{
    return (uint)(clock());
}
