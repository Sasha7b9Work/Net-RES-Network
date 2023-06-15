/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define pin17_5_Pin GPIO_PIN_0
#define pin17_5_GPIO_Port GPIOA
#define XP2_5_Pin GPIO_PIN_1
#define XP2_5_GPIO_Port GPIOA
#define ADC1_3_BAT_Pin GPIO_PIN_3
#define ADC1_3_BAT_GPIO_Port GPIOA
#define DD2_CS_Pin GPIO_PIN_4
#define DD2_CS_GPIO_Port GPIOA
#define DD2_CLK_Pin GPIO_PIN_5
#define DD2_CLK_GPIO_Port GPIOA
#define DD2_DO_Pin GPIO_PIN_6
#define DD2_DO_GPIO_Port GPIOA
#define DD2_DI_Pin GPIO_PIN_7
#define DD2_DI_GPIO_Port GPIOA
#define DD2_WP_Pin GPIO_PIN_0
#define DD2_WP_GPIO_Port GPIOB
#define pin_18_Pin GPIO_PIN_1
#define pin_18_GPIO_Port GPIOB
#define TFT_RST_Pin GPIO_PIN_11
#define TFT_RST_GPIO_Port GPIOB
#define TFT_CS_Pin GPIO_PIN_12
#define TFT_CS_GPIO_Port GPIOB
#define TFT_SCL_Pin GPIO_PIN_13
#define TFT_SCL_GPIO_Port GPIOB
#define TFT_DC_Pin GPIO_PIN_14
#define TFT_DC_GPIO_Port GPIOB
#define TFT_SDA_Pin GPIO_PIN_15
#define TFT_SDA_GPIO_Port GPIOB
#define XP4_3_USART1_Pin GPIO_PIN_9
#define XP4_3_USART1_GPIO_Port GPIOA
#define XP4_4_USART1_Pin GPIO_PIN_10
#define XP4_4_USART1_GPIO_Port GPIOA
#define Beeper_Pin GPIO_PIN_4
#define Beeper_GPIO_Port GPIOB
#define Button1_Pin GPIO_PIN_8
#define Button1_GPIO_Port GPIOB
#define Button2_Pin GPIO_PIN_9
#define Button2_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
