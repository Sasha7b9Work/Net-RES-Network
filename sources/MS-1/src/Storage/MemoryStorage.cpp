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

    static const int NUM_PAGES = (END - BEGIN) / W25Q80DV::SIZE_PAGE;

    struct ValueInt
    {
        int value = 0;
        bool is_valid = false;
    };

    struct Page
    {
    public:
        static const int SIZE = W25Q80DV::SIZE_PAGE;

    private:

        uint startAddress;

        ValueInt records_good;      // Столько хороших записей на странице
        ValueInt records_bad;       // Столько плохих записей на странице

    public:

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
            return W25Q80DV::SIZE_PAGE / sizeof(Measurements);
        }

        Record LastRecord()
        {
            return Record(startAddress + (uint)GetMaxRecordsCount() * sizeof(Measurements));
        }

        int GetCountRecordsGood()
        {
            if (!records_good.is_valid)
            {
                records_good.value = 0;

                for (Record record = FirstRecord(); record < LastRecord(); record++)
                {
                    if (record.IsCorrectData())
                    {
                        records_good.value++;
                    }
                }

                records_good.is_valid = true;
            }

            return records_good.value;
        }

        int GetCountRecordsBad()
        {
            if (records_bad.is_valid)
            {
                records_bad.value = 0;

                for (Record record = FirstRecord(); record < LastRecord(); record++)
                {
                    if (!record.IsEmpty())
                    {
                        if (!record.IsErased())
                        {
                            if (!record.IsCorrectData())
                            {
                                records_bad.value++;
                            }
                        }
                    }
                }

                records_bad.is_valid = true;
            }

            return records_bad.value;
        }

        void Prepare()
        {
            for (Record record = FirstRecord(); record < LastRecord(); record++)
            {
                if (record.IsEmpty() || record.IsErased())
                {
                    continue;
                }

                if (!record.IsCorrectData())
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
                if (record.IsCorrectData() && record.GetNumber() > result)
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
                if (record.IsCorrectData())
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
                if (record.IsCorrectData())
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
                if (record.IsCorrectData())
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
    };

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

        measurements.number = GetNewNumber();

        record.Write(measurements);

        return record;
    }

    // Проверить все сектора на предмет повреждённых записей и стереть их
    static void Prepare();

    static int GetCountRecordsGood();
    static int GetCountRecordsBad();
    static int GetCountRecordsAll();

    static void EraseAllRecords();
}


Record::Record(uint _address) : address(_address)
{
//    page = &MemoryStorage::pages[address / MemoryStorage::Page::SIZE];
}


Measurements &Record::GetMeasurements()
{
    if (address != address_meas)
    {
        address_meas = address;

        W25Q80DV::ReadLess1024bytes(address, &measurements, sizeof(Measurements));
    }

    return measurements;
}


void Record::Write(const Measurements &meas)
{
    measurements = meas;
    measurements.crc = measurements.CalculateCRC();
    address_meas = address;

    W25Q80DV::WriteLess1024bytes(address, &measurements, (int)sizeof(Measurements));
}


void Record::Erase()
{
    W25Q80DV::WriteUInt((uint)Begin(), 0);
}


void MemoryStorage::Init()
{
    for (int i = 0; i < NUM_PAGES; i++)
    {
        pages[i].Init(i);
    }

    Prepare();
}


void MemoryStorage::Erase(Record *record)
{
    record->Erase();
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


bool MemoryStorage::GetOldest(Record *record)
{
    return Record::Oldest(record);
}


void MemoryStorage::Prepare()
{
    for (int i = 0; i < NUM_PAGES; i++)
    {
        pages[i].Prepare();
    }
}


int MemoryStorage::GetCountRecordsAll()
{
    int bad = GetCountRecordsBad();

    int good = GetCountRecordsGood();

    return bad + good;
}


int MemoryStorage::GetCountRecordsGood()
{
    int result = 0;

    for (int i = 0; i < NUM_PAGES; i++)
    {
        result += pages[i].GetCountRecordsGood();
    }

    return result;
}


int MemoryStorage::GetCountRecordsBad()
{
    int result = 0;

    for (int i = 0; i < NUM_PAGES; i++)
    {
        result += pages[i].GetCountRecordsBad();
    }

    return result;
}


bool Record::Oldest(Record *record)
{
    bool exist_result = false;

    for (int i = 0; i < MemoryStorage::NUM_PAGES; i++)
    {
        Record oldest(0);

        if (MemoryStorage::pages[i].GetOldestRecord(&oldest))
        {
            if (!exist_result || oldest.GetMeasurements().number < record->GetMeasurements().number)
            {
                exist_result = true;

                *record = oldest;
            }
        }
    }

    return exist_result;
}


bool Record::Newest(Record *record)
{
    bool exist_result = false;

    for (int i = 0; i < MemoryStorage::NUM_PAGES; i++)
    {
        Record newest(0);

        if (MemoryStorage::pages[i].GetNewestRecord(&newest))
        {
            if (!exist_result || newest.GetMeasurements().number > record->GetMeasurements().number)
            {
                exist_result = true;

                *record = newest;
            }
        }
    }

    return exist_result;
}


void MemoryStorage::EraseAllRecords()
{
    for (int i = 0; i < NUM_PAGES; i++)
    {
        pages[i].Erase();
    }
}


bool MemoryStorage::Test()
{
    EraseAllRecords();

    if (GetCountRecordsBad() != 0)
    {
        return false;
    }

    if (GetCountRecordsGood() != 0)
    {
        return false;
    }

    static int prev_records_count = -1;

    while (prev_records_count != GetCountRecordsAll())
    {
        Measurements meas;

        prev_records_count = GetCountRecordsAll();

        Append(meas);
    }

    while (true)
    {
        prev_records_count = prev_records_count;
    }

    return GetCountRecordsAll() == 0;
}
