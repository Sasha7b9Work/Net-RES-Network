// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Utils/Text/String.h"
#include "Settings/Settings.h"
#include "Hardware/HAL/HAL_PINS.h"


struct PackedTime
{
    int hours;
    int minutes;
    int seconds;
    int year;
    int month;
    int day;
    int ms;
    PackedTime(int h = 11, int m = 11, int s = 11, int d = 11, int mo = 11, int y = 11) :
        hours(h), minutes(m), seconds(s), year(y), month(mo), day(d), ms(0) {};

    String<> ToString() const;
};


namespace HAL
{
    void Init();

    void Delay(unsigned int timeMS);

    String<> GetUID();
}


namespace HAL_ADC
{
    void Init();

    void Update();

    float GetVoltage();

    extern void *handle;           // ADC_HandleTypeDef
}


namespace HAL_I2C1
{
    void Init();

    int8 Read(uint8 dev_id, uint8 reg_addr, uint8 *reg_data, uint16 len);
    int8 Read16(uint8 dev_id, uint8 *data);

    int8 Write(uint8 dev_id, uint8 reg_addr, uint8 *reg_data, uint16 len);
    int8 Write8(uint8 dev_id, uint8 data);
}


namespace HAL_RTC
{
    void Init();

    PackedTime GetTime();

    void SetTime(const PackedTime &);
}


namespace HAL_USART_HC12
{
    void Init();

    void Transmit(const void *buffer, int size);

    extern void *handle;               // UART_HandleTypeDef
}


namespace HAL_ROM
{
    void SaveSettings(const Settings &);
    bool LoadSettings(Settings &);
}


#ifdef __cplusplus
extern "C" {
#endif 

    void NMI_Handler(void);
    void HardFault_Handler(void);
    void MemManage_Handler(void);
    void BusFault_Handler(void);
    void UsageFault_Handler(void);
    void SVC_Handler(void);
    void DebugMon_Handler(void);
    void PendSV_Handler(void);
    void SysTick_Handler(void);
    void USB_LP_CAN1_RX0_IRQHandler(void);
    void USART1_IRQHandler(void);
    void ADC1_2_IRQHandler(void);
    void TIM3_IRQHandler(void);

#ifdef __cplusplus
}
#endif
