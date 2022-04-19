/// Sasha7b9@tut.by (c)
#include "main.h"
#include "Hardware/InterCom.h"
#include "Hardware/CDC/CDC.h"
#include "Modules/HC12/HC12.h"
#include "Modules/ST7735/ST7735.h"
#include "Display/Display.h"


namespace InterCom
{
    Direction::E direction = Direction::_None;
}



void InterCom::SetDirection(Direction::E dir)
{
    direction = dir;
}


void InterCom::Send(pchar measure)
{
    if (!measure)
    {
        return;
    }

    if (direction & Direction::CDC)
    {
        CDC::Transmit(measure);
    }

    if (direction & Direction::HC12)
    {
        HC12::Transmit(measure);
    }

    if (direction & Direction::Display)
    {
        Display::SetMeasure(measure);
    }
}
