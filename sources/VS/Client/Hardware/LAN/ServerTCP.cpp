// 2022/05/04 14:41:28 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Hardware/LAN/ServerTCP.h"
#include "Hardware/LAN/libnet/netserver.h"
#include "Hardware/LAN/libnet/netpacket.h"


namespace ServerTCP
{
    net__::netserver server(2);

    sock_t socket = -1;

    size_t OnReceiveData(net__::netpacket *, void *);

    size_t OnConnection(sock_t, void *);
}


void ServerTCP::Open(uint16 port)
{
    Close();

    socket = server.openPort(port);

    server.setConnectCB(OnConnection, nullptr);
}


bool ServerTCP::Opened()
{
    return !server.isClosed(socket);
}


void ServerTCP::Close()
{
    if (!Opened())
    {
        return;
    }

    server.closePort();
}


size_t ServerTCP::OnReceiveData(net__::netpacket *packet, void *)
{
    char buffer[1024];

    sprintf(buffer, "received %d bytes", (int)packet->get_maxsize());

    DWORD num_chars = 0;

    WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), buffer, std::strlen(buffer), &num_chars, NULL);

    return packet->get_maxsize();
}


size_t ServerTCP::OnConnection(sock_t sock, void *)
{
    server.setConPktCB(sock, OnReceiveData, nullptr);

    return 0;
}


void ServerTCP::Update()
{
    server.run();
}
