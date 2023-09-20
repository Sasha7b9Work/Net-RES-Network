// 2023/06/15 14:13:06 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include <stm32f3xx_hal.h>


struct Pin
{
    Pin(GPIO_TypeDef *_gpio, uint16 _pin, uint _mode, uint _pull) : gpio(_gpio), pin(_pin), mode(_mode), pull(_pull) { }
    void Init();
    void ToLow();
    void ToHi();
    void Set(bool);
    bool IsHi();
private:
    GPIO_TypeDef *gpio;
    uint16        pin;
    uint          mode;
    uint          pull;
};


struct PinOutputPP : public Pin
{
    PinOutputPP(GPIO_TypeDef *_gpio, uint16 _pin) : Pin(_gpio, _pin, GPIO_MODE_OUTPUT_PP, GPIO_PULLUP) { }
};


struct PinAF_OD : public Pin
{
    PinAF_OD(GPIO_TypeDef *_gpio, uint16 _pin) : Pin(_gpio, _pin, GPIO_MODE_AF_OD, GPIO_PULLUP) { }
};


struct PinAnalog : public Pin
{
    PinAnalog(GPIO_TypeDef *_gpio, uint16 _pin) : Pin(_gpio, _pin, GPIO_MODE_ANALOG, GPIO_NOPULL) { }
};


extern Pin pinWP;
extern PinOutputPP pinBEEP;
extern PinAnalog pinADC;
extern PinAF_OD pinSCL;
extern PinAF_OD pinSDA;
