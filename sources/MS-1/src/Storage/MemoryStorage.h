// 2023/09/08 22:13:56 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Storage/Storage.h"


namespace MemoryStorage
{
    void Init();

    void *Append(const Measurements &);

    // Возвращает указатель на самую старую структуру данных (которая считана раньше всех). После использования нужно вызвать Erase()
    // с этим указателем, чтобы стереть структуру из хранилища
    bool GetOldest(Measurements *meas, int *number);

    // Возвращает измерение, следующее за number_prev. Если таковое существует,
    // в number возвращается номер возвращённого измерения
    bool GetNext(Measurements *meas, int number_prev, int *number);

    void Erase(const Measurements *);

    void Test();
};
