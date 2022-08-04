// 2022/05/05 12:28:20 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Menu.h"
#include "Display/Display.h"
#include "Menu/MenuItems.h"
#include "Menu/Pages/Pages.h"
#include "Settings/Settings.h"
#include "Display/Font/Font.h"


void Menu::ShortPress()
{
    if (!Opened())
    {
        ++gset.display.typeDisplaydInfo;

        if (gset.display.typeDisplaydInfo.value == TypeDisplayedInformation::Menu)
        {
            gset.display.typeDisplaydInfo.value = TypeDisplayedInformation::MeasurePressure;
        }

    }
    else
    {
        Menu::OpenedPage()->ShortPressure();
    }

    Display::need_redraw = true;
}


void Menu::LongPress()
{
    if (!Opened())
    {
        opened = PageMain::self;
    }
    else
    {
        Menu::OpenedPage()->LongPressure();
    }

    Display::need_redraw = true;
}


bool Menu::Opened()
{
    return (opened != &Page::Empty);
}


void Menu::Draw()
{
    Display::BeginScene(Color::BLACK);

    Font::Set(TypeFont::_8);

    Menu::OpenedPage()->Draw(0, 0);

    Display::EndScene();
}
