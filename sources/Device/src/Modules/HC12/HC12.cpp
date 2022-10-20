// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Modules/HC12/HC12.h"
#include "stm32f1xx_hal.h"
#include "Hardware/HAL/HAL.h"
#include "Hardware/Timer.h"
#include <cstring>


#define PORT_SET GPIOA
#define PIN_SET  GPIO_PIN_6


namespace HC12
{
    static UART_HandleTypeDef handle;

    char recv_buffer = 255;
}


void HC12::Init()
{
    GPIO_InitTypeDef  is;

    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_USART1_CLK_ENABLE();

    is.Pin       = GPIO_PIN_9;
    is.Mode      = GPIO_MODE_AF_PP;
    is.Speed     = GPIO_SPEED_FREQ_HIGH;

    HAL_GPIO_Init(GPIOA, &is);
    
    is.Pin  = GPIO_PIN_10;              // TX
    is.Pull = GPIO_NOPULL;
    is.Mode = GPIO_MODE_INPUT;
    
    HAL_GPIO_Init(GPIOA, &is);

    is.Pin = PIN_SET;                // SET Для АТ команд
    is.Mode = GPIO_MODE_OUTPUT_PP;

    HAL_GPIO_Init(PORT_SET, &is);

    HAL_GPIO_WritePin(PORT_SET, PIN_SET, GPIO_PIN_SET);

    handle.Instance          = USART1;
    handle.Init.BaudRate     = 9600;
    handle.Init.WordLength   = UART_WORDLENGTH_8B;
    handle.Init.StopBits     = UART_STOPBITS_1;
    handle.Init.Parity       = UART_PARITY_NONE;
    handle.Init.HwFlowCtl    = UART_HWCONTROL_NONE;
    handle.Init.Mode         = UART_MODE_TX_RX;
    handle.Init.OverSampling = UART_OVERSAMPLING_16;

    HAL_UART_Init(&handle);

    HAL_NVIC_SetPriority(USART1_IRQn, 0, 1);
    HAL_NVIC_EnableIRQ(USART1_IRQn);

    HAL_UART_Receive_IT(&handle, (uint8 *)&recv_buffer, 1);

//    Command("AT");
}


void HC12::Transmit(const void *buffer, int size)
{
    if (!buffer)
    {
        return;
    }

    HAL_UART_Transmit(&handle, (uint8_t *)buffer, (uint16_t)size, 0xFFFF);
}


void HC12::Command(pchar command)
{
    HAL_GPIO_WritePin(PORT_SET, PIN_SET, GPIO_PIN_RESET);

    TimeMeterMS().WaitMS(40);

    Transmit(command, (int)std::strlen(command));
    Transmit("\r", 1);

    HAL_GPIO_WritePin(PORT_SET, PIN_SET, GPIO_PIN_SET);

    TimeMeterMS().WaitMS(80);
}


void HC12::ReceiveCallback()
{
    static int counter = 0;

    recv_buffer = recv_buffer;

    if (counter++ == 100)
    {
        counter = counter;
    }

    HAL_UART_Receive_IT(&handle, (uint8 *)&recv_buffer, 1);
}
