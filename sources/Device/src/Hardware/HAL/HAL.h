// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


namespace HAL
{
    void Init();
    
    void Delay(unsigned int timeMS);
}


#ifdef __cplusplus
extern "C" {
#endif

void Error_Handler();

#ifdef __cplusplus
}
#endif
