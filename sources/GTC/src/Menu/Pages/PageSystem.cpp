// 2022/08/04 14:32:05 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Pages/Pages.h"
#include "Settings/Settings.h"
#include "Hardware/HAL/HAL.h"


extern const DPage pageMain;


static int cur_field = 0;
static int state = 0;
static PackedTime time;
static TimeMeterMS meter;

static void Before_OpenTime()
{
    time = HAL_RTC::GetTime();
}

DEF_TIMEITEM(tTime, *PageSystem::self, Before_OpenTime, cur_field, state, time, meter)


DEF_GOVERNOR(gSerialNumber,
    "С/Н",
    *PageSystem::self,
    EmptyVV,
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
    EmptyVV,
    ClosePageSystem
);


DEF_PAGE_3(pageSystem, //-V1027
    "СИСТЕМА",
    pageMain,
    EmptyVV,
    tTime,
    gSerialNumber,
    bClosePageSystem
)


const Page *const PageSystem::self = (const Page *)&pageSystem;
