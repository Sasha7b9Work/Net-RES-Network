// 2022/05/05 12:27:16 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/MenuItems.h"
#include "Menu/Pages/Pages.h"
#include "Display/Display.h"
#include "Utils/Text/String.h"


const Page *Page::Opened()
{
    return MainPage::self;
}


void Page::Draw() const
{
    DrawTitle();

    DrawItems();
}


void Page::DrawTitle() const
{
    Rectangle(Display::WIDTH - 1, 19).DrawFilled(0, 0, Color::BLACK, Color::WHITE);

    String<>(Title()).Draw(10, 5, Color::WHITE);
}


void Page::DrawItems() const
{
    for (int i = FirstItemOnScreen(); i < LastItemOnScreen(); i++)
    {
        const Item *item = items[i];

        item->Draw();
    }
}


int Page::FirstItemOnScreen() const
{
    return 0;
}


int Page::LastItemOnScreen() const
{
    return 1;
}


void Choice::Draw() const
{

}
