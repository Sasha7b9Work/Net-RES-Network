// 2022/05/05 13:14:44 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Pages/Pages.h"
#include "Settings/Settings.h"


static Choice choicePressure
(
    "Äàâëåíèå", PageDisplay::self, &gset.display.show_measure[TypeMeasure::Pressure], 2
);


static Item *items[] =
{
    &choicePressure,
    nullptr
};


static Page pageDisplay
(
    "ÄÈÑÏËÅÉ",
    MainPage::self,
    items
);


Page *PageDisplay::self = &pageDisplay;
