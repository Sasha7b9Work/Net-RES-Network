// 2022/05/05 12:27:33 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


struct TypeItem
{
    enum E
    {
        Page,
        Choice,
        Count
    };
};


struct Page;


struct Item
{
    TypeItem::E type;
    Page *keeper;
};


struct Page : public Item
{
    Item *items;
};


struct Choice : public Item
{
    uint8 *cell;
};
