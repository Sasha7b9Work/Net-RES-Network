#include "defines.h"
#include "Hardware/CDC/CDC.h"
#include "Hardware/HAL/HAL.h"
#include "Hardware/Modules/HC12/HC12.h"
#include <stm32f1xx_hal.h>

#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
    #pragma clang diagnostic ignored "-Wmissing-noreturn"
#endif

void NMI_Handler(void)
{
}


void HardFault_Handler(void)
{
    while (1)
    {
    }
}


void MemManage_Handler(void)
{
    while (1)
    {
    }
}


void BusFault_Handler(void)
{
    while (1)
    {
    }
}


void UsageFault_Handler(void)
{
    while (1)
    {
    }
}


void SVC_Handler(void)
{

}


void DebugMon_Handler(void)
{

}


void PendSV_Handler(void)
{

}


void SysTick_Handler(void)
{
    HAL_IncTick();
}


void USB_LP_CAN1_RX0_IRQHandler(void)
{
    HCDC_OnIRQHandler();
}

void USART1_IRQHandler(void)
{
    HAL_UART_IRQHandler((UART_HandleTypeDef *)HAL_USART1::handle);
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *)
{
    HAL_USART1::ReceiveCallback();
}
