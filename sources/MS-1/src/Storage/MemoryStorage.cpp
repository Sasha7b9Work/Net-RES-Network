// 2023/09/08 22:14:01 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Storage/MemoryStorage.h"
#include "Utils/Math.h"
#include "Hardware/Timer.h"
#include <cstring>
#include <cstdlib>


namespace MemoryStorage
{
    static const uint BEGIN = 0;
    static const uint END = 1024 * 1024;

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

        void Write(int number, Measurements &meas)
        {
            meas.number = number;
            meas.WriteToMemory(address);
            W25Q80DV::WriteUInt(address + sizeof(Measurements), 0);     // Записываем ноль для контроля записи
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

        bool IsValid()
        {
            Measurements &meas = GetMeasurements();

            if (meas.number == -1 || meas.number == 0 || meas.control_field != 0)
            {
                return false;
            }

            return (meas.GetCRC() == meas.CalculateCRC());
        }

        void Erase()
        {
            W25Q80DV::WriteUInt((uint)Begin(), 0);
        }

        static bool Oldest(Record *);

        static Record *Newest();

        static Record *ForMeasurements(const Measurements *);

        // Возвращает запись, следующую за номером prev_nubmer
        static Record *GetAfterNumber(int prev_number);

        bool operator<(const Record &rhs)
        {
            return address < rhs.address;
        }

        void operator++(int /*i*/)
        {
            address += 4;
        }
    };

    struct Page
    {
        void Init(int num_page)
        {
            startAddress = BEGIN + W25Q80DV::SIZE_PAGE * (uint)num_page;
        }

        Record FirstRecord()
        {
            return Record(startAddress);
        }

        int GetMaxRecordsCount() const
        {
            return W25Q80DV::SIZE_PAGE / sizeof(Record);
        }

        Record LastRecord()
        {
            return Record(startAddress + GetMaxRecordsCount() * sizeof(Record));
        }

        int GetRecordsCount()
        {
            int result = 0;

            for (Record record = FirstRecord(); record < LastRecord(); record++)
            {
                if (record.IsValid())
                {
                    result++;
                }
            }

            return result;
        }

        void Prepare()
        {
            for (Record record = FirstRecord(); record < LastRecord(); record++)
            {
                if (record.IsEmpty() || record.IsErased())
                {
                    continue;
                }

                if (!record.IsValid())
                {
                    record.Erase();
                }
            }
        }

        // Возвращает первую пригодную для записи страницу или nullptr, если все заняты
        static Page *GetFirstForRecord();

        // Возвращает страницу с самой старой записью
        static Page *GetWithOldestRecord();

        bool GetFirstEmptyRecord(Record *out)
        {
            for (Record record = FirstRecord(); record < LastRecord(); record++)
            {
                if (record.IsEmpty())
                {
                    *out = record;

                    return true;
                }
            }

            return false;
        }

        Record Append(Measurements &measurements);

        void Erase()
        {
            int num_page = (int)(startAddress / W25Q80DV::SIZE_PAGE);

            W25Q80DV::ErasePage(num_page);
        }

        bool IsEmpty()
        {
            for (Record record = FirstRecord(); record < LastRecord(); record++)
            {
                if (record.IsEmpty())
                {
                    continue;
                }

                return false;
            }

            return true;
        }

        int GetLastNumber()
        {
            int result = 0;

            for (Record record = FirstRecord(); record < LastRecord(); record++)
            {
                if (record.IsValid() && record.GetNumber() > result)
                {
                    result = record.GetNumber();
                }
            }

            return result;
        }

        bool GetOldestRecord(Record *out)
        {
            Record result(0);

            bool exist = false;     // Если true, то в result уже что-то записано

            for (Record record = FirstRecord(); record < LastRecord(); record++)
            {
                if (record.IsValid())
                {
                    if (!exist || (record.GetNumber() < result.GetNumber()))
                    {
                        exist = true;

                        result = record;
                    }
                }
            }

            if (exist)
            {
                *out = result;
            }

            return exist;
        }

        // Возвращает запись с минимальным относительно num_record номером
        bool GetMinRecord(int num_record, Record *out)
        {
            Record result(0);

            bool exist = false;     // Если true, то в result уже что-то записано

            for (Record record = FirstRecord(); record < LastRecord(); record++)
            {
                if (record.IsValid())
                {
                    if (exist)
                    {
                        if (record.GetNumber() >= num_record && record.GetNumber() < result.GetNumber())
                        {
                            result = record;
                        }
                    }
                    else
                    {
                        if (record.GetNumber() >= num_record)
                        {
                            exist = true;

                            result = record;
                        }
                    }
                }
            }

            if (exist)
            {
                *out = result;
            }

            return exist;
        }

        bool GetNewestRecord(Record *out)
        {
            Record result(0);

            bool exist = false;     // Если true, то в result уже что-то записано

            for (Record record = FirstRecord(); record < LastRecord(); record++)
            {
                if (record.IsValid())
                {
                    if (!exist || (record.GetNumber() > result.GetNumber()))
                    {
                        result = record;
                    }
                }
            }

            if (exist)
            {
                *out = result;
            }

            return exist;
        }

    private:

        uint startAddress;
    };

    static const int NUM_PAGES = (END - BEGIN) / W25Q80DV::SIZE_PAGE;

    static Page pages[NUM_PAGES];

    static int GetNewNumber()
    {
        int result = 0;

        for (int i = 0; i < NUM_PAGES; i++)
        {
            Page &page = pages[i];

            if (page.IsEmpty())
            {
                continue;
            }

            if (page.GetLastNumber() > result)
            {
                result = page.GetLastNumber();
            }
        }

        return result + 1;
    }

    Page *Page::GetWithOldestRecord()
    {
        Page *result = nullptr;

        for (int i = 0; i < NUM_PAGES; i++)
        {
            Page &page = pages[i];

            if (page.IsEmpty())
            {
                continue;
            }

            int last_number = page.GetLastNumber();

            if (last_number != 0)
            {
                if (!result || (last_number < result->GetLastNumber()))
                {
                    result = &page;
                }
            }
        }

        return result;
    }

    Page *Page::GetFirstForRecord()
    {
        for (int i = 0; i < NUM_PAGES; i++)
        {
            Record record(0);

            if (pages[i].GetFirstEmptyRecord(&record))
            {
                return &pages[i];
            }
        }

        return nullptr;
    }

    Record Page::Append(Measurements &measurements)
    {
        Record record(0);

        if (!GetFirstEmptyRecord(&record))
        {
            Erase();

            record = FirstRecord();
        }

        record.Write(GetNewNumber(), measurements);

        return record;
    }

    // Проверить все сектора на предмет повреждённых записей и стереть их
    static void Prepare();

    int NumberOldestRecord();
    int NumberNewestRecord();

    static int GetRecordsCount();
}


void MemoryStorage::Init()
{
    for (int i = 0; i < NUM_PAGES; i++)
    {
        pages[i].Init(i);
    }

    Prepare();
}


void MemoryStorage::Erase(const Measurements *meas)
{
    Record::ForMeasurements(meas)->Erase();
}


void MemoryStorage::Append(Measurements &meas)
{
    Page *page = Page::GetFirstForRecord();

    if (!page)
    {
        page = Page::GetWithOldestRecord();
    }

    page->Append(meas);
}


bool MemoryStorage::GetOldest(Measurements *meas)
{
    Record record(0);

    if (Record::Oldest(&record))
    {
        Measurements::CopyFromMemory(record.address, meas);

        return true;
    }

    return false;
}


bool MemoryStorage::GetNext(Measurements *meas, int number_prev)
{
    if (number_prev == -1)
    {
        return false;
    }

    if (Record::Newest()->number <= number_prev)
    {
        return false;
    }

    Record *record = Record::GetAfterNumber(number_prev);

    if (number)
    {
        *number = record ? record->number : -1;
    }

    if (record)
    {
        Measurements::CopyFromMemory(&record->measurements, meas);
    }

    return (record != nullptr);
}


void MemoryStorage::Prepare()
{
    for (int i = 0; i < NUM_PAGES; i++)
    {
        pages[i].Prepare();
    }
}


MemoryStorage::Record *MemoryStorage::Record::Oldest()
{
    Record *result = nullptr;

    for (int i = 0; i < NUM_PAGES; i++)
    {
        Record *oldest = pages[i].GetOldestRecord();

        if (oldest)
        {
            if (!result || oldest->number < result->number)
            {
                result = oldest;
            }
        }
    }

    return result;
}


MemoryStorage::Record *MemoryStorage::Record::GetAfterNumber(int prev_number)
{
    int min_number = prev_number + 1;       // Минимально возможный номер возвращаемой записи

    Record *result = nullptr;

    for (int i = 0; i < NUM_PAGES; i++)
    {
        Page &page = pages[i];

        Record *newest = page.GetOldestRecord();

        if (!newest)
        {
            continue;
        }
        else if(newest->number < min_number)
        {
            continue;
        }

        // В этой странице есть записи, которые больше либо равны min_number

        Record *record = page.GetMinRecord(min_number);

        if (record)
        {
            if (!result || (record->number < result->number))
            {
                result = record;
            }
        }
    }

    return result;
}


MemoryStorage::Record *MemoryStorage::Record::Newest()
{
    Record *result = nullptr;

    for (int i = 0; i < NUM_PAGES; i++)
    {
        Record *newest = pages[i].GetNewestRecord();

        if (newest)
        {
            if (!result || newest->number > result->number)
            {
                result = newest;
            }
        }
    }

    return result;
}


int MemoryStorage::NumberOldestRecord()
{
    Record *record = Record::Oldest();

    return record ? record->number : 0;
}


int MemoryStorage::NumberNewestRecord()
{
    Record *record = Record::Newest();

    return record ? record->number : 0;
}


int MemoryStorage::GetRecordsCount()
{
    int result = 0;

    for (int i = 0; i < NUM_PAGES; i++)
    {
        result += pages[i].GetRecordsCount();
    }

    return result;
}


MemoryStorage::Record *MemoryStorage::Record::ForMeasurements(const Measurements *meas)
{
    uint *pointer = (uint *)meas;

    pointer--;

    return (MemoryStorage::Record *)pointer;
}


namespace MemoryStorage
{
    namespace NSTest
    {
        static void AppendMeasure()
        {
//            Measurements meas = Storage::GetFullMeasurements();
        }

        static void Fill()
        {
            const int num_records = 1150 * 10;

            for (int i = 0; i < num_records; i++)
            {
                AppendMeasure();
            }
        }

        // Повредить хранилище
        static void Corrupt()
        {
            for (int i = 0; i < 100; i++)
            {
                uint value = 0;
                uint address = 0;

                while (value == 0)
                {
                    address = BEGIN + (uint)std::rand() % (END - BEGIN);

                    address &= 0xFFFFFFFFFC;

                    value = *((uint *)address);
                }

                value = 0;

                W25Q80DV::WriteUInt(address, value);

                Prepare();
            }
        }

        static void ReadAll()
        {
            while (GetRecordsCount())
            {
                Measurements meas;
                int number = -1;

                if (MemoryStorage::GetOldest(&meas, &number))
                {
//                  Record *record = Record::ForMeasurements(meas);
//
//                  LOG_WRITE("erase record %X number %d for measure %X, all %d, first %d, last %d",
//                  record, record->number, meas, GetRecordsCount(), NumberOldestRecord(), NumberNewestRecord());

                    MemoryStorage::Erase(&meas);
                }
            }
        }
    }
}


void MemoryStorage::Test()
{
    NSTest::Fill();

    NSTest::Corrupt();

    NSTest::ReadAll();
}


#include "MemoryStorage_test.inc"
