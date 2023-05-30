// 2022/05/05 13:14:44 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Pages/Pages.h"
#include "Settings/Settings.h"


extern const DPage pageMain;


DEF_CHOICE_2(chTemperature,
    "Температура",
    *PageDisplay::PageMeasures::self,
    EmptyVV,
    gset.display.show_measure[TypeMeasure::Temperature],
    "Откл", "Вкл"
)

DEF_CHOICE_2(chHumidity,
    "Влажность",
    *PageDisplay::PageMeasures::self,
    EmptyVV,
    gset.display.show_measure[TypeMeasure::Humidity],
    "Откл", "Вкл"
)

DEF_CHOICE_2(chPressure,
    "Давление",
    *PageDisplay::PageMeasures::self,
    EmptyVV,
    gset.display.show_measure[TypeMeasure::Pressure],
    "Откл", "Вкл"
)

DEF_CHOICE_2(chDewPoint,
    "Точка росы",
    *PageDisplay::PageMeasures::self,
    EmptyVV,
    gset.display.show_measure[TypeMeasure::DewPoint],
    "Откл", "Вкл"
)

static void CloseMeasures()
{
    PageDisplay::PageMeasures::self->Close();
};

DEF_BUTTN( bCloseMeasures,
    "Закрыть",
    *PageDisplay::PageMeasures::self,
    EmptyVV,
    CloseMeasures
)

DEF_PAGE_5(pageMeasures, //-V1027
    "ИЗМЕРЕНИЯ",
    *PageDisplay::self,
    EmptyVV,
    chTemperature,
    chPressure,
    chHumidity,
    chDewPoint,
    bCloseMeasures
)


void ClosePageDisplay()
{
    PageDisplay::self->Close();
}

DEF_BUTTN( bClosePageDisplay,
    "Закрыть",
    *PageDisplay::self,
    EmptyVV,
    ClosePageDisplay
)

DEF_PAGE_2(pageDisplay, //-V1027
    "ДИСПЛЕЙ",
    pageMain,
    EmptyVV,
    pageMeasures,
    bClosePageDisplay
)

const Page * const PageDisplay::self = (const Page *)&pageDisplay;
const Page * const PageDisplay::PageMeasures::self = (const Page *)&pageMeasures;
