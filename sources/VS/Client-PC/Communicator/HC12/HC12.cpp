// 2022/04/29 13:56:00 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "Communicator/HC12/HC12.h"
#include "Communicator/HC12/RS232/rs232.h"


namespace HC12
{
    static const int NUM_PORTS = 32;
}


void HC12::Init()
{
    for (int i = 0; i < NUM_PORTS; i++)
    {
        RS232_OpenComport(i, 9600, "8N1", false);
    }
}


void HC12::Update()
{
    for (int i = 0; i < NUM_PORTS; i++)
    {

    }
}
