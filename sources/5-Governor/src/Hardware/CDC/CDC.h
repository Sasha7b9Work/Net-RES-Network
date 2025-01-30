// 2022/04/20 08:54:03 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "usbd_cdc.h"


extern void *handlePCD;        // PCD_HandleTypeDef


void HCDC_Init(void);

uint8 HCDC_Transmit(const void *buffer, int size);

void HCDC_TransmitF(pchar buffer, ...);

void HCDC_OnIRQHandler(void);
