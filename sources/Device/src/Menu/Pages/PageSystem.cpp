// 2022/08/04 14:32:05 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Pages/Pages.h"


static int serialNumber = 0;

extern const DPage pageMain;


DEF_GOVERNOR(gSerialNumber,
    "С/Н",
    *PageSystem::self,
    0, (int)0xFFFFFFFF,
    serialNumber
)


void ClosePageSystem()
{
    PageSystem::self->Close();
}


DEF_BUTTN(bClosePageSystem,
    "Закрыть",
    *PageSystem::self,
    ClosePageSystem
);


DEF_PAGE_2(pageSystem, //-V1027
    "СИСТЕМА",
    pageMain,
    gSerialNumber,
    bClosePageSystem
)


const Page *const PageSystem::self = (const Page *)&pageSystem;
