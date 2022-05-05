// 2022/05/05 13:14:44 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Pages/Pages.h"


static uint8 measurePressure;


static Choice choicePressure
(
    "Давление", PageDisplay::self, &measurePressure, 2
);


static const Item *items[] =
{
    &choicePressure,
    nullptr
};


static Page pageDisplay
(
    "ДИСЛЕЙ",
    MainPage::self,
    items
);


Page *PageDisplay::self = &pageDisplay;
