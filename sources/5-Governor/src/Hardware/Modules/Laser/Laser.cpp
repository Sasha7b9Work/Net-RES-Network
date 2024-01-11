// 2024/01/11 11:02:46 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Hardware/Modules/Laser/Laser.h"
#include "Hardware/HAL/HAL.h"


namespace Laser
{
    static const uint TURN_ON = 0x4f;
}


void Laser::Init()
{
    HAL_USART1::Send(TURN_ON);
}


void Laser::CallbackOnReceive(pchar)
{

}
