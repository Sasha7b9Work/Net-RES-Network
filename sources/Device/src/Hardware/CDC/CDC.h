#pragma once

#ifdef __cplusplus
 extern "C" {
#endif

#include "usbd_cdc.h"

extern USBD_CDC_ItfTypeDef USBD_Interface_fops_FS;

namespace CDC
{
     uint8_t Transmit(char *buffer);
}

#ifdef __cplusplus
}
#endif
