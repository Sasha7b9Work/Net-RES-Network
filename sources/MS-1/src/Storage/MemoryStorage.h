// 2023/09/08 22:13:56 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Storage/Storage.h"


struct Record
{
    // address - по этому адресу во внешней памяти хранится запись
    Record(uint _address) : address(_address) { }

    Measurements measurements;
    uint         address;

    Measurements &GetMeasurements()
    {
        static Measurements prev_meas;          // Здесь последние считанные измерения
        static uint prev_address = (uint)-1;    // Здесь адрес, откуда считаны последние измерения

        if (address != prev_address)
        {
            prev_address = address;

            W25Q80DV::ReadLess1024bytes(address, &prev_meas, sizeof(Measurements));
        }

        return prev_meas;
    }

    int GetNumber()
    {
        return GetMeasurements().number;
    }

    uint Begin()
    {
        return address;
    }

    uint End()
    {
        return Begin() + sizeof(Measurements);     // Четыре байта для записи проверочного нуля
    }

    void Write(const Measurements &meas)
    {
        meas.WriteToMemory(address);
    }

    bool IsEmpty()                                                  // Сюда может быть произведена запись
    {
        for (uint p = Begin(); p < End(); p += 4)
        {
            if (W25Q80DV::ReadUInt(p) != (uint)(-1))
            {
                return false;
            }
        }

        return true;
    }

    bool IsErased()                         // Запись стёрта
    {
        return GetMeasurements().number == 0;
    }

    bool IsCorrectData()
    {
        Measurements &meas = GetMeasurements();

        if (meas.number == -1 ||        // Ничего не было записано
            meas.number == 0 ||         // Стёрто
            meas.control_field != 0     // Не записано полностью
            )
        {
            return false;
        }

        return (meas.GetCRC() == meas.CalculateCRC());
    }

    void Erase()
    {
        W25Q80DV::WriteUInt((uint)Begin(), 0);
    }

    static bool Oldest(Record *record);

    static bool Newest(Record *record);

    bool operator<(const Record &rhs)
    {
        return address < rhs.address;
    }

    void operator++(int /*i*/)
    {
        address += 4;
    }
};


namespace MemoryStorage
{
    void Init();

    void Append(Measurements &);

    // Возвращает указатель на самую старую структуру данных (которая считана раньше всех). После использования нужно вызвать Erase()
    // с этим указателем, чтобы стереть структуру из хранилища
    bool GetOldest(Record *record);

    void Erase(Record *);

    bool Test();
};
