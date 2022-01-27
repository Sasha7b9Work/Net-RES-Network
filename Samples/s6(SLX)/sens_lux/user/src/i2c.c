
#include "i2c.h"

uint8_t aTxBuffer[8];

//----------------------------------------------------------------//
HAL_StatusTypeDef I2C_WriteBuffer(I2C_HandleTypeDef hi, uint8_t DEV_ADDR, uint8_t sizebuf)
{
	return HAL_I2C_Master_Transmit(&hi, (uint16_t)DEV_ADDR,(uint8_t*) &aTxBuffer, (uint16_t)sizebuf, (uint32_t)50);
}
//----------------------------------------------------------------//
HAL_StatusTypeDef I2C_ReadBuffer(I2C_HandleTypeDef hi, uint8_t DEV_ADDR, uint8_t sizebuf)
{
	return HAL_I2C_Master_Receive(&hi, (uint16_t)DEV_ADDR, (uint8_t*) &aTxBuffer, (uint16_t)sizebuf, (uint32_t)50);
}
//----------------------------------------------------------------//
