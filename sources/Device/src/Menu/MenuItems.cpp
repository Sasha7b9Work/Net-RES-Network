// 2022/05/05 12:27:16 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/MenuItems.h"
#include "Menu/Pages/Pages.h"
#include "Display/Display.h"
#include "Utils/Text/String.h"
#include "Menu/Menu.h"


const Page *Menu::OpenedPage()
{
    return MainPage::self;
}


bool Item::Opened() const
{
    return true;
}


void Item::Draw(int x, int y) const
{
    if (Opened())
    {
        DrawOpened(x, y);
    }
    else
    {
        DrawClosed(x, y);
    }
}


void Page::DrawOpened(int x, int y) const
{
    DrawTitle(x, y);

    DrawItems(x, y + 28);
}


void Page::DrawTitle(int x, int y) const
{
    Rectangle(Item::WIDTH, 28).DrawFilled(x, y, Color::BLACK, Color::WHITE);

    String<>(Title()).Draw(x + 10, y + 5, Color::WHITE);
}


void Page::DrawItems(int x, int y) const
{
    for (int i = FirstItemOnScreen(); i < LastItemOnScreen(); i++)
    {
        items[i]->DrawClosed(x, y);
        y += Item::HEIGHT;
    }
}


void Page::DrawClosed(int x, int y) const
{
    Rectangle(Item::WIDTH, Item::HEIGHT).DrawFilled(x, y, Color::BLACK, Color::WHITE);

    String<>(Title()).Draw(x + 10, y + 5, Color::WHITE);
}


int Page::FirstItemOnScreen() const
{
    return 0;
}


int Page::LastItemOnScreen() const
{
    return 1;
}
