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



struct Item
{
    TypeItem::E type;
};


struct Page : public Item
{

};


struct Choice : public Item
{

};
