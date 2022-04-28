#define WIN32_LEAN_AND_MEAN
#include "Application.h"
#include "Frame.h"
#include "Device.h"


void Application::Init()
{
    Device::Init();
}


void Application::Update()
{
    Device::Update();
}
