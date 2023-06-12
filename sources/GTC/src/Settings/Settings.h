// 2022/05/05 15:22:56 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Display/Display.h"


struct TypeDisplayedInformation
{
    enum E
    {
        MeasureTemperature,
        MeasureHumidity,
        MeasurePressure,
        MeasureDewPoint,
        AllMeasures,
        Menu,
        Count
    };

    E value;

    TypeDisplayedInformation &operator++()
    {
        value = (E)(value + 1);

        return *this;
    }

    bool IsAllMeasures() const { return value == AllMeasures; }
};



struct SettingsDisplay
{
    uint8                       show_measure[TypeMeasure::Count];
    TypeDisplayedInformation    typeDisplaydInfo;
};


struct SettingsMeasures
{
    int min[TypeMeasure::Count];
    int max[TypeMeasure::Count];
};


struct SettingsSystem
{
    int serial_number;
};


struct Settings
{
    uint crc;
    uint number;
    SettingsDisplay  display;
    SettingsSystem   system;
    SettingsMeasures measures;

    bool operator!=(const Settings &);
    bool operator==(const Settings &);

    static void Load();

    static void Save();
};


extern Settings gset;
