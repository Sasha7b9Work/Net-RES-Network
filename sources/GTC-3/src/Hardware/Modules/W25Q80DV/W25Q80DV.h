// 2023/08/07 09:56:54 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


namespace W25Q80DV
{
    // —тереть страницу, которой принадлежит address
    void ErasePageForAddress(uint address);

    void Write(uint address, uint8 byte);

    uint8 Read(uint address);

    bool Test();
}
