// 2023/09/08 22:13:56 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Storage/Storage.h"
#include "Modules/W25Q80DV/W25Q80DV.h"


struct Record
{
private:

    uint  address;

    Measurements measurements;
    uint         address_meas = (uint)-1;       // Если address_meas != address, то нужно загрузить

public:
    // address - по этому адресу во внешней памяти хранится запись
    Record(uint _address) : address(_address) { }

    Measurements &GetMeasurements()
    {
        if (address != address_meas)
        {
            address_meas = address;

            W25Q80DV::ReadLess1024bytes(address, &measurements, sizeof(Measurements));
        }

        return measurements;
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
        measurements = meas;
        measurements.crc = measurements.CalculateCRC();
        address_meas = address;

        W25Q80DV::WriteLess1024bytes(address, &measurements, (int)sizeof(Measurements));
    }

    bool IsEmpty()                                                  // Сюда может быть произведена запись
    {
        static bool first = true;
        static Measurements zero_meas;

        if (first)
        {
            first = false;

            std::memset(&zero_meas, 0xFF, sizeof(Measurements));
        }

        return std::memcmp(&GetMeasurements(), &zero_meas, sizeof(Measurements)) == 0;
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

        uint old_CRC = meas.crc;
        uint new_CRC = meas.CalculateCRC();

        return (old_CRC == new_CRC);
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

    void operator++(int)
    {
        address += sizeof(Measurements);
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
