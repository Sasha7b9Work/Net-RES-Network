// 2023/12/22 11:26:44 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Modules/W25Q80DV/W25Q80DV.h"
#include <cstring>


template void W25Q80DV::ReadBuffer<36>(uint address, void *buffer);


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


template<int count>
void W25Q80DV::WriteBuffer(uint address, const void *_buffer)
{
    uint end = address + size;

    const uint8 *pointer = (const uint8 *)_buffer;

    while (address < end)
    {
        buffer[address++] = *pointer++;
    }
}


template<int count>
void W25Q80DV::ReadBuffer(uint address, void *out)
{
    std::memcpy(out, &buffer[address], (uint)count);
}


void W25Q80DV::ErasePage(int num_page)
{
    uint address = num_page * SIZE_PAGE;
    uint end = address + SIZE_PAGE;

    while (address < end)
    {
        buffer[address++] = 0xFF;
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
