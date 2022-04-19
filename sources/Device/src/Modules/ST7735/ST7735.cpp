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
#define SET_DC   HAL_GPIO_WritePin(GPIOB, Display::PIN_DC, GPIO_PIN_SET);
#define RESET_DC HAL_GPIO_WritePin(GPIOB, Display::PIN_DC, GPIO_PIN_RESET);
#define SET_CS   HAL_GPIO_WritePin(GPIOB, Display::PIN_CS, GPIO_PIN_SET);
#define RESET_CS HAL_GPIO_WritePin(GPIOB, Display::PIN_CS, GPIO_PIN_RESET);

    static const uint16 PIN_RESET = GPIO_PIN_11;
    static const uint16 PIN_DC = GPIO_PIN_14;
    static const uint16 PIN_CS = GPIO_PIN_12;

    static SPI_HandleTypeDef handle;

    void SendCommand(uint8);
    void SendData8(uint8);
    void SendData16(uint16);
    void SetWindow(uint8 startX, uint8 startY, uint8 stopX, uint8 stopY);
}


void Display::Init()
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
    handle.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
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

    SendCommand(0x01);
    HAL_Delay(12);

    SendCommand(0x11);
    HAL_Delay(12);

    SendCommand(0x3A);
    SendData8(0x05);

    SendCommand(0x36);
    SendData8(0xA0);

    SendCommand(0xB1);
    SendData16(0x000F);
    SendData16(0x000F);
    SendData16(0x000F);

    SendCommand(0x29);
}


void Display::Update()
{
    BeginScene(Color::WHITE);
}


void Display::BeginScene(Color)
{
    Rectangle(50, 50).Fill(10, 10, Color::BLACK);
}


void Rectangle::Fill(int x, int y, Color::E color)
{
    Color::SetCurrent(color);

    Display::SetWindow((uint8)x, (uint8)y, (uint8)width, (uint8)height);

    Display::SendCommand(0x2C);

    SPI2->CR1 |= SPI_CR1_DFF;
    SET_DC;
    RESET_CS;

    for (int i = 0; i < width * height; i++) {
        while (!(SPI2->SR & SPI_SR_TXE));
        SPI2->DR = 0xf0f0;

        while (!(SPI2->SR & SPI_SR_TXE));
        while ((SPI2->SR & SPI_SR_BSY));
    }

    SET_CS;

    SPI2->CR1 &= ~SPI_CR1_DFF;
}


void Rectangle::Draw(int x, int y, Color::E color)
{
    Color::SetCurrent(color);
}


void Point::Set(int x, int y, Color::E color)
{
    Color::SetCurrent(color);
}


void Display::SetWindow(uint8 startX, uint8 startY, uint8 stopX, uint8 stopY)
{
    SendCommand(0x2A);
    SendData8(0x00);
    SendData8(startX);
    SendData8(0x00);
    SendData8(stopX);

    SendCommand(0x2B);
    SendData8(0x00);
    SendData8(startY);
    SendData8(0x00);
    SendData8(stopY);
}


void Display::SendData16(uint16 data)
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


void Display::SendData8(uint8 data)
{
    SET_DC;
    RESET_CS;

    while ((SPI2->SR & SPI_SR_TXE) == RESET);
    SPI2->DR = data;

    while ((SPI2->SR & SPI_SR_TXE) == RESET);
    while ((SPI2->SR & SPI_SR_BSY) != RESET);

    SET_CS;
}


void Display::SendCommand(uint8 data)
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
