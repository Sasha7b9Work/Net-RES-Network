// 2023/04/04 09:57:45 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Hardware/HAL/HAL.h"
#include <stm32f1xx_hal.h>


namespace HAL_USART2
{
    static UART_HandleTypeDef handle;
}


void HAL_USART2::Init()
{
    __HAL_RCC_USART2_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART2 GPIO Configuration
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX
    */

    GPIO_InitTypeDef is;

    is.Pin = GPIO_PIN_2;
    is.Mode = GPIO_MODE_AF_PP;
    is.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &is);

    is.Pin = GPIO_PIN_3;
    is.Mode = GPIO_MODE_INPUT;
    is.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &is);

    handle.Instance = USART2;
    handle.Init.BaudRate = 115200;
    handle.Init.WordLength = UART_WORDLENGTH_8B;
    handle.Init.StopBits = UART_STOPBITS_1;
    handle.Init.Parity = UART_PARITY_NONE;
    handle.Init.Mode = UART_MODE_TX_RX;
    handle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    handle.Init.OverSampling = UART_OVERSAMPLING_16;

    HAL_UART_Init(&handle);
}
