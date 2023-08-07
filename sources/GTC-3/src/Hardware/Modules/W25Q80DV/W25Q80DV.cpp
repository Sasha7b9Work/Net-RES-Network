// 2023/08/07 09:57:09 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Hardware/Modules/W25Q80DV/W25Q80DV.h"
#include "Hardware/HAL/HAL.h"
#include "Utils/Buffer.h"
#include <cstdlib>


/*
*   Block 0
*   Sector 0
*   Адреса 000000h - 0000FFh
*/

//                            page
#define PROGRAM_PAGE  0x02  /* 34 */
#define READ_DATA     0x03  /* 26 */
#define WRITE_DISABLE 0x04  /* 23 */
#define READ_STATUS_1 0x05  /* 24 */
#define WRITE_ENABLE  0x06  /* 22 */
#define SECTOR_ERASE  0x20  /* 36 */


namespace W25Q80DV
{
    // Записывает uin8, а затем младшие 3 байта из второго значения
    static void Write32bit(uint8, uint);

    static bool IsBusy();

    static void WaitRelease();
}


void W25Q80DV::Write1024bytes(const uint8 *buffer, int size)
{
    WaitRelease();

    HAL_SPI1::Write(WRITE_ENABLE);                          // Write enable

    Write32bit(SECTOR_ERASE, 0x000000);                     // Sector erase

    HAL_SPI1::Write(WRITE_DISABLE);                         // Write disable

    WaitRelease();

    HAL_SPI1::Write(WRITE_ENABLE);                          // Write enable

    Buffer<uint8, 1024> data;

    data[0] = PROGRAM_PAGE; //-V525
    data[1] = 0;                // \ 
    data[2] = 0;                // | Адрес
    data[3] = 0;                // /

    for (int i = 0; i < size; i++)
    {
        data[4 + i] = buffer[i];
    }

    //                                                       команда   адрес
    HAL_SPI1::Write(data.Data(), size + 1 + 3);     // Page program

    HAL_SPI1::Write(WRITE_DISABLE);              // Write disable
}


void W25Q80DV::Read1024bytes(uint8 *buffer, int size)
{
    WaitRelease();

    Buffer<uint8, 1024> out;

    out[0] = READ_DATA; //-V525
    out[1] = 0;
    out[2] = 0;
    out[3] = 0;

    Buffer<uint8, 1024> in;

    HAL_SPI1::WriteRead(out.Data(), in.Data(), size + 1 + 3);

    for (int i = 0; i < size; i++)
    {
        buffer[i] = in[4 + i];
    }
}


void W25Q80DV::ReadID()
{

}


void W25Q80DV::ErasePageForAddress(uint address)
{

}


void W25Q80DV::Write(uint address, uint8 byte)
{

}


uint8 W25Q80DV::Read(uint address)
{
    return 0;
}


bool W25Q80DV::Test()
{
    ErasePageForAddress(0);

    for (int i = 0; i < 100; i++)
    {
        uint8 byte = (uint8)std::rand();

        Write(0, byte);

        if (byte != Read(0))
        {
            return false;
        }
    }

    return true;
}
