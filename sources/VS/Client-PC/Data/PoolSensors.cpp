// 2022/08/24 14:57:06 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Data/PoolSensors.h"
#include "Utils/DynamicBuffer.h"


namespace PoolSensors
{
    static DynamicBuffer <128>buffer;
}


void PoolSensors::AppendReceivedData(uint8 *data, int size)
{
    buffer.Append(data, size);
}


void PoolSensors::Update()
{

}
