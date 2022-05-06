// 2022/05/05 12:26:53 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Pages/Pages.h"


extern const DPage pageMain;
extern const DPage pageDisplay;
extern const DPage pageHC12;


static void CloseMainPage()
{
    PageMain::self->Close();
}


static const DButton bCloseMainPage =
{
    TypeItem::Button,
    "Закрыть",
    (const Page *)&pageMain,
    CloseMainPage
};


static const Item *items[] =
{
    (const Page *)&pageDisplay,
    (const Page *)&pageHC12,
    (Item *)&bCloseMainPage,
    nullptr
};


static uint8 ciPageMain = 0;


const DPage pageMain =
{
    TypeItem::Page,
    "МЕНЮ",
    nullptr,
    items,
    &ciPageMain
};


const Page * const PageMain::self = (const Page *)&pageMain;
