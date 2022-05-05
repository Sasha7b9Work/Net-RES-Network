// 2022/05/05 14:53:43 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Pages/Pages.h"


static const Item *items[] =
{
    nullptr
};


static Page pageHC12
{
    "HC12",
    MainPage::self,
    items
};


Page *PageHC12::self = &pageHC12;
