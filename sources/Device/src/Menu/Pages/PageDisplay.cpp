// 2022/05/05 13:14:44 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Pages/Pages.h"
#include "Settings/Settings.h"


extern const DPage pageMain;
extern const DPage pageDisplay;
extern const DPage pageMeasures;


//static const DChoice chPressure =
//{
//    TypeItem::Choice,
//    "Давление",
//    (const Page *)&pageMeasures,
//    &gset.display.show_measure[TypeMeasure::Pressure], 2,
//    "Откл", "Вкл"
//};


DEF_CHOICE_2( chPressure,
    "Давление",
    pageMeasures,
    gset.display.show_measure[TypeMeasure::Pressure],
    "Откл", "Вкл"
)


static const DChoice chIllumination =
{
    TypeItem::Choice,
    "Освещённость",
    (const Page *)&pageMeasures,
    &gset.display.show_measure[TypeMeasure::Illumination], 2,
    "Откл", "Вкл"
};

static const DChoice chVelocity =
{
    TypeItem::Choice,
    "Скорость",
    (const Page *)&pageMeasures,
    &gset.display.show_measure[TypeMeasure::Velocity], 2,
    "Откл", "Вкл"
};

static const DChoice chTemperature =
{
    TypeItem::Choice,
    "Температура",
    (const Page *)&pageMeasures,
    &gset.display.show_measure[TypeMeasure::Temperature], 2,
    "Откл", "Вкл"
};

static const DChoice chHumidity =
{
    TypeItem::Choice,
    "Влажность",
    (const Page *)&pageMeasures,
    &gset.display.show_measure[TypeMeasure::Humidity], 2,
    "Откл", "Вкл"
};

static void CloseMeasures()
{
    PageDisplay::PageMeasures::self->Close();
};


static const DButton bCloseMeasures =
{
    TypeItem::Button,
    "Закрыть", (const Page *)&pageMeasures, CloseMeasures
};


static const Item * const itemsMeasures[] =
{
    (Item *)&chPressure,
    (Item *)&chIllumination,
    (Item *)&chVelocity,
    (Item *)&chTemperature,
    (Item *)&chHumidity,
    (Item *)&bCloseMeasures,
    nullptr
};


static uint8 ciPageMeasures = 0;

const DPage pageMeasures =
{
    TypeItem::Page,
    "ИЗМЕРЕНИЯ",
    (const Page *)&pageDisplay,
    itemsMeasures,
    &ciPageMeasures
};


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
