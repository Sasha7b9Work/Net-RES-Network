// 2022/04/29 13:57:01 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Application.h"
#include "Communicator/Communicator.h"
#include "Display/Display.h"
#include "Communicator/LAN/ServerTCP.h"
#include "Communicator/HC12/HC12.h"
#include "Frame.h"
#include "Data/PoolSensors.h"
#include "Display/Diagram/Diagram.h"


void Application::Init()
{
    Log::Init();

    Communicator::Init();

    LOG_WRITE("size %d %d", Diagram::Pool::GetFirst()->GetSize().x, Diagram::Pool::GetFirst()->GetSize().y);
}


void Application::Update()
{
    Communicator::Update();

    PoolSensors::Update();
}


void Frame::OnClose()
{
    Log::DeInit();
}
