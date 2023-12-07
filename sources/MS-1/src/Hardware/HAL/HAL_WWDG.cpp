// 2023/12/07 16:56:41 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Hardware/HAL/HAL.h"
#include <stm32f3xx_hal.h>


namespace HAL_WWDG
{
    static WWDG_HandleTypeDef handle =
    {
        WWDG,
        {
            WWDG_PRESCALER_8,
            0x50,
            0x7F,
            WWDG_EWI_DISABLE
        }
    };
}


void HAL_WWDG::Init()
{
    HAL_WWDG_Init(&handle);
}


void HAL_WWDG::Update()
{
    HAL_WWDG_Refresh(&handle);
}
