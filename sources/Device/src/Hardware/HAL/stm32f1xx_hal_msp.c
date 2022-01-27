#include "main.h"
#include "stm32f1xx_hal.h"


void HAL_MspInit()
{
  __HAL_RCC_AFIO_CLK_ENABLE();
  __HAL_RCC_PWR_CLK_ENABLE();
}
