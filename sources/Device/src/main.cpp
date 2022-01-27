#include "Modules/HC12/HC12.h"
#include "Hardware/HAL/HAL.h"
#include "Modules/BME280/BME280.h"
#include "Hardware/USBD/usbd_cdc_if.h"
#include <string.h>


int main(void)
{
    HAL::Init();

    BME280::Init();

    HC12::Init();

    while (1)
    {
        char buffer[128];

        BME280::Update(buffer);

        CDC_Transmit_FS((unsigned char *)buffer, strlen(buffer));

        HC12::Send(buffer);         

        HAL::Delay(1000);
    }
}
