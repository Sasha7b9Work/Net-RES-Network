// 2022/04/20 08:54:03 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once

#include "usbd_cdc.h"

extern USBD_CDC_ItfTypeDef USBD_Interface_fops_FS;


#ifdef __cplusplus
 extern "C" {
#endif

namespace  CDC
{
     uint8_t Transmit(const char *buffer);
}

#ifdef __cplusplus
}
#endif
