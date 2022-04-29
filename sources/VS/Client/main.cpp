// 2022/04/29 13:57:01 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "Application.h"
#include "Communicator/Communicator.h"
#include "Display/Display.h"


void Application::Init()
{

}


void Application::Update()
{
    Communicator::Update();
    Display::Update();
}
