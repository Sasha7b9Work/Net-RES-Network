// 2022/05/05 15:23:05 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Settings/Settings.h"
#include "Hardware/HAL/HAL.h"


static const Settings default =
{
    // Display
    {
        {1, 1, 1, 0},
        { TypeDisplayedInformation::AllMeasures }
    },
    // System
    {
        0                                           // serial_number
    },
    // Measures
    {
        {-100, 0, 0, -100},
        {100, 1000, 100, 100}
    }
};


Settings gset = default;


#ifdef WIN32
uint Settings::GetID()
{
    return 112;
}
#else
uint Settings::GetID()
{
    uint address = 0x8000000 + 0x10000 - 4;

    uint *pointer = (uint *)address;

    return *pointer;
}
#endif


void Settings::Load()
{
    Settings settings;

    if(HAL)
}


void Settings::Update()
{

}