// 2022/08/04 14:32:05 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Pages/Pages.h"
#include "Settings/Settings.h"


extern const DPage pageMain;


static int cur_field = 0;
static int state = 0;
static bool prev_opened = false;

DEF_TIMEITEM(tTime, *PageSystem::self, cur_field, state, prev_opened)


DEF_GOVERNOR(gSerialNumber,
    "С/Н",
    *PageSystem::self,
    0, (int)0x7FFFFFFF,
    gset.system.serial_number
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


DEF_PAGE_3(pageSystem, //-V1027
    "СИСТЕМА",
    pageMain,
    tTime,
    gSerialNumber,
    bClosePageSystem
)


const Page *const PageSystem::self = (const Page *)&pageSystem;
