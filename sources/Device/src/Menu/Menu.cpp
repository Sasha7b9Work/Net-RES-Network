// 2022/05/05 12:28:20 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Menu.h"
#include "Display/Display.h"
#include "Menu/MenuItems.h"
#include "Menu/Pages/Pages.h"


namespace Menu
{
    const Page *opened = nullptr;
}


void Menu::ShortPress()
{
    if (!Opened())
    {
        opened = PageMain::self;
    }
    else
    {
        Menu::OpenedPage()->SelectNextItem();
    }
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
}


bool Menu::Opened()
{
    return (opened != nullptr);
}


void Menu::Draw()
{
    Display::BeginScene(Color::BLACK);

    const Page *page = Menu::OpenedPage();

    DPage *dpage = (DPage *)page;
    dpage = dpage;

    page->Draw(0, 0);

    Display::EndScene();
}
