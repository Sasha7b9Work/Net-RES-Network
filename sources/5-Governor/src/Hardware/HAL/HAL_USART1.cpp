// 2024/01/11 10:43:04 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Hardware/HAL/HAL.h"
#include <stm32f1xx_hal.h>


namespace HAL_USART1
{
    struct RecvBuffer
    {
        static const int SIZE = 128;

        RecvBuffer() : pointer(0) { }

        void Push(char symbol)
        {
            if (pointer < SIZE)
            {
                data[pointer++] = symbol;
            }
        }

        char *Data() { return &data[0]; }
        int NumSymbols() { return pointer; }
        void Clear() { pointer = 0; }

    private:
        char data[SIZE];
        int pointer;
    } recv_buffer;

    static UART_HandleTypeDef handleUART;
    void *handle = (void *)&handleUART;

    static char recv_byte = 0;

    static void (*callback_on_receive)(pchar) = nullptr;
}


void HAL_USART1::Init(void (*_callback_on_receive)(pchar))
{
    callback_on_receive = _callback_on_receive;

    __HAL_RCC_USART1_CLK_ENABLE();

    GPIO_InitTypeDef is;

    is.Pin = GPIO_PIN_6;            // TX
    is.Mode = GPIO_MODE_AF_PP;
    is.Speed = GPIO_SPEED_FREQ_HIGH;

    HAL_GPIO_Init(GPIOB, &is);

    is.Pin = GPIO_PIN_7;            // RX
    is.Mode = GPIO_MODE_INPUT;
    is.Pull = GPIO_NOPULL;

    HAL_GPIO_Init(GPIOB, &is);

    __HAL_AFIO_REMAP_USART1_ENABLE();

    handleUART.Instance = USART1;
    handleUART.Init.BaudRate = 19200;
    handleUART.Init.WordLength = UART_WORDLENGTH_8B;
    handleUART.Init.StopBits = UART_STOPBITS_1;
    handleUART.Init.Parity = UART_PARITY_NONE;
    handleUART.Init.Mode = UART_MODE_TX_RX;
    handleUART.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    handleUART.Init.OverSampling = UART_OVERSAMPLING_16;

    HAL_UART_Init(&handleUART);

    HAL_NVIC_SetPriority(USART1_IRQn, 1, 1);
    HAL_NVIC_EnableIRQ(USART1_IRQn);

    HAL_UART_Receive_IT(&handleUART, (uint8 *)&recv_byte, 1);
}


void HAL_USART1::Send(uint8 byte)
{
    HAL_UART_Transmit(&handleUART, &byte, 1, 10);
}


void HAL_USART1::ReceiveCallback()
{
    recv_buffer.Push(recv_byte);

    HAL_UART_Receive_IT(&handleUART, (uint8 *)&recv_byte, 1);
}


void HAL_USART1::Update()
{
    if (!callback_on_receive)
    {
        return;
    }
}
