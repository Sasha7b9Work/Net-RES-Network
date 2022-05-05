// 2022/05/05 14:53:43 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Pages/Pages.h"


void ClosePageHC12()
{
    PageHC12::self->Close();
}


static const Button bClosePageHC12
(
    "Закрыть", PageHC12::self, ClosePageHC12
);


static const Item *items[] =
{
    &bClosePageHC12,
    nullptr
};


static uint8 ciPageHC12 = 0;


static const Page pageHC12
(
    "HC12",
    PageMain::self,
    items,
    &ciPageHC12
);


const Page * const PageHC12::self = &pageHC12;
