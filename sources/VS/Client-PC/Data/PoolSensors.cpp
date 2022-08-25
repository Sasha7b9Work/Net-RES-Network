// 2022/08/24 14:57:06 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Data/PoolSensors.h"
#include "Utils/DynamicBuffer.h"
#include "Log.h"
#include "Utils/Math.h"
#include <cstring>


namespace PoolSensors
{
    static DynamicBuffer <128>buffer;

    static bool FindFirstABC();

    static bool ParseCommand(char bytes[16]);
}


void PoolSensors::AppendReceivedData(uint8 *data, int size)
{
    buffer.Append(data, size);
}


void PoolSensors::Update()
{
    if (FindFirstABC() && buffer.Size() >= 16)
    {
        char bytes[16];

        std::memcpy(bytes, buffer.Data(), 16);

        buffer.RemoveFirst(16);

        if (!ParseCommand(bytes))
        {
            LOG_ERROR("Can not parse command");
        }
    }
}


bool PoolSensors::FindFirstABC()
{
    int removed_bytes = 0;

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

        removed_bytes++;
    }

    if (removed_bytes != 0)
    {
        LOG_ERROR("error command");
    }

    return false;
}


bool PoolSensors::ParseCommand(char message[16])
{
    uint8 type = message[3];

    uint id = 0;

    std::memcpy(&id, &message[4], 4);

    uint hash = 0;

    std::memcpy(&hash, &message[8], 4);

    float value = 0.0f;

    std::memcpy(&value, &message[12], 4);

    if (Math::CalculateHash(&value, 4) == hash)
    {
        LOG_WRITE("id = %d, type = %d, value = %f", id, type, value);

        return true;
    }

    return false;
}
