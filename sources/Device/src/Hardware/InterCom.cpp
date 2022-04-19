// Sasha7b9@tut.by (c)
#include "main.h"
#include "Hardware/InterCom.h"
#include "Hardware/CDC/CDC.h"
#include "Modules/HC12/HC12.h"
#include "Modules/ST7735/ST7735.h"
#include "Display/Display.h"
#include "Utils/Text/String.h"


namespace InterCom
{
    Direction::E direction = Direction::_None;
}



void InterCom::SetDirection(Direction::E dir)
{
    direction = dir;
}


void InterCom::Send(TypeMeasure::E type, float measure)
{
    static const pchar names[TypeMeasure::Count] =
    {
        "Давление",
        "Освещённость",
        "Влажность",
        "Скорость",
        "Температура"
    };

    String<> message("%s : %f", names[type], measure);

    if (direction & Direction::CDC)
    {
        CDC::Transmit(message.c_str());
    }

    if (direction & Direction::HC12)
    {
        HC12::Transmit(message.c_str());
    }

    if (direction & Direction::Display)
    {
        Display::SetMeasure(type, measure);
    }
}
