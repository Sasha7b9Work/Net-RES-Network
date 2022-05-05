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
    Page       *keeper;

    Item(TypeItem::E _type, pchar _title, Page *_keeper) : type(_type), title(_title), keeper(_keeper) { }

    virtual ~Item() {}

    pchar Title() const { return title; }

    virtual void Draw(int x, int y) const;

    virtual void DrawOpened(int x, int y) const {}

    virtual void DrawClosed(int x, int y) const {}

    bool Opened() const;

    bool IsPage() const { return type == TypeItem::Page; }
    bool IsChoice() const { return type == TypeItem::Choice; }
    bool IsButton() const { return type == TypeItem::Button; }

    Page *ReinterpetToPage() { return (Page *)this; }
    Choice *ReinterpretToChoice() { return (Choice *)this; }
    Button *ReinterpretToButton() { return (Button *)this; }
};


struct Page : public Item
{
    static const int NUM_ITEMS_ON_SCREEN = 5;

    Item **items;

    uint8 currentItem;

    Page(pchar title, Page *keeper, Item **_items) : Item(TypeItem::Page, title, keeper), items(_items) {}

    virtual void DrawOpened(int x, int y) const;

    // Выделить следующий итем
    void SelectNextItem();

    // Изменить состояние текущего итема
    void ChangeCurrentItem();

    void Open();

    void Close();

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
    typedef void (*funcChanged)();

    uint8 *cell;
    uint8 count;
    pchar names[2];
    funcChanged funcOnChanged;

    Choice(pchar title, Page *keeper, uint8 *_cell, uint8 _count, funcChanged func, pchar name0, pchar name1) :
        Item(TypeItem::Choice, title, keeper), cell(_cell), count(_count), funcOnChanged(func)
    {
        names[0] = name0;
        names[1] = name1;
    }

    virtual void DrawClosed(int x, int y) const;

    void Change();
};


struct Button : public Item
{
    typedef void (*funcPressButton)();

    funcPressButton funcPress;

    Button(pchar title, Page *keeper, funcPressButton _funcPress) : Item(TypeItem::Button, title, keeper), funcPress(_funcPress) {}

    void FuncOnPress() { funcPress(); }

    virtual void DrawClosed(int x, int y) const;
};
