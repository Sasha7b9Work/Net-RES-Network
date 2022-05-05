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

    virtual ~Item() {}

    pchar Title() const { return title; }

    virtual void Draw(int x, int y) const;

    virtual void DrawOpened(int x, int y) const {}

    virtual void DrawClosed(int x, int y) const {}

    bool Opened() const;
};


struct Page : public Item
{
    const Item **items;

    uint8 currentItem;

    Page(pchar title, const Page *keeper, const Item **_items) : Item(TypeItem::Page, title, keeper), items(_items) {}

    virtual void DrawOpened(int x, int y) const;

private:

    void DrawTitle(int x, int y) const;

    void DrawItems(int x, int y) const;

    virtual void DrawClosed(int x, int y) const;

    // ѕервый выводимый итем на текущей странице
    int FirstItemOnScreen() const;

    // ѕоследний выводимый итем на текущей странице
    int LastItemOnScreen() const;
};


struct Choice : public Item
{
    uint8 *cell;
    uint8 count;

    Choice(pchar title, const Page *keeper, uint8 *_cell, uint8 _count) : Item(TypeItem::Choice, title, keeper), cell(_cell), count(_count) { }
};
