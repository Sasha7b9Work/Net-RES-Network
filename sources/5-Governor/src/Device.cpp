// 2022/04/27 11:48:13 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Device.h"
#include "Hardware/Modules/HC12/HC12.h"
#include "Hardware/HAL/HAL.h"
#include "Hardware/Modules/BME280/BME280.h"
#include "Hardware/Modules/CG-Anem/CG-Anem.h"
#include "Hardware/Modules/BH1750/BH1750.h"
#include "Hardware/CDC/CDC.h"
#include "Hardware/Modules/ST7735/ST7735.h"
#include "Hardware/Timer.h"
#include "Hardware/InterCom.h"
#include "Display/Display.h"
#include "Hardware/Keyboard.h"


void Device::Init()
{
    HAL::Init();

    CDC::Init();
}


void Device::Update()
{
    static float prev_angle = -100.0f;

    Keyboard::Update();

    if (Keyboard::GetAngle() != prev_angle)
    {
        prev_angle = Keyboard::GetAngle();

        CDC::TransmitF("Angle %.1f", prev_angle);
    }
}
