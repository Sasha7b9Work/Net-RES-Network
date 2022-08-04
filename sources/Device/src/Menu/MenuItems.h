// 2022/05/05 12:27:33 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Display/Display.h"


struct TypeItem
{
    enum E
    {
        Page,           // Страница содержит другие элементы управления
        Choice,         // Выбор из нескольких значений
        Button,         // Кнопка - по нажатию что-то происходит
        Governor,       // Можно изменять значение в некоторых пределах
        Count
    };
};


struct Page;
struct Choice;
struct Button;
struct Governor;


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

    String<> Title() const;

    void Draw(int x, int y) const;

    void DrawOpened(int x, int y) const;
    void DrawClosed(int x, int y) const;

    bool Opened() const;

    bool IsPage() const     { return (ReinterpretToDItem()->type == TypeItem::Page);   }
    bool IsChoice() const   { return (ReinterpretToDItem()->type == TypeItem::Choice); }
    bool IsButton() const   { return (ReinterpretToDItem()->type == TypeItem::Button); }
    bool IsGovernor() const { return (ReinterpretToDItem()->type == TypeItem::Governor); }

    const DItem *ReinterpretToDItem() const { return (DItem *)this; }

    const Page *ReinterpetToPage() const { return (const Page *)this; }
    const Choice *ReinterpretToChoice() const { return (const Choice *)this; }
    const Button *ReinterpretToButton() const { return (const Button *)this; }
    const Governor *ReinterpretToGovernor() const { return (const Governor *)this; }
};


//-------------------------------------------------------------------------------------------------


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

    // Короткое нажатие кнопки
    void ShortPressure() const;

    // Длинное нажатие кнопки
    void LongPressure() const;

    void Open() const;

    void Close() const;

    const DPage *ReinterpretToDPage() const { return (DPage *)this; }

    const Item *CurrentItem() const;

    static Page Empty;

private:

    void DrawTitle(int x, int y) const;

    void DrawItems(int x, int y) const;

    // Первый выводимый итем на текущей странице
    int FirstItemOnScreen() const;

    // Последний выводимый итем на текущей странице
    int LastItemOnScreen() const;

    int NumItems() const;
};


//-------------------------------------------------------------------------------------------------


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


//-------------------------------------------------------------------------------------------------


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


//-------------------------------------------------------------------------------------------------


struct DGovernor
{
    COMMON_PART_ITEM

    int min;
    int max;
    int *value;
};


struct Governor : public Item
{
    void DrawClosed(int x, int y) const;

    void Open() const;

    const DGovernor *RetinterpretToDGovernor() const { return (DGovernor *)this; }
};
