// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


/*
*  Формат передачи измерений
*  
*/


namespace HC12
{
    void Init();

    void Transmit(const void *buffer, int size);
}
