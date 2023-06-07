// 2023/06/05 14:51:25 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Hardware/HAL/HAL.h"
#include "Utils/Math.h"
#include <stm32f1xx_hal.h>


/*
* Настройки хранятся в верхних 4 кБ памяти
*/


namespace HAL_ROM
{
    #define ADDR_FLASH_PAGE_60    ((uint)0x0800F000) /* Base @ of Page 60, 1 Kbytes */
    #define ADDR_FLASH_PAGE_61    ((uint)0x0800F400) /* Base @ of Page 61, 1 Kbytes */
    #define ADDR_FLASH_PAGE_62    ((uint)0x0800F800) /* Base @ of Page 62, 1 Kbytes */
    #define ADDR_FLASH_PAGE_63    ((uint)0x0800FC00) /* Base @ of Page 63, 1 Kbytes */

    #define SIZE_SECTOR 1024

    #define ADDR_BEGIN  ADDR_FLASH_PAGE_60
    #define ADDR_END    (ADDR_FLASH_PAGE_63 + (SIZE_SECTOR))

    #define SIZE_SETTINGS   256


    // Возвращает адрес последних сохранённых настроек. Если настройки не сохранялись, возвращает 0
    static uint LastRecord();

    static void EraseAll();

    // Возвращает false в случае неудачи (контрольная сумма не совпадает или целевое место не пустое)
    static bool Save(uint address, const Settings &set);
}



void HAL_ROM::SaveSettings(const Settings &set)
{
    uint addr_last = LastRecord();

    uint addr_rec = addr_last + SIZE_SETTINGS;

    if (addr_last == 0)
    {
        addr_rec = ADDR_BEGIN;
    }

    if (addr_last == ADDR_END - SIZE_SETTINGS)
    {
        EraseAll();

        addr_rec = ADDR_BEGIN;
    }


}


bool HAL_ROM::LoadSettings(Settings &set)
{
    uint address = LastRecord();

    if (address == 0)
    {
        return false;
    }

    while (address >= ADDR_BEGIN)
    {
        uint crc = Math::CalculateCRC((const void *)(address + 4), (int)sizeof(set));

        if (crc == *((uint *)address))
        {
            std::memcpy(&set, (const void *)address, (int)sizeof(set));

            return true;
        }

        address -= SIZE_SETTINGS;
    }

    return false;
}


uint HAL_ROM::LastRecord()
{
    uint address = ADDR_BEGIN;

    while (address < ADDR_END)
    {
        uint value = *((uint *)address);

        if (value == (uint)(-1))
        {
            return (address == ADDR_BEGIN) ? 0 : (address - SIZE_SETTINGS);
        }

        address += SIZE_SETTINGS;
    }

    return ADDR_END - SIZE_SETTINGS;
}


void HAL_ROM::EraseAll()
{
    uint error = 0;
    FLASH_EraseInitTypeDef is;

    is.TypeErase = FLASH_TYPEERASE_PAGES;
    is.PageAddress = ADDR_BEGIN;
    is.NbPages = 4;

    HAL_FLASH_Unlock();

    if (HAL_FLASHEx_Erase(&is, &error) != HAL_OK)
    {
        error = error;
    }

    HAL_FLASH_Lock();
}
