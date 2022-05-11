// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


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


void user_delay_ms(uint period);
int8 user_i2c_read(uint8 dev_id, uint8 reg_addr, uint8 *reg_data, uint16 len);
int8 user_i2c_write(uint8 dev_id, uint8 reg_addr, uint8 *reg_data, uint16 len);

int8 user_i2c_write8(uint8 dev_id, uint8 data);
int8 user_i2c_read16(uint8 dev_id, uint8 *data);
