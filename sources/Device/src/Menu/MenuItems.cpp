// 2022/05/05 12:27:16 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/MenuItems.h"
#include "Menu/Pages/Pages.h"
#include "Display/Display.h"
#include "Utils/Text/String.h"
#include "Menu/Menu.h"


namespace Menu
{
    extern Page *opened;
}


Page *Menu::OpenedPage()
{
    return opened;
}


void Page::Open()
{
    Menu::opened = this;

    if (currentItem == NumItems() - 1)
    {
        currentItem = 0;
    }
}


void Page::Close()
{
    if (this == PageMain::self)
    {
        Menu::opened = nullptr;
    }
    else
    {
        Menu::opened = keeper;
    }
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

    DrawItems(x, y + 27);
}


void Page::DrawTitle(int x, int y) const
{
    Rectangle(Item::WIDTH, 27).DrawFilled(x, y, Color::BLACK, Color::WHITE);

    String<>(Title()).Draw(x + 10, y + 10, Color::GRAY_50);
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
    Color::E fill = Color::BLACK;
    Color::E draw = Color::WHITE;

    if (keeper->items[keeper->currentItem] == this)
    {
        fill = Color::GREEN_50;
    }

    Rectangle(Item::WIDTH, Item::HEIGHT).DrawFilled(x, y, fill, draw);

    String<>(Title()).Draw(x + 10, y + 5, draw);
}


void Choice::DrawClosed(int x, int y) const
{
    Color::E fill = Color::BLACK;
    Color::E draw = Color::WHITE;

    if (keeper->items[keeper->currentItem] == this)
    {
        fill = Color::GREEN_50;
    }

    Rectangle(Item::WIDTH, Item::HEIGHT).DrawFilled(x, y, fill, draw);

    String<>(Title()).Draw(x + 10, y + 5, draw);

    String<>(names[*cell]).Draw(x + 130, y + 5, draw);
}


void Button::DrawClosed(int x, int y) const
{
    Color::E fill = Color::BLACK;
    Color::E draw = Color::WHITE;

    if (keeper->items[keeper->currentItem] == this)
    {
        fill = Color::GREEN_50;
    }

    Rectangle(Item::WIDTH, Item::HEIGHT).DrawFilled(x, y, fill, draw);

    String<>(Title()).Draw(x + 10, y + 5, draw);
}


int Page::FirstItemOnScreen() const
{
    return (currentItem / Page::NUM_ITEMS_ON_SCREEN) * Page::NUM_ITEMS_ON_SCREEN;
}


int Page::LastItemOnScreen() const
{
    int result = FirstItemOnScreen() + Page::NUM_ITEMS_ON_SCREEN;

    if (result > NumItems())
    {
        result = NumItems();
    }

    return result;
}


int Page::NumItems() const
{
    for (int i = 0; ; i++)
    {
        if (items[i] == nullptr)
        {
            return i;
        }
    }
}


void Page::SelectNextItem()
{
    currentItem++;

    if (currentItem == NumItems())
    {
        currentItem = 0;
    }
}


void Page::ChangeCurrentItem()
{
    Item *item = items[currentItem];

    if (item->IsPage())
    {
        item->ReinterpetToPage()->Open();
    }
    else if (item->IsChoice())
    {
        item->ReinterpretToChoice()->Change();
    }
    else if (item->IsButton())
    {
        item->ReinterpretToButton()->FuncOnPress();
    }
}


void Choice::Change()
{
    *cell = *cell + 1;

    if (*cell == count)
    {
        *cell = 0;
    }
}
