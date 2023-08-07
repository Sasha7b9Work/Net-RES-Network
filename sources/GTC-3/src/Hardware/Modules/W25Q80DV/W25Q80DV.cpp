// 2023/08/07 09:57:09 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Hardware/Modules/W25Q80DV/W25Q80DV.h"
#include <cstdlib>


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
