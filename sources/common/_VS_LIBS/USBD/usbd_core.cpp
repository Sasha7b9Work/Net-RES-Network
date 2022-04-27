// 2022/04/27 14:29:19 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include <usbd_core.h>


USBD_StatusTypeDef USBD_Init(USBD_HandleTypeDef * /*pdev*/, USBD_DescriptorsTypeDef * /*pdesc*/, uint8_t /*id*/)
{
    return USBD_FAIL;
}


USBD_StatusTypeDef USBD_Start(USBD_HandleTypeDef * /*pdev*/)
{
    return USBD_FAIL;
}


USBD_StatusTypeDef USBD_RegisterClass(USBD_HandleTypeDef * /*pdev*/, USBD_ClassTypeDef * /*pclass*/)
{
    return USBD_FAIL;
}
