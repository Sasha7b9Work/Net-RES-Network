// 2023/08/07 09:56:54 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


namespace W25Q80DV
{
    // Размер буфера ограничен 1024 байтами
    void Write1024bytes(uint address, const uint8 *buffer, int size);

    // Размер буфера ограничен 1024 байтами
    void Read1024bytes(uint address, uint8 *buffer, int size);

    void ReadID(uint8 id[2]);

    // Стереть страницу, которой принадлежит address
    void EraseSectorForAddress(uint address);

    void Write(uint address, uint8 byte);

    uint8 Read(uint address);

    namespace Test
    {
        void Run();

        bool Result();
    }
}
