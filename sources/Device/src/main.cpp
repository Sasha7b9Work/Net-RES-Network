#include "Modules/HC12/HC12.h"
#include "Hardware/HAL/HAL.h"
#include "Modules/BME280/BME280.h"


int main(void)
{
    HAL::Init();

    BME280::Init();

    HC12::Init();

    while (1)
    {
        char buffer[128];

        BME280::Update(buffer);

        HAL::Delay(1000);
    }
}
