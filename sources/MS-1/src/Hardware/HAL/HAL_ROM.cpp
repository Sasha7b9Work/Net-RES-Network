// 2023/06/05 14:51:25 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Hardware/HAL/HAL.h"
#include "Utils/Math.h"
#include <stm32f3xx_hal.h>
#include <cstring>


static const uint ADDR_FLASH_SECTOR_63 = ((uint)0x0801F800);
static const uint ADDR_SECTOR_SETTINGS = ADDR_FLASH_SECTOR_63;


bool HAL_ROM::LoadSettings(Settings *settings)
{
    uint *pointer = (uint *)(ADDR_SECTOR_SETTINGS); //-V566

    if (*pointer == (uint)(-1))
    {
        return false;
    }

    std::memcpy(settings, (const void *)(ADDR_SECTOR_SETTINGS), sizeof(Settings)); //-V566

    return true;
}


void HAL_ROM::SaveSettings(const Settings *settings)
{
    HAL_FLASH_Unlock();

    FLASH_EraseInitTypeDef itd =
    {
        FLASH_TYPEERASE_PAGES,
        ADDR_SECTOR_SETTINGS,
        1
    };

    uint error = 0;

    if (HAL_FLASHEx_Erase(&itd, &error) != HAL_OK)
    {
        error = error;
    }

    uint address = ADDR_SECTOR_SETTINGS;

    uint *data = (uint *)settings;

    for (uint i = 0; i < (sizeof(Settings) / sizeof(uint) + 1); i++)
    {
        if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, address, *data) != HAL_OK)
        {
            address = address;
        }
        address += 4;
        data++;
    }

    HAL_FLASH_Lock();
}

