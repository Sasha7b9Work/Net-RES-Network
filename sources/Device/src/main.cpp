#include "Modules/HC12/HC12.h"
#include "Hardware/HAL/HAL.h"
#include "Modules/BME280/BME280.h"
#include "Hardware/CDC/CDC.h"


int main(void)
{
    HAL::Init();

    BME280::Init();

    HC12::Init();

    while (1)
    {
        const char *buffer = BME280::GetMeasure();

        CDC::Transmit(buffer);

        HC12::Transmit(buffer);

        HAL::Delay(1000);
    }
}
