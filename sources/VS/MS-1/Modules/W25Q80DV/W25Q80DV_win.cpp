// 2023/12/22 11:26:44 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Modules/W25Q80DV/W25Q80DV.h"


namespace W25Q80DV
{
    static uint8 buffer[SIZE];
}


void W25Q80DV::Init()
{
    for (uint i = 0; i < SIZE; i++)
    {
        buffer[i] = 0xFF;
    }
}


void W25Q80DV::WriteLess1024bytes(uint address, const void *_buffer, int size)
{
    uint end = address + size;

    const uint8 *pointer = (const uint8 *)_buffer;

    while (address < end)
    {
        buffer[address++] = *pointer++;
    }
}


void W25Q80DV::ReadLess1024bytes(uint address, void *_buffer, int size)
{
    uint end = address + size;

    uint8 *pointer = (uint8 *)_buffer;

    while (address < end)
    {
        *pointer++ = buffer[address++];
    }
}


void W25Q80DV::ErasePage(int num_page)
{
    uint address = num_page * SIZE_PAGE;
    uint end = address + SIZE_PAGE;

    while (address < end)
    {
        buffer[address++] = 0x0;
    }
}


void W25Q80DV::WriteUInt(uint address, uint value)
{
    BitSet32 data(value);

    buffer[address++] = data.bytes[0];
    buffer[address++] = data.bytes[1];
    buffer[address++] = data.bytes[2];
    buffer[address++] = data.bytes[3];
}


uint W25Q80DV::ReadUInt(uint address)
{
    BitSet32 data(0);

    data.bytes[0] = buffer[address++];
    data.bytes[1] = buffer[address++];
    data.bytes[2] = buffer[address++];
    data.bytes[3] = buffer[address++];

    return data.word;
}
