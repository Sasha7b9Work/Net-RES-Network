// 2022/08/24 14:56:50 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


namespace PoolSensors
{
    // Добавить принятые данные
    void AppendReceivedData(uchar *data, int size);

    void Update();
}
