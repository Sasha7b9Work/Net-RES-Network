#include "ds18b20.h"
#include "stm32f1xx_hal.h"
//--------------------------------------------------
void DelayMicro( uint32_t micros)
{
	micros *= (SystemCoreClock / 1000000) / 9;
	/* Wait till done */
	while (micros--) ;
}
//--------------------------------------------------
void port_init(void)
{
/*  HAL_GPIO_DeInit(GPIOB, GPIO_PIN_11);
  GPIOB->CRH |= GPIO_CRH_MODE11;
  GPIOB->CRH |= GPIO_CRH_CNF11_0;
  GPIOB->CRH &= ~GPIO_CRH_CNF11_1;
	*/

  GPIO_InitTypeDef GPIO_InitStruct;

  GPIO_InitStruct.Pin = GPIO_PIN_2;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;	//GPIO_CRL_MODE0
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}
//--------------------------------------------------
uint8_t ds18b20_Reset(void)
{
  uint16_t status;
 /*
  GPIOB->ODR &= ~GPIO_ODR_ODR11;//Ã­Ã¨Ã§ÃªÃ¨Ã© Ã³Ã°Ã®Ã¢Ã¥Ã­Ã¼
  DelayMicro(485);//Ã§Ã Ã¤Ã¥Ã°Ã¦ÃªÃ  ÃªÃ Ãª Ã¬Ã¨Ã­Ã¨Ã¬Ã³Ã¬ Ã­Ã  480 Ã¬Ã¨ÃªÃ°Ã®Ã±Ã¥ÃªÃ³Ã­Ã¤
  GPIOB->ODR |= GPIO_ODR_ODR11;//Ã¢Ã»Ã±Ã®ÃªÃ¨Ã© Ã³Ã°Ã®Ã¢Ã¥Ã­Ã¼
  DelayMicro(65);//Ã§Ã Ã¤Ã¥Ã°Ã¦ÃªÃ  ÃªÃ Ãª Ã¬Ã¨Ã­Ã¨Ã¬Ã³Ã¬ Ã­Ã  60 Ã¬Ã¨ÃªÃ°Ã®Ã±Ã¥ÃªÃ³Ã­Ã¤
  status = GPIOB->IDR & GPIO_IDR_IDR11;//Ã¯Ã°Ã®Ã¢Ã¥Ã°Ã¿Ã¥Ã¬ Ã³Ã°Ã®Ã¢Ã¥Ã­Ã¼
  DelayMicro(500);//Ã§Ã Ã¤Ã¥Ã°Ã¦ÃªÃ  ÃªÃ Ãª Ã¬Ã¨Ã­Ã¨Ã¬Ã³Ã¬ Ã­Ã  480 Ã¬Ã¨ÃªÃ°Ã®Ã±Ã¥ÃªÃ³Ã­Ã¤
*/
  GPIOA->ODR &= ~GPIO_ODR_ODR2;//Ã­Ã¨Ã§ÃªÃ¨Ã© Ã³Ã°Ã®Ã¢Ã¥Ã­Ã¼
  DelayMicro(485);//Ã§Ã Ã¤Ã¥Ã°Ã¦ÃªÃ  ÃªÃ Ãª Ã¬Ã¨Ã­Ã¨Ã¬Ã³Ã¬ Ã­Ã  480 Ã¬Ã¨ÃªÃ°Ã®Ã±Ã¥ÃªÃ³Ã­Ã¤
  GPIOA->ODR |= GPIO_ODR_ODR2;//Ã¢Ã»Ã±Ã®ÃªÃ¨Ã© Ã³Ã°Ã®Ã¢Ã¥Ã­Ã¼
  DelayMicro(65);//Ã§Ã Ã¤Ã¥Ã°Ã¦ÃªÃ  ÃªÃ Ãª Ã¬Ã¨Ã­Ã¨Ã¬Ã³Ã¬ Ã­Ã  60 Ã¬Ã¨ÃªÃ°Ã®Ã±Ã¥ÃªÃ³Ã­Ã¤
  status = GPIOA->IDR & GPIO_IDR_IDR2;//Ã¯Ã°Ã®Ã¢Ã¥Ã°Ã¿Ã¥Ã¬ Ã³Ã°Ã®Ã¢Ã¥Ã­Ã¼
  DelayMicro(500);//Ã§Ã Ã¤Ã¥Ã°Ã¦ÃªÃ  ÃªÃ Ãª Ã¬Ã¨Ã­Ã¨Ã¬Ã³Ã¬ Ã­Ã  480 Ã¬Ã¨ÃªÃ°Ã®Ã±Ã¥ÃªÃ³Ã­Ã¤



  return (status ? 1 : 0);//Ã¢Ã¥Ã°Ã­Â¸Ã¬ Ã°Ã¥Ã§Ã³Ã«Ã¼Ã²Ã Ã²
}
//----------------------------------------------------------
uint8_t ds18b20_ReadBit(void)
{
  uint8_t bit = 0;
  /*
  GPIOB->ODR &= ~GPIO_ODR_ODR11;//Ã­Ã¨Ã§ÃªÃ¨Ã© Ã³Ã°Ã®Ã¢Ã¥Ã­Ã¼
  DelayMicro(2);
  GPIOB->ODR |= GPIO_ODR_ODR11;//Ã¢Ã»Ã±Ã®ÃªÃ¨Ã© Ã³Ã°Ã®Ã¢Ã¥Ã­Ã¼
  DelayMicro(13);
  bit = (GPIOB->IDR & GPIO_IDR_IDR11 ? 1 : 0);//Ã¯Ã°Ã®Ã¢Ã¥Ã°Ã¿Ã¥Ã¬ Ã³Ã°Ã®Ã¢Ã¥Ã­Ã¼
  DelayMicro(45);
  */
  GPIOA->ODR &= ~GPIO_ODR_ODR2;//Ã­Ã¨Ã§ÃªÃ¨Ã© Ã³Ã°Ã®Ã¢Ã¥Ã­Ã¼
  DelayMicro(2);
  GPIOA->ODR |= GPIO_ODR_ODR2;//Ã¢Ã»Ã±Ã®ÃªÃ¨Ã© Ã³Ã°Ã®Ã¢Ã¥Ã­Ã¼
  DelayMicro(13);
  bit = (GPIOA->IDR & GPIO_IDR_IDR2 ? 1 : 0);//Ã¯Ã°Ã®Ã¢Ã¥Ã°Ã¿Ã¥Ã¬ Ã³Ã°Ã®Ã¢Ã¥Ã­Ã¼
  DelayMicro(45);


  return bit;
}
//-----------------------------------------------
uint8_t ds18b20_ReadByte(void)
{
  uint8_t data = 0;
  for (uint8_t i = 0; i <= 7; i++)
  data += ds18b20_ReadBit() << i;
  return data;
}
//-----------------------------------------------
void ds18b20_WriteBit(uint8_t bit)
{
	/*
  GPIOB->ODR &= ~GPIO_ODR_ODR11;
  DelayMicro(bit ? 3 : 65);
  GPIOB->ODR |= GPIO_ODR_ODR11;
  DelayMicro(bit ? 65 : 3);
  */

  GPIOA->ODR &= ~GPIO_ODR_ODR2;
  DelayMicro(bit ? 3 : 65);
  GPIOA->ODR |= GPIO_ODR_ODR2;
  DelayMicro(bit ? 65 : 3);
}
//-----------------------------------------------
void ds18b20_WriteByte(uint8_t dt)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    ds18b20_WriteBit(dt >> i & 1);
    //Delay Protection
    DelayMicro(5);
  }
}
//-----------------------------------------------
uint8_t ds18b20_init(uint8_t mode)
{
	if(ds18b20_Reset()) return 1;
  if(mode==SKIP_ROM)
  {
		//SKIP ROM
		ds18b20_WriteByte(0xCC);
		//WRITE SCRATCHPAD
		ds18b20_WriteByte(0x4E);
		//TH REGISTER 100 Ã£Ã°Ã Ã¤Ã³Ã±Ã®Ã¢
		ds18b20_WriteByte(0x64);
		//TL REGISTER - 30 Ã£Ã°Ã Ã¤Ã³Ã±Ã®Ã¢
		ds18b20_WriteByte(0x9E);
		//Resolution 12 bit
		ds18b20_WriteByte(RESOLUTION_12BIT);
  }
  return 0;
}
//----------------------------------------------------------
void ds18b20_MeasureTemperCmd(uint8_t mode, uint8_t DevNum)
{
  ds18b20_Reset();
  if(mode==SKIP_ROM)
  {
    //SKIP ROM
    ds18b20_WriteByte(0xCC);
  }
  //CONVERT T
  ds18b20_WriteByte(0x44);
}
//----------------------------------------------------------
void ds18b20_ReadStratcpad(uint8_t mode, uint8_t *Data, uint8_t DevNum)
{
  uint8_t i;
  ds18b20_Reset();
  if(mode==SKIP_ROM)
  {
    //SKIP ROM
    ds18b20_WriteByte(0xCC);
  }
  //READ SCRATCHPAD
  ds18b20_WriteByte(0xBE);
  for(i=0;i<8;i++)
  {
    Data[i] = ds18b20_ReadByte();
  }
}
//----------------------------------------------------------
uint8_t ds18b20_GetSign(uint16_t dt)
{
  if (dt&(1<<11)) return 1;
  else return 0;
}
//----------------------------------------------------------
float ds18b20_Convert(uint16_t dt)
{
  float t;
  float sign = 1.0;

  if(ds18b20_GetSign(dt)){
	  dt = (dt ^ 0xFFFF) + 1;
	  sign = -1.0;
  }

  t = (float) ((dt&0x07FF)>>4);
  t += (float)(dt&0x000F) / 16.0;
  return sign*t;
}
//----------------------------------------------------------
