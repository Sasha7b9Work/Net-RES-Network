// 2022/05/05 12:27:16 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/MenuItems.h"
#include "Menu/Pages/Pages.h"


const Page *Page::Opened()
{
    return MainPage::self;
}


void Page::Draw() const
{

}
