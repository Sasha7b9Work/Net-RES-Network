#ifndef __BH1750_H__
#define __BH1750_H__

#include "i2c.h"


#define BH1750_Addr 	0x46
#define BH1750_ON   	0x01
#define BH1750_CON  	0x10
#define BH1750_ONE  	0x20
#define BH1750_RSET 	0x07


void BH1750_Start(void);
void BH1750_Read(void);
void BH1750_Convert(void);
float BH1750_GetLumen(void);

#endif

