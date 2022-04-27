#include <usbd_cdc.h>



uint8_t USBD_CDC_SetTxBuffer(USBD_HandleTypeDef * /*pdev*/, uint8_t * /*pbuff*/, uint16_t /*length*/)
{
    return 0;
}


uint8_t USBD_CDC_SetRxBuffer(USBD_HandleTypeDef * /*pdev*/, uint8_t * /*pbuff*/)
{
    return 0;
}

uint8_t USBD_CDC_ReceivePacket(USBD_HandleTypeDef * /*pdev*/)
{
    return 0;
}

uint8_t USBD_CDC_TransmitPacket(USBD_HandleTypeDef * /*pdev*/)
{
    return 0;
}
