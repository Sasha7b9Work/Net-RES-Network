// 2022/05/05 13:14:44 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Pages/Pages.h"
#include "Settings/Settings.h"


extern const DPage pageMain;


void ClosePageDisplay()
{
    PageDisplay::self->Close();
}

DEF_BUTTN( bClosePageDisplay,
    "Закрыть",
    *PageDisplay::self,
    EmptyVV,
    ClosePageDisplay
)

DEF_PAGE_1(pageDisplay, //-V1027
    "ДИСПЛЕЙ",
    pageMain,
    EmptyVV,
    bClosePageDisplay
)

const Page * const PageDisplay::self = (const Page *)&pageDisplay;
