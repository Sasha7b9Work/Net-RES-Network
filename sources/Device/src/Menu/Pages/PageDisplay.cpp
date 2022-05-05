// 2022/05/05 13:14:44 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Pages/Pages.h"
#include "Settings/Settings.h"


static Choice chPressure
(
    "Давление", PageDisplay::PageMeasures::self, &gset.display.show_measure[TypeMeasure::Pressure], 2,
    "Откл", "Вкл"
);

static Choice chIllumination
(
    "Освещённость", PageDisplay::PageMeasures::self, &gset.display.show_measure[TypeMeasure::Illumination], 2,
    "Откл", "Вкл"
);

static Choice chVelocity
(
    "Скорость", PageDisplay::PageMeasures::self, &gset.display.show_measure[TypeMeasure::Velocity], 2,
    "Откл", "Вкл"
);

static Choice chTemperature
(
    "Температура", PageDisplay::PageMeasures::self, &gset.display.show_measure[TypeMeasure::Temperature], 2,
    "Откл", "Вкл"
);

static Choice chHumidity
(
    "Влажность", PageDisplay::PageMeasures::self, &gset.display.show_measure[TypeMeasure::Humidity], 2,
    "Откл", "Вкл"
);

static void CloseMeasures()
{
    PageDisplay::PageMeasures::self->Close();
};


static Button bCloseMeasures
(
    "Закрыть", PageDisplay::PageMeasures::self, CloseMeasures
);


static Item *itemsMeasures[] =
{
    &chPressure,
    &chIllumination,
    &chVelocity,
    &chTemperature,
    &chHumidity,
    &bCloseMeasures,
    nullptr
};


static Page pageMeasures
(
    "ИЗМЕРЕНИЯ",
    PageDisplay::self,
    itemsMeasures
);


void ClosePageDisplay()
{
    PageDisplay::self->Close();
}


static Button bClosePageDisplay
(
    "Закрыть", PageDisplay::self, ClosePageDisplay
);


static Item *itemsDisplay[] =
{
    PageDisplay::PageMeasures::self,
    &bClosePageDisplay,
    nullptr
};


static Page pageDisplay
(
    "ДИСПЛЕЙ",
    PageMain::self,
    itemsDisplay
);


Page *PageDisplay::self = &pageDisplay;
Page *PageDisplay::PageMeasures::self = &pageMeasures;
