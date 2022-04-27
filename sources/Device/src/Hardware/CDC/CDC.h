// 2022/04/20 08:54:03 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "usbd_cdc.h"


extern USBD_CDC_ItfTypeDef USBD_Interface_fops_FS;


struct CDC
{
    static void Init();

    static uint8_t Transmit(const char *buffer);

    static void OnIRQHandler();

    static void *handlePCD;        // PCD_HandleTypeDef
};
