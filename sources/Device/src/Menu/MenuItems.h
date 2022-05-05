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
    const Page *keeper;

    Item(TypeItem::E _type, const Page *_keeper) : type(_type), keeper(_keeper) { }
};


struct Page : public Item
{
    const Item **items;

    Page(const Page *keeper, const Item **_items) : Item(TypeItem::Page, keeper), items(_items) {}

    void Draw() const;

    static const Page *Opened();
};


struct Choice : public Item
{
    uint8 *cell;
    int count;

    Choice(const Page *keeper, uint8 *_cell, int _count) : Item(TypeItem::Choice, keeper), cell(_cell), count(_count) { }
};
