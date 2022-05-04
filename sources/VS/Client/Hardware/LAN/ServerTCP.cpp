// 2022/05/04 14:41:28 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Hardware/LAN/ServerTCP.h"
#include "Hardware/LAN/libnet/netserver.h"


namespace ServerTCP
{
    net__::netserver server(2);

    sock_t socket = -1;
}


void ServerTCP::Connect(uint16 port)
{
    Disconnect();

    socket = server.doConnect("localhost", port);
}


bool ServerTCP::Connected()
{
    return !client.isClosed(socket);
}


void ServerTCP::Disconnect()
{
    if (!Connected())
    {
        return;
    }

    server.disconnect(socket);
}


void ServerTCP::Transmit(const void *buffer, int size)
{
    if (!Connected())
    {
        return;
    }

    net__::netpacket packet((size_t)size, (uint8 *)buffer);

    server.sendPacket(socket, packet);
}
