// 2022/08/24 14:56:50 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


struct TypeMeasure
{
    enum E
    {
        Pressure,           // Давление
        Illumination,       // Освещённость
        Temperature,        // Температура
        Humidity,           // Влажность
        Velocity,           // Скорость
        Count
    };

    static pchar GetTitle(TypeMeasure::E);
    static pchar GetUnits(TypeMeasure::E);
};


// Хранилище нативных принятых байтов
namespace PoolSensors
{
    // Добавить принятые данные
    void AppendReceivedData(uint8 *data, int size);

    void Update();
}
