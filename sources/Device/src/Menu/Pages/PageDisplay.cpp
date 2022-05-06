// 2022/05/05 13:14:44 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Pages/Pages.h"
#include "Settings/Settings.h"


extern const DPage pageMain;
extern const DPage pageDisplay;
extern const DPage pageMeasures;


DEF_CHOICE_2( chPressure,
    "Давление",
    pageMeasures,
    gset.display.show_measure[TypeMeasure::Pressure],
    "Откл", "Вкл"
)

DEF_CHOICE_2(chIllumination,
    "Освещённость",
    pageMeasures,
    gset.display.show_measure[TypeMeasure::Illumination],
    "Откл", "Вкл"
)

DEF_CHOICE_2(chVelocity,
    "Скорость",
    pageMeasures,
    gset.display.show_measure[TypeMeasure::Velocity],
    "Откл", "Вкл"
)

DEF_CHOICE_2(chTemperature,
    "Температура",
    pageMeasures,
    gset.display.show_measure[TypeMeasure::Temperature],
    "Откл", "Вкл"
)

DEF_CHOICE_2(chHumidity,
    "Влажность",
    pageMeasures,
    gset.display.show_measure[TypeMeasure::Humidity],
    "Откл", "Вкл"
)

static void CloseMeasures()
{
    PageDisplay::PageMeasures::self->Close();
};

DEF_BUTTN(bCloseMeasures,
    "Закрыть",
    pageMeasures,
    CloseMeasures
)

DEF_PAGE_6(pageMeasures,
    "ИЗМЕРЕНИЯ",
    pageDisplay,
    chPressure,
    chIllumination,
    chVelocity,
    chTemperature,
    chHumidity,
    bCloseMeasures
)


void ClosePageDisplay()
{
    PageDisplay::self->Close();
}


static const DButton bClosePageDisplay =
{
    TypeItem::Button,
    "Закрыть", (const Page *)&pageDisplay, ClosePageDisplay
};


static const Item * const itemsDisplay[] =
{
    (Item *)&pageMeasures,
    (Item *)&bClosePageDisplay,
    nullptr
};


static uint8 ciPageDisplay = 0;


const DPage pageDisplay =
{
    TypeItem::Page,
    "ДИСПЛЕЙ",
    (const Page *)&pageMain,
    itemsDisplay,
    &ciPageDisplay
};


const Page * const PageDisplay::self = (const Page *)&pageDisplay;
const Page * const PageDisplay::PageMeasures::self = (const Page *)&pageMeasures;
