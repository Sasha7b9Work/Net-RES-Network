// 2022/05/06 13:37:26 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


#define DEF_BUTTN(name, title, keeper, function)    \
    static const DButton name =                     \
    {                                               \
        TypeItem::Button,                           \
        title,                                      \
        (const Page *)&keeper,                      \
        function                                    \
    };


#define DEF_ITEMS_1(name, item)         \
    static const Item * const name[] =  \
    {                                   \
        (Item *)&item,                  \
        nullptr                         \
    };


#define DEF_PAGE(name, title, keeper, items)    \
static uint8 ci##name = 0;                      \
const DPage name =                              \
{                                               \
    TypeItem::Page,                             \
    title,                                      \
    (const Page *)&keeper,                      \
    items,                                      \
    &ci##name                                   \
};
