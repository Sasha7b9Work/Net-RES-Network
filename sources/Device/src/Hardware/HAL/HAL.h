// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include <stm32f1xx_hal.h>


namespace HAL
{
    void Init();

    void Delay(unsigned int timeMS);
}


namespace HAL_I2C1
{
    extern void *handle;     // I2C_HandleTypeDef

    void Init();
}


void user_delay_ms(uint32_t period);
int8_t user_i2c_read(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len);
int8_t user_i2c_write(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len);

int8_t user_i2c_write8(uint8_t dev_id, uint8_t data);
int8_t user_i2c_read16(uint8_t dev_id, uint8_t *data);
