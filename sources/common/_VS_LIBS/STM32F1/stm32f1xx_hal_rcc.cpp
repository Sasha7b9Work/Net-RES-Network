// 2022/04/27 15:11:27 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include <stm32f1xx_hal.h>


HAL_StatusTypeDef HAL_RCC_ClockConfig(RCC_ClkInitTypeDef * /*RCC_ClkInitStruct*/, uint32_t /*FLatency*/)
{
    return HAL_OK;
}