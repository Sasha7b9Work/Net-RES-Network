// 2023/10/03 11:23:11 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Display/StartScreen.h"
#include "Display/Display.h"
#include "Hardware/Timer.h"


void StartScreen::Run()
{
    Display::BeginScene(Color::WHITE);

    Display::EndScene();

    for (int i = 0; i < Display::HEIGHT; i++)
    {
        HLine(Display::WIDTH).Draw(0, i, Color::BLUE);

        Display::EndScene();
    }
}
