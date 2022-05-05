// 2022/05/05 12:26:53 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Pages/Pages.h"


static const Item *items[] =
{
    PageDisplay::self,
    nullptr
};


static Page pageMain
(
    "Μενώ",
    nullptr,
    items
);


const Page *MainPage::self = &pageMain;
