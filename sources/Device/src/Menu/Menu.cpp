// 2022/05/05 12:28:20 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Menu.h"
#include "Display/Display.h"
#include "Menu/MenuItems.h"
#include "Menu/Pages/Pages.h"
#include "Settings/Settings.h"
#include "Display/Font/Font.h"


namespace Menu
{
    const Page *opened = &Page::Empty;
}


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
        Menu::OpenedPage()->SelectNextItem();
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
        Menu::OpenedPage()->ChangeCurrentItem();
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
