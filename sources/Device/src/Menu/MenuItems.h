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
    pchar       title;
    const Page *keeper;

    Item(TypeItem::E _type, pchar _title, const Page *_keeper) : type(_type), title(_title), keeper(_keeper) { }

    pchar Title() const { return title; }
};


struct Page : public Item
{
    const Item **items;

    uint8 currentItem;

    Page(pchar title, const Page *keeper, const Item **_items) : Item(TypeItem::Page, title, keeper), items(_items) {}

    void Draw() const;

    static const Page *Opened();

private:

    void DrawTitle() const;

    void DrawItems() const;
};


struct Choice : public Item
{
    uint8 *cell;
    uint8 count;

    Choice(pchar title, const Page *keeper, uint8 *_cell, uint8 _count) : Item(TypeItem::Choice, title, keeper), cell(_cell), count(_count) { }
};
