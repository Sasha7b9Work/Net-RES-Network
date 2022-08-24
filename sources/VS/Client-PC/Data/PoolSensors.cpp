// 2022/08/24 14:57:06 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Data/PoolSensors.h"
#include "Utils/DynamicBuffer.h"
#include <cstring>


namespace PoolSensors
{
    static DynamicBuffer <128>buffer;

    static bool FindFirstABC();
}


void PoolSensors::AppendReceivedData(uint8 *data, int size)
{
    buffer.Append(data, size);
}


void PoolSensors::Update()
{
    if (!FindFirstABC())
    {
        return;
    }

    if (buffer.Size() >= 16)
    {
        char bytes[16];

        std::memcpy(bytes, buffer.Data(), 16);

        buffer.RemoveFirst(16);

        float value = 0.0f;

        std::memcpy(&value, bytes + 12, 4);

        value = value;
    }
}


bool PoolSensors::FindFirstABC()
{
    while (buffer.Size() >= 3)
    {
        if (*buffer.Data() == 'A')
        {
            if (*(buffer.Data() + 1) == 'B')
            {
                if (*(buffer.Data() + 2) == 'C')
                {
                    return true;
                }
            }
        }

        buffer.RemoveFirst(1);
    }

    return false;
}
