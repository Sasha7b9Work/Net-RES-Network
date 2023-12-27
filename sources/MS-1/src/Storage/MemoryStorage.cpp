// 2023/09/08 22:14:01 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Storage/MemoryStorage.h"
#include "Hardware/Timer.h"


namespace MemoryStorage
{
    struct Page
    {
        static const int SIZE = W25Q80DV::SIZE_PAGE;

        Page(uint _address) : address(_address) { }

    private:

        uint address;
    };

    // Сюда считываем много памяти, чтобы потом работать с ОЗУ
    namespace Cache
    {
        static const int SIZE = 8 * 1024;
        static uint8 buffer[SIZE] __attribute__((section("CCM_DATA")));

        static uint begin = (uint)-1;               // Начало памяти в кеше

        static bool IsDirty()
        {
            return begin >= W25Q80DV::SIZE;
        }

        static uint End()
        {
            uint end = begin + SIZE;

            if (end > W25Q80DV::SIZE)
            {
                end = W25Q80DV::SIZE;
            }

            return end;
        }

        static void MarkAsDirty()
        {
            begin = (uint)-1;
        }

        // Возвращает true, если содержит память из адреса address, размером size
        static bool Consist(uint address, int size)
        {
            if (IsDirty() || begin > address)
            {
                return false;
            }

            return address + (uint)size < End();
        }

        static void Fill(uint address)
        {
            begin = address;

            uint size = W25Q80DV::SIZE - begin;

            if (size > SIZE)
            {
                size = SIZE;
            }

            W25Q80DV::ReadBuffer<SIZE>(begin, buffer);
        }

        static void Read(uint address, void *out, int size)
        {
            if (!Consist(address, size))
            {
                Fill(address);
            }

            uint shift = address - begin;

            std::memcpy(out, &buffer[shift], (uint)size);
        }
    }

    static Record first_record((uint)-1);
    static Record last_record((uint)-1);
}


void MemoryStorage::Init()
{
    uint time_start = TIME_MS;

    for (uint address = 0; address < W25Q80DV::SIZE; address += Record::SIZE)
    {
        Record record(address);

        if (record.IsExist())
        {
            if (!record.IsEmpty())                      // Если сюда уже что-то было записано
            {
                if (!record.IsErased())                 // И не стёрто
                {
                    if (record.IsCorrect())
                    {                                   // Корректируем первую и последнюю записи
                        if (!first_record.IsExist())
                        {
                            first_record = record;
                        }

                        if (!last_record.IsExist())
                        {
                            last_record = record;
                        }

                        if (record > last_record)
                        {
                            last_record = record;
                        }

                        if (record < first_record)
                        {
                            first_record = record;
                        }
                    }
                    else
                    {
                        record.Erase();         // Стираем некорректную запись
                    }
                }
            }
        }
    }

    uint time = TIME_MS - time_start;

    time = time;
}


void MemoryStorage::Append(Measurements &)
{

}


bool Record::IsEmpty()
{
    static bool first = true;
    static Measurements empty_meas;

    if (first)
    {
        first = false;

        std::memset(&empty_meas, 0xFF, sizeof(empty_meas));
    }

    Measurements &meas = GetMeasurements();

    return std::memcmp(&meas, &empty_meas, sizeof(meas)) == 0;
}


bool Record::IsErased()
{
    return GetMeasurements().number == 0;
}


bool Record::IsCorrect()
{
    Measurements &meas = GetMeasurements();

    return (meas.control_field == 0) && (meas.CalculateCRC() == meas.crc);
}


void Record::Erase()
{
    W25Q80DV::WriteUInt(address, 0);

    if (MemoryStorage::Cache::Consist(address, sizeof(uint)))
    {
        MemoryStorage::Cache::MarkAsDirty();
    }
}


Measurements &Record::GetMeasurements()
{
    return value_meas.GetMeasurements(address);
}


Measurements &Record::ValueMeasurements::GetMeasurements(uint addr)
{
    if (!is_valid)
    {
        is_valid = true;

        MemoryStorage::Cache::Read(addr, &measurements, sizeof(measurements));
    }

    return measurements;
}
