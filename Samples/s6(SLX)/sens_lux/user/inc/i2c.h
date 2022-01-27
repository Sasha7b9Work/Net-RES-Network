#ifndef __I2C_H
#define __I2C_H

#include "stm32f1xx_hal.h"


HAL_StatusTypeDef I2C_WriteBuffer(I2C_HandleTypeDef hi, uint8_t DEV_ADDR, uint8_t sizebuf);
HAL_StatusTypeDef I2C_ReadBuffer(I2C_HandleTypeDef hi, uint8_t DEV_ADDR, uint8_t sizebuf);


#endif // __I2C_H
