// 2022/08/04 14:32:05 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Pages/Pages.h"


void ClosePageSystem()
{
    PageSystem::self->Close();
}


DEF_BUTTN(bClosePageSystem,
    "Закрыть",
    *PageSystem::self,
    ClosePageSystem
);


DEF_PAGE_1(pageSystem,
    "Система",
    *PageMain::self,
    bClosePageSystem
)


const Page *const PageSystem::self = (const Page *)&pageSystem;
