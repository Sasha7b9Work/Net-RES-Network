#include "bh1750.h"

extern uint8_t aTxBuffer[];
extern I2C_HandleTypeDef hi2c1;

float BH1750_result_lx=0;
uint16_t BH1750_result=0;
uint8_t value1 = 0;
uint8_t value2 = 0;

HAL_StatusTypeDef BH1750_WriteReg(uint8_t cmd)
{
	aTxBuffer[0] = cmd;
	HAL_StatusTypeDef HAL_result;
	HAL_result = I2C_WriteBuffer(hi2c1, BH1750_Addr, 1);	//1 Byte
	while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY);

	return HAL_result;
}


void BH1750_Start(void)
{
	BH1750_WriteReg(BH1750_ON);
	BH1750_WriteReg(BH1750_RSET);
	BH1750_WriteReg(BH1750_CON);
}

void BH1750_Read(void)
{   	
	HAL_StatusTypeDef HAL_result;
	HAL_result = I2C_WriteBuffer(hi2c1, BH1750_Addr, 1);	//1 Byte
	while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY);
	I2C_ReadBuffer(hi2c1, BH1750_Addr, 2);	//1 Byte
	while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY);

	value1 = aTxBuffer[0];
	value2 = aTxBuffer[1];
}

void BH1750_Convert(void)
{
	BH1750_result = value1;
	BH1750_result = (BH1750_result<<8)+value2;
	BH1750_result_lx = (float)BH1750_result/1.2;
}

float BH1750_GetLumen(void)
{
    BH1750_Read();
    BH1750_Convert();
    return BH1750_result_lx;
}



