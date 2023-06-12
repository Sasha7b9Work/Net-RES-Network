// 2022/08/04 14:32:05 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Pages/Pages.h"
#include "Settings/Settings.h"
#include "Hardware/HAL/HAL.h"


extern const DPage pageMain;


static int cur_field = 0;
static int state = 0;
static PackedTime time;

static void Before_OpenTime(bool open)
{
    if (open)
    {
        time = HAL_RTC::GetTime();
    }
}

DEF_TIMEITEM(tTime, *PageSystem::self, Before_OpenTime, cur_field, state, time)


DEF_GOVERNOR(gSerialNumber,
    "С/Н",
    *PageSystem::self,
    EmptyFuncOpenClose,
    0, (int)0x7FFFFFFF,
    gset.system.serial_number
)


void ClosePageSystem(bool)
{
    PageSystem::self->Close();
}


DEF_BUTTN(bClosePageSystem,
    "Закрыть",
    *PageSystem::self,
    ClosePageSystem,
    nullptr
);


DEF_PAGE_3(pageSystem, //-V1027
    "СИСТЕМА",
    pageMain,
    EmptyFuncOpenClose,
    tTime,
    gSerialNumber,
    bClosePageSystem
)


const Page *const PageSystem::self = (const Page *)&pageSystem;
