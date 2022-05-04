// 2022/04/29 10:12:30 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#define WIN32_LEAN_AND_MEAN
#include "defines.h"
#include "Application.h"
#include "Frame.h"
#include "Device.h"
#include "Hardware/LAN/ClientTCP.h"


void Application::Init()
{
    Device::Init();

    ClientTCP::Connect(777);
}


void Application::Update()
{
    Device::Update();
}
