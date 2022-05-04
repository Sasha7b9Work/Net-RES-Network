// 2022/05/04 14:41:28 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Hardware/LAN/ClientTCP.h"


void ClientTCP::Connect(uint16 port)
{
    Disconnect();
}


bool ClientTCP::Connected()
{
    return false;
}


void ClientTCP::Disconnect()
{
    if (!Connected())
    {
        return;
    }
}


void ClientTCP::Transmit(const void *buffer, int size)
{
    if (!Connected())
    {
        return;
    }
}
