// 2022/08/24 15:11:17 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Utils/DynamicBuffer.h"


template void DynamicBuffer<128>::Append(uint8 *, int);


template<int size_chunk>
void DynamicBuffer<size_chunk>::Append(uint8 *data, int size)
{

}
