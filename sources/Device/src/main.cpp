#include "main.h"
#include "usb_device.h"
#include "i2c.h"
#include "Modules/HC12/HC12.h"
#include "Hardware/HAL/HAL.h"
#include "Modules/BME280/BME280.h"


int main(void)
{
    HAL::Init();

    BME280::Init();

    MX_USB_DEVICE_Init();

    HC12_Init();

    while (1)
    {
        BME280::Update();
    }
}
