// 2022/04/29 13:57:01 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Application.h"
#include "Communicator/Communicator.h"
#include "Display/Display.h"
#include "Hardware/LAN/ServerTCP.h"


void Application::Init()
{
    ServerTCP::Open(777);
}


void Application::Update()
{
    Communicator::Update();
    Display::Update();
    ServerTCP::Update();
}
