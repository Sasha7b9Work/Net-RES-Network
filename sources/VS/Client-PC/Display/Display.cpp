// 2022/04/29 16:45:45 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "Display/Display.h"
#include "Display/Colors.h"
#include "Frame.h"
#include "Utils/Timer.h"
#include "Utils/Text/String.h"
#include "Display/Font.h"


pchar TypeMeasure::GetTitle(TypeMeasure::E type)
{
    static const pchar titles[Count] =
    {
        "Давление",
        "Освещённость",
        "Скорость",
        "Температура",
        "Влажность"
    };

    return titles[type];
}


pchar TypeMeasure::GetUnits(TypeMeasure::E type)
{
    static const pchar units[Count] =
    {
        "МПа",
        "лк",
        "м/с",
        "Ц",
        "%%"
    };

    return units[type];
}


void Display::SwitchMeasure(TypeMeasure::E)
{
}


void Display::Reset()
{
}
