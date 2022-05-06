// 2022/05/05 14:53:43 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Pages/Pages.h"


extern const DPage pageHC12;
extern const DPage pageMain;


void ClosePageHC12()
{
    PageHC12::self->Close();
}


static const DButton bClosePageHC12 =
{
    TypeItem::Button,
    "Закрыть",
    (const Page *)&pageHC12,
    ClosePageHC12
};


static const Item * const items[] =
{
    (Item *)&bClosePageHC12,
    nullptr
};


static uint8 ciPageHC12 = 0;


const DPage pageHC12 =
{
    TypeItem::Page,
    "HC12",
    (const Page *)&pageMain,
    items,
    &ciPageHC12
};


const Page *const PageHC12::self = (const Page *)&pageHC12;
