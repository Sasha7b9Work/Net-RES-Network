// 2024/01/18 11:45:50 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Pages/Pages.h"


extern const DPage pageMain;


static void ClosePageDataBase(bool)
{
    PageDataBase::self->Close();
}


DEF_BUTTON(bClosePageDataBase,
    "Çàêğûòü",
    *PageDataBase::self,
    ClosePageDataBase,
    nullptr,
    nullptr
)


DEF_PAGE_1(pageDataBase,
    "ÁÀÇÀ ÄÀÍÍÛÕ",
    pageMain,
    nullptr,
    nullptr,
    bClosePageDataBase
)


const Page *const PageDataBase::self = (const Page *)&pageDataBase;
