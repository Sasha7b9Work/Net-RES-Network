// 2022/03/12 09:24:45 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "main.h"
#include "Modules/ST7735/ST7735.h"
#include <stm32f1xx_hal.h>


/*
    B11 - RST    Reset
    B14 - RS     D/C

    B12 - CS
    B13 - SCK    SCL
    B15 - SDA    MOSI
*/


namespace Display
{
    static const uint16 PIN_RESET = GPIO_PIN_11;
    static const uint16 PIN_DC = GPIO_PIN_14;

    static SPI_HandleTypeDef handle;
}


void Display::Init()
{
    __HAL_RCC_SPI2_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    GPIO_InitTypeDef spi_struct = {0};

    spi_struct.Pin = GPIO_PIN_12 |     // CS
                     GPIO_PIN_13 |     // SCL
                     GPIO_PIN_15;      // MOSI
    spi_struct.Mode = GPIO_MODE_AF_PP;
    spi_struct.Speed = GPIO_SPEED_FREQ_HIGH;

    HAL_GPIO_Init(GPIOB, &spi_struct);

    handle.Instance = SPI2;
    handle.Init.Mode = SPI_MODE_MASTER;
    handle.Init.Direction = SPI_DIRECTION_2LINES;
    handle.Init.DataSize = SPI_DATASIZE_8BIT;
    handle.Init.CLKPolarity = SPI_POLARITY_LOW;
    handle.Init.CLKPhase = SPI_PHASE_1EDGE;
    handle.Init.NSS = SPI_NSS_HARD_OUTPUT;
    handle.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
    handle.Init.FirstBit = SPI_FIRSTBIT_MSB;
    handle.Init.TIMode = SPI_TIMODE_DISABLE;
    handle.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    handle.Init.CRCPolynomial = 10;

    if (HAL_SPI_Init(&handle) != HAL_OK)
    {
        Error_Handler();
    }

    GPIO_InitTypeDef gpio_struct = {0};

    HAL_GPIO_WritePin(GPIOB, PIN_RESET | PIN_DC, GPIO_PIN_RESET);

    gpio_struct.Pin = PIN_RESET | PIN_DC;
    gpio_struct.Mode = GPIO_MODE_OUTPUT_PP;
    gpio_struct.Pull = GPIO_NOPULL;
    gpio_struct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOB, &gpio_struct);
}


void Display::Update()
{

}


void Display::BeginScene(Color)
{

}


void Display::EndScene()
{

}
