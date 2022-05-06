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


#define COMMON_PART_ITEM     TypeItem::E type;      \
                             pchar       title;     \
                             const Page *keeper;    \


struct DItem
{
    COMMON_PART_ITEM
};


struct Item
{
    static const int WIDTH = Display::WIDTH - 1;
    static const int HEIGHT = 20;

    pchar Title() const { return ReinterpretToDItem()->title; }

    void Draw(int x, int y) const;

    void DrawOpened(int x, int y) const;
    void DrawClosed(int x, int y) const;

    bool Opened() const;

    bool IsPage() const   { return (ReinterpretToDItem()->type == TypeItem::Page);   }
    bool IsChoice() const { return (ReinterpretToDItem()->type == TypeItem::Choice); }
    bool IsButton() const { return (ReinterpretToDItem()->type == TypeItem::Button); }

    const DItem *ReinterpretToDItem() const { return (DItem *)this; }

    const Page *ReinterpetToPage() const { return (const Page *)this; }
    const Choice *ReinterpretToChoice() const { return (const Choice *)this; }
    const Button *ReinterpretToButton() const { return (const Button *)this; }
};


struct DPage
{
    COMMON_PART_ITEM

    const Item *const *items;
    uint8 *currentItem;
};


struct Page : public Item
{
    static const int NUM_ITEMS_ON_SCREEN = 5;

    void DrawOpened(int x, int y) const;

    void DrawClosed(int x, int y) const;

    // Выделить следующий итем
    void SelectNextItem() const;

    // Изменить состояние текущего итема
    void ChangeCurrentItem() const;

    void Open() const;

    void Close() const;

    const DPage *ReinterpretToDPage() const { return (DPage *)this; }

    const Item *CurrentItem() const;

private:

    void DrawTitle(int x, int y) const;

    void DrawItems(int x, int y) const;

    // Первый выводимый итем на текущей странице
    int FirstItemOnScreen() const;

    // Последний выводимый итем на текущей странице
    int LastItemOnScreen() const;

    int NumItems() const;
};


struct DChoice
{
    COMMON_PART_ITEM

    uint8 *const cell;
    const uint8 count;
    pchar names[2];
};


struct Choice : public Item
{
    void DrawClosed(int x, int y) const;

    void Change() const;

    pchar CurrentName() const;

    const DChoice *ReinterpretToDChoice() const { return (DChoice *)this; }
};


struct DButton
{
    typedef void (*funcPressButton)();

    COMMON_PART_ITEM

    const funcPressButton funcPress;
};


struct Button : public Item
{
    void FuncOnPress() const { ReinterpretToDButton()->funcPress(); }

    void DrawClosed(int x, int y) const;

    const DButton *ReinterpretToDButton() const { return (DButton *)this; }
};
