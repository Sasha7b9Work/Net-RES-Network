// 2022/03/12 09:24:45 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "main.h"
#include "Modules/ST7735/ST7735.h"
#include "Hardware/Timer.h"
#include "Display/Font/Font.h"
#include "Utils/Text/String.h"
#include "Display/Display.h"
#include <stm32f1xx_hal.h>
#include <cstring>


/*
    B11 - RST    Reset
    B14 - RS     D/C

    B12 - CS
    B13 - SCK    SCL
    B15 - SDA    MOSI
*/


namespace ST7735
{
#define SET_DC   HAL_GPIO_WritePin(GPIOB, PIN_DC, GPIO_PIN_SET);
#define RESET_DC HAL_GPIO_WritePin(GPIOB, PIN_DC, GPIO_PIN_RESET);
#define SET_CS   HAL_GPIO_WritePin(GPIOB, PIN_CS, GPIO_PIN_SET);
#define RESET_CS HAL_GPIO_WritePin(GPIOB, PIN_CS, GPIO_PIN_RESET);

    static const uint16 PIN_RESET = GPIO_PIN_11;
    static const uint16 PIN_DC = GPIO_PIN_14;
    static const uint16 PIN_CS = GPIO_PIN_12;

    static SPI_HandleTypeDef handle;

    static void SendCommand(uint8);
    static void SendData8(uint8);
    static void SendData16(uint16);
    static void SetWindow(int startX, int startY, int stopX, int stopY);

    const uint16 colors[Color::Count] =
    {
        0xffff,
        0x0000,
        MAKE_COLOR(31, 0, 0),
        MAKE_COLOR(0, 63, 0),
        MAKE_COLOR(0, 0, 31),
        MAKE_COLOR(15, 31, 15),
        MAKE_COLOR(7, 15, 7),
        MAKE_COLOR(3, 6, 3)
    };
}


void ST7735::Init()
{
    __HAL_RCC_SPI2_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    GPIO_InitTypeDef spi_struct = {0};

    spi_struct.Pin = GPIO_PIN_13 |     // SCL
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
    handle.Init.NSS = SPI_NSS_SOFT;
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

    HAL_GPIO_WritePin(GPIOB, PIN_RESET | PIN_DC | PIN_CS, GPIO_PIN_RESET);

    gpio_struct.Pin = PIN_RESET | PIN_DC | PIN_CS;
    gpio_struct.Mode = GPIO_MODE_OUTPUT_PP;
    gpio_struct.Pull = GPIO_NOPULL;
    gpio_struct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOB, &gpio_struct);

    SPI2->CR1 |= SPI_CR1_SPE;

    HAL_GPIO_WritePin(GPIOB, PIN_CS, GPIO_PIN_RESET);

    HAL_GPIO_WritePin(GPIOB, PIN_RESET, GPIO_PIN_SET);
    HAL_Delay(5);
    HAL_GPIO_WritePin(GPIOB, PIN_RESET, GPIO_PIN_RESET);
    HAL_Delay(5);
    HAL_GPIO_WritePin(GPIOB, PIN_RESET, GPIO_PIN_SET);
    HAL_Delay(5);

    SendCommand(0x01);      // SWRESET Software reset
    HAL_Delay(12);

    SendCommand(0x11);      // SLPOUT Sleep out
    HAL_Delay(12);

    SendCommand(0x3A);      // COLMOD Interface pixel format
    SendData8(0x05);        // 16 bit / pixel

    SendCommand(0x36);      // MADCTL Memory Data Access Control
    SendData8(0xA0);

    SendCommand(0xB1);      // FRMCTR1 Frame rate
    SendData16(0x000F);
    SendData16(0x000F);
    SendData16(0x000F);

    SendCommand(0x29);      // DISPON Display on
}


void ST7735::WriteBuffer(uint8 *points)
{
    SetWindow((uint8)0, (uint8)0, (uint8)Display::WIDTH, (uint8)Display::HEIGHT);

    SendCommand(0x2C);         // RAMWR

    SPI2->CR1 |= SPI_CR1_DFF;
    SET_DC;
    RESET_CS;

    for (int i = 0; i < Display::WIDTH * Display::HEIGHT / 2; i++)
    {
        while (!(SPI2->SR & SPI_SR_TXE));
        SPI2->DR = colors[(*points) & 0x0F];

        while (!(SPI2->SR & SPI_SR_TXE));
        while ((SPI2->SR & SPI_SR_BSY));

        while (!(SPI2->SR & SPI_SR_TXE));
        SPI2->DR = colors[((*points) >> 4) & 0x0F];

        while (!(SPI2->SR & SPI_SR_TXE));
        while ((SPI2->SR & SPI_SR_BSY));

        points++;
    }

    SET_CS;

    SPI2->CR1 &= ~SPI_CR1_DFF;
}


void ST7735::WriteBuffer(int x0, int y0, int width, int height)
{
    SetWindow(x0, y0, width, height);

    SendCommand(0x2C);

    SPI2->CR1 |= SPI_CR1_DFF;
    SET_DC;
    RESET_CS;

    for (int y = y0; y < y0 + height; y++)
    {
        for (int x = x0; x < x0 + width; x += 2)
        {
            uint8 points = Display::Buffer::GetPixels(x, y);

            while (!(SPI2->SR & SPI_SR_TXE));
            SPI2->DR = colors[points & 0x0F];

            while (!(SPI2->SR & SPI_SR_TXE));
            while ((SPI2->SR & SPI_SR_BSY));

            while (!(SPI2->SR & SPI_SR_TXE));
            SPI2->DR = colors[(points >> 4) & 0x0F];

            while (!(SPI2->SR & SPI_SR_TXE));
            while ((SPI2->SR & SPI_SR_BSY));
        }
    }

    SET_CS;

    SPI2->CR1 &= ~SPI_CR1_DFF;
}


void ST7735::SetWindow(int x, int y, int width, int height)
{
    int stopX = x + width - 1;
    int stopY = y + height - 1;

    SendCommand(0x2A);      // CASET
    SendData8(0x00);
    SendData8((uint8)x);
    SendData8(0x00);
    SendData8((uint8)stopX);

    SendCommand(0x2B);      // RASET
    SendData8(0x00);
    SendData8((uint8)y);
    SendData8(0x00);
    SendData8((uint8)stopY);
}


void ST7735::SendData16(uint16 data)
{
    SET_DC;
    RESET_CS;

    SPI2->CR1 |= SPI_CR1_DFF;

    while (!(SPI2->SR & SPI_SR_TXE)) {};
    SPI2->DR = data;

    while (!(SPI2->SR & SPI_SR_TXE)) {};
    while ((SPI2->SR & SPI_SR_BSY)) {};

    SET_CS;
}


void ST7735::SendData8(uint8 data)
{
    SET_DC;
    RESET_CS;

    while ((SPI2->SR & SPI_SR_TXE) == RESET);
    SPI2->DR = data;

    while ((SPI2->SR & SPI_SR_TXE) == RESET);
    while ((SPI2->SR & SPI_SR_BSY) != RESET);

    SET_CS;
}


void ST7735::SendCommand(uint8 data)
{
    RESET_DC;
    RESET_CS;

    SPI2->CR1 &= ~SPI_CR1_DFF;

    while (!(SPI2->SR & SPI_SR_TXE));
    SPI2->DR = data;

    while (!(SPI2->SR & SPI_SR_TXE));
    while ((SPI2->SR & SPI_SR_BSY));

    SET_CS;
}
