// 2022/05/05 12:27:33 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Display/Display.h"
#include "Hardware/Keyboard.h"
#include "Hardware/HAL/HAL.h"
#include "Hardware/Timer.h"


struct TypeItem
{
    enum E
    {
        Page,           // Страница содержит другие элементы управления
        Choice,         // Выбор из нескольких значений
        Button,         // Кнопка - по нажатию что-то происходит
        Governor,       // Можно изменять значение в некоторых пределах
        Time,
        Count
    };
};


struct Page;
struct Choice;
struct Button;
struct Governor;
struct TimeItem;


typedef void(*FuncOpenClose)(bool);
inline void EmptyFuncOpenClose(bool) { }


#define COMMON_PART_ITEM    TypeItem::E    type;            \
                            pchar          title;           \
                            const Page    *keeper;          \
                            FuncOpenClose  funcOnOpenClose     // Выполняется перед открытием (true) или закрытием (false) итема

struct DItem
{
    COMMON_PART_ITEM;
};


struct Item
{
    static const int WIDTH = Display::WIDTH - 1;
    static const int HEIGHT = 20;

    String<> Title() const;

    void Draw(int x, int y, bool active) const;

    void DrawOpened(int x, int y, bool active) const;
    void DrawClosed(int x, int y, bool active) const;

    void ShortPressure(Key::E) const;
    void LongPressure(Key::E) const;
    void DoubleClick() const;

    const Page *Keeper() const { return ToDItem()->keeper; }

    void Open() const;
    void Close() const;

    bool IsOpened() const;

    static const Item *Opened() { return opened_item; };

    bool IsPage() const     { return (ToDItem()->type == TypeItem::Page);   }
    bool IsChoice() const   { return (ToDItem()->type == TypeItem::Choice); }
    bool IsButton() const   { return (ToDItem()->type == TypeItem::Button); }
    bool IsGovernor() const { return (ToDItem()->type == TypeItem::Governor); }
    bool IsTimeItem() const { return (ToDItem()->type == TypeItem::Time); }

    const DItem *ToDItem() const { return (DItem *)this; }

    const Page *ToPage() const { return (const Page *)this; }
    const Choice *ToChoice() const { return (const Choice *)this; }
    const Button *ToButton() const { return (const Button *)this; }
    const Governor *ToGovernor() const { return (const Governor *)this; }
    const TimeItem *ToTimeItem() const { return (const TimeItem *)this; }

    static Item Empty;

protected:

    virtual ~Item() { }

    static const Item *opened_item;
};


//-------------------------------------------------------------------------------------------------


struct DPage
{
    COMMON_PART_ITEM;

    const Item *const *items;
    uint8 *currentItem;
};


struct Page : public Item
{
    static const int NUM_ITEMS_ON_SCREEN = 5;

    void DrawOpened(int x, int y, bool acitve) const;
    void DrawClosed(int x, int y, bool active) const;

    void ShortPressure(Key::E) const;
    void LongPressure(Key::E) const;
    void DoubleClick() const;

    void Close() const;

    const DPage *ToDPage() const { return (DPage *)this; }

    const Item *CurrentItem() const;

private:

    void DrawTitle(int x, int y) const;

    void DrawItems(int x, int y, bool active) const;

    // Первый выводимый итем на текущей странице
    int FirstItemOnScreen() const;

    // Последний выводимый итем на текущей странице
    int LastItemOnScreen() const;

    int NumItems() const;

    virtual ~Page() { }
};


//-------------------------------------------------------------------------------------------------


struct DChoice
{
    COMMON_PART_ITEM;

    uint8 *const cell;
    const uint8 count;
    pchar names[2];
};


struct Choice : public Item
{
    void DrawClosed(int x, int y, bool active) const;
    void DrawOpened(int x, int y, bool active) const;

    void ShortPressure(Key::E) const;
    void LongPressure() const;
    void DoubleClick() const;

    pchar CurrentName() const;

    const DChoice *ToDChoice() const { return (DChoice *)this; }
};


//-------------------------------------------------------------------------------------------------


struct DButton
{
    COMMON_PART_ITEM;

    bool *marked;            // Если это значение равно true, то кнопка с галочкой. Типа "выбрано"
};


struct Button : public Item
{
    void ShortPressure(Key::E) const;
    void LongPressure() const { ToDItem()->funcOnOpenClose(true); }
    void DoubleClick() const;

    void DrawClosed(int x, int y, bool active) const;
    void DrawOpened(int x, int y, bool active) const;

    const DButton *ToDButton() const { return (DButton *)this; }
};


//-------------------------------------------------------------------------------------------------


struct DGovernor
{
    COMMON_PART_ITEM;

    int min;
    int max;
    int *value;
};


struct Governor : public Item
{
    void DrawClosed(int x, int y, bool active) const;
    void DrawOpened(int x, int y, bool active) const;

    void ShortPressure(Key::E) const;
    void LongPressure() const;
    void DoubleClick() const;

    const DGovernor *ToDGovernor() const { return (DGovernor *)this; }

private:
    void DrawControls(int x, int y) const;

    void DrawControl(int x, int y, const String<> &, bool active) const;

    struct ActiveControl
    {
        enum E
        {
            Increase,       // При коротком нажатии увеличение значения
            Decrease,       // При коротком нажатии уменьшение значения
            Close,          // При коротком нажатии закрывается
            Count
        };
    };

    static ActiveControl::E active_control;
};


//-------------------------------------------------------------------------------------------------


struct DTimeItem
{
    COMMON_PART_ITEM;

    int *cur_field;     // Область, в которой находится курсор
                        // [0...5] <-> [часы ... год], 6 - применить, 7 - выход
    int *state;         // 0 - выбор поля для изменения
                        // 1 - изменение
    PackedTime *time;
};


struct TimeItem : public Item
{
    void DrawClosed(int x, int y, bool active) const;
    void DrawOpened(int x, int y, bool active) const;

    void ShortPressure(Key::E) const;
    void LongPressure(Key::E) const;
    void DoubleClick() const;

    const DTimeItem *ToDTimeItem() const { return (DTimeItem *)this; }
private:

    void ChangeCurrentField(Key::E) const;
};
