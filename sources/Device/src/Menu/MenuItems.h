// 2022/05/05 12:27:33 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Display/Display.h"


struct TypeItem
{
    enum E
    {
        Page,
        Choice,
        Button,
        Count
    };
};


struct Page;
struct Choice;
struct Button;


struct Item
{
    static const int WIDTH = Display::WIDTH - 1;
    static const int HEIGHT = 20;

    TypeItem::E type;
    pchar       title;
    const Page *keeper;

    Item(TypeItem::E _type, pchar _title, const Page *_keeper) : type(_type), title(_title), keeper(_keeper) { }

    virtual ~Item() {}

    pchar Title() const { return title; }

    virtual void Draw(int x, int y) const;

    virtual void DrawOpened(int, int) const {}

    virtual void DrawClosed(int, int) const {}

    bool Opened() const;

    bool IsPage() const { return type == TypeItem::Page; }
    bool IsChoice() const { return type == TypeItem::Choice; }
    bool IsButton() const { return type == TypeItem::Button; }

    const Page *ReinterpetToPage() const { return (const Page *)this; }
    const Choice *ReinterpretToChoice() const { return (const Choice *)this; }
    const Button *ReinterpretToButton() const { return (const Button *)this; }
};


struct Page : public Item
{
    static const int NUM_ITEMS_ON_SCREEN = 5;

    const Item * const *items;

    uint8 *currentItem;

    Page(pchar title, const Page *keeper, const Item * const *_items, uint8 *_currentItem) : Item(TypeItem::Page, title, keeper), items(_items), currentItem(_currentItem) {}

    virtual void DrawOpened(int x, int y) const;

    // Выделить следующий итем
    void SelectNextItem() const;

    // Изменить состояние текущего итема
    void ChangeCurrentItem() const;

    void Open() const;

    void Close() const;

private:

    void DrawTitle(int x, int y) const;

    void DrawItems(int x, int y) const;

    virtual void DrawClosed(int x, int y) const;

    // Первый выводимый итем на текущей странице
    int FirstItemOnScreen() const;

    // Последний выводимый итем на текущей странице
    int LastItemOnScreen() const;

    int NumItems() const;
};


struct Choice : public Item
{
    uint8 * const cell;
    const uint8 count;
    pchar names[2];

    Choice(pchar title, const Page *keeper, uint8 *_cell, uint8 _count, pchar name0, pchar name1) :
        Item(TypeItem::Choice, title, keeper), cell(_cell), count(_count)
    {
        names[0] = name0;
        names[1] = name1;
    }

    virtual void DrawClosed(int x, int y) const;

    void Change() const;
};


struct Button : public Item
{
    typedef void (*funcPressButton)();

    const funcPressButton funcPress;

    Button(pchar title, const Page *keeper, funcPressButton _funcPress) : Item(TypeItem::Button, title, keeper), funcPress(_funcPress) {}

    void FuncOnPress() const { funcPress(); }

    virtual void DrawClosed(int x, int y) const;
};
