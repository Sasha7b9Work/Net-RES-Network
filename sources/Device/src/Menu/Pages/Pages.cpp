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

DEF_BUTTN(bCloseMainPage,
    "Закрыть",
    pageMain,
    CloseMainPage
)

DEF_PAGE_3(pageMain,
    "МЕНЮ",
    Page::Empty,
    pageDisplay,
    pageHC12,
    bCloseMainPage
)



const Page * const PageMain::self = (const Page *)&pageMain;
