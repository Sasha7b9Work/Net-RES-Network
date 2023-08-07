// 2023/01/30 15:35:49 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Hardware/HAL/HAL.h"
#include <stm32f1xx_hal.h>
#include <time.h>


namespace HAL_RTC
{
#define WAKEUP_TIMER_ENABLE 0x32F2

    static RTC_HandleTypeDef handleRTC =
    {
        RTC,
        {
            RTC_AUTO_1_SECOND       // AsynchPrediv
        }
    };


    static HAL_StatusTypeDef  RTC_WriteTimeCounter(RTC_HandleTypeDef *hrtc, uint32_t TimeCounter);
    static HAL_StatusTypeDef  RTC_EnterInitMode(RTC_HandleTypeDef *hrtc);
    static HAL_StatusTypeDef  RTC_ExitInitMode(RTC_HandleTypeDef *hrtc);
    static uint32_t           RTC_ReadTimeCounter(RTC_HandleTypeDef *hrtc);
}


void HAL_RTC::Init()
{
    RCC_OscInitTypeDef RCC_OscInitStruct;
    RCC_PeriphCLKInitTypeDef  PeriphClkInitStruct;

    /*##-1- Configue LSI as RTC clock soucre ###################################*/
    HAL_RCC_GetOscConfig(&RCC_OscInitStruct);

    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI | RCC_OSCILLATORTYPE_LSE;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
    RCC_OscInitStruct.LSEState = RCC_LSE_ON;
    RCC_OscInitStruct.LSIState = RCC_LSI_OFF;
    HAL_RCC_OscConfig(&RCC_OscInitStruct);

    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_RTC;
    PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
    HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct);


    /*##-2- Enable RTC peripheral Clocks #######################################*/
    /* Enable RTC Clock */
    __HAL_RCC_RTC_ENABLE();

    HAL_RTC_Init(&handleRTC);
}


PackedTime HAL_RTC::GetTime()
{
    time_t rawtime = RTC_ReadTimeCounter(&handleRTC);

    struct tm *timeinfo = gmtime(&rawtime);

    return PackedTime(timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec, timeinfo->tm_year + 1900, timeinfo->tm_mon, timeinfo->tm_mday);
}


uint HAL_RTC::SetTime(const PackedTime &time)
{
    struct tm timeinfo =
    {
        time.seconds,
        time.minutes,
        time.hours,
        time.day,
        time.month,
        time.year + 100,
        0,
        0,
        0
    };

    time_t rawtime = mktime(&timeinfo);

    __HAL_LOCK(&handleRTC);

    handleRTC.State = HAL_RTC_STATE_BUSY;

    RTC_WriteTimeCounter(&handleRTC, (uint)rawtime);

    handleRTC.State = HAL_RTC_STATE_READY;

    __HAL_UNLOCK(&handleRTC);

    return HAL_OK;
}


String<> PackedTime::ToString() const
{
    return String<>("%02d:%02d:%02d:%03d", hours, minutes, seconds, ms);
}


HAL_StatusTypeDef HAL_RTC::RTC_WriteTimeCounter(RTC_HandleTypeDef *hrtc, uint32_t TimeCounter)
{
    HAL_StatusTypeDef status = HAL_OK;

    /* Set Initialization mode */
    if (RTC_EnterInitMode(hrtc) != HAL_OK)
    {
        status = HAL_ERROR;
    }
    else
    {
        /* Set RTC COUNTER MSB word */
        WRITE_REG(hrtc->Instance->CNTH, (TimeCounter >> 16U));
        /* Set RTC COUNTER LSB word */
        WRITE_REG(hrtc->Instance->CNTL, (TimeCounter & RTC_CNTL_RTC_CNT));

        /* Wait for synchro */
        if (RTC_ExitInitMode(hrtc) != HAL_OK)
        {
            status = HAL_ERROR;
        }
    }

    return status;
}


HAL_StatusTypeDef HAL_RTC::RTC_EnterInitMode(RTC_HandleTypeDef *hrtc)
{
    uint32_t tickstart = 0U;

    tickstart = HAL_GetTick();
    /* Wait till RTC is in INIT state and if Time out is reached exit */
    while ((hrtc->Instance->CRL & RTC_CRL_RTOFF) == (uint32_t)RESET) //-V1044
    {
        if ((HAL_GetTick() - tickstart) > RTC_TIMEOUT_VALUE)
        {
            return HAL_TIMEOUT;
        }
    }

    /* Disable the write protection for RTC registers */
    __HAL_RTC_WRITEPROTECTION_DISABLE(hrtc);


    return HAL_OK;
}


HAL_StatusTypeDef HAL_RTC::RTC_ExitInitMode(RTC_HandleTypeDef *hrtc)
{
    uint32_t tickstart = 0U;

    /* Disable the write protection for RTC registers */
    __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);

    tickstart = HAL_GetTick();
    /* Wait till RTC is in INIT state and if Time out is reached exit */
    while ((hrtc->Instance->CRL & RTC_CRL_RTOFF) == (uint32_t)RESET) //-V1044
    {
        if ((HAL_GetTick() - tickstart) > RTC_TIMEOUT_VALUE)
        {
            return HAL_TIMEOUT;
        }
    }

    return HAL_OK;
}


uint32_t HAL_RTC::RTC_ReadTimeCounter(RTC_HandleTypeDef *hrtc)
{
    uint16_t high1 = 0U, high2 = 0U, low = 0U;
    uint32_t timecounter = 0U;

    high1 = READ_REG(hrtc->Instance->CNTH & RTC_CNTH_RTC_CNT);
    low = READ_REG(hrtc->Instance->CNTL & RTC_CNTL_RTC_CNT);
    high2 = READ_REG(hrtc->Instance->CNTH & RTC_CNTH_RTC_CNT);

    if (high1 != high2)
    { /* In this case the counter roll over during reading of CNTL and CNTH registers,
         read again CNTL register then return the counter value */
        timecounter = (((uint32_t)high2 << 16U) | READ_REG(hrtc->Instance->CNTL & RTC_CNTL_RTC_CNT));
    }
    else
    { /* No counter roll over during reading of CNTL and CNTH registers, counter
         value is equal to first value of CNTL and CNTH */
        timecounter = (((uint32_t)high1 << 16U) | low);
    }

    return timecounter;
}
