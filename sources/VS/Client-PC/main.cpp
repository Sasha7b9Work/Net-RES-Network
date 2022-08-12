// 2022/04/29 13:57:01 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Application.h"
#include "Communicator/Communicator.h"
#include "Display/Display.h"
#include "Communicator/LAN/ServerTCP.h"
#include "Communicator/HC12/HC12.h"
#include "Frame.h"


void Application::Init()
{
//    AllocConsole();

    Communicator::Init();
}


void Application::Update()
{
    Communicator::Update();
    Display::Update();
}


void Frame::OnClose()
{
//    FreeConsole();
}
