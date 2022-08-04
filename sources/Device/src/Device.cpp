// 2022/04/27 11:48:13 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Device.h"
#include "Modules/HC12/HC12.h"
#include "Hardware/HAL/HAL.h"
#include "Modules/BME280/BME280.h"
#include "Modules/CG-Anem/CG-Anem.h"
#include "Modules/BH1750/BH1750.h"
#include "Hardware/CDC/CDC.h"
#include "Modules/ST7735/ST7735.h"
#include "Hardware/Timer.h"
#include "Hardware/InterCom.h"
#include "Display/Display.h"
#include "Hardware/Keyboard.h"


void Device::Init()
{
    HAL::Init();

    ST7735::Init();

    BME280::Init();

    HC12::Init();

#ifdef TYPE_1
    CG_Anem::Init();
#endif

    BH1750::Init();

    Keyboard::Init();

    InterCom::SetDirection((Direction::E)(Direction::CDC | Direction::HC12 | Direction::Display));
}


void Device::Update()
{
    float temp = 0.0f;
    float pressure = 0.0f;
    float humidity = 0.0;

    if (BME280::GetMeasures(1000, &temp, &pressure, &humidity))
    {
        InterCom::Send(TypeMeasure::Temperature, temp);
        InterCom::Send(TypeMeasure::Pressure, pressure);
        InterCom::Send(TypeMeasure::Humidity, humidity);
    }

#ifdef TYPE_1

    float velocity = 0.0f;

    if (CG_Anem::GetMeasure(1000, &velocity))
    {
        InterCom::Send(TypeMeasure::Velocity, velocity);
    }
#endif

    float illumination = 0.0f;

    if (BH1750::GetMeasure(1000, &illumination))
    {
        InterCom::Send(TypeMeasure::Illumination, illumination);
    }

    Keyboard::Update();

    Display::Update();
}
