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
}


void ServerTCP::Open(uint16 port)
{
    Close();

    socket = server.openPort(port);

    server.setConPktCB(socket, OnReceiveData, nullptr);
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

    std::cout << buffer << std::endl;

    return packet->get_maxsize();
}


void ServerTCP::Update()
{
    server.run();
}
