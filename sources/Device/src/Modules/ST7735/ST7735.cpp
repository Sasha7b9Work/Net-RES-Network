// 2022/03/12 09:24:45 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "main.h"
#include "Modules/ST7735/ST7735.h"
#include "Hardware/Timer.h"
#include "Modules/ST7735/Font/Font.h"
#include "Utils/Text/String.h"
#include <stm32f1xx_hal.h>
#include <cstring>


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

    static void SendCommand(uint8);
    static void SendData8(uint8);
    static void SendData16(uint16);
    static void SetWindow(uint8 startX, uint8 startY, uint8 stopX, uint8 stopY);

    namespace Buffer
    {
        static uint8 buffer[WIDTH * HEIGHT / 2];       // Четырёхбитный цвет

        static uint8 *FirstPixels()
        {
            return &buffer[0];
        }

        static void SetPoint(int x, int y)
        {
            if (x < 0)       { return; }
            if (y < 0)       { return; }
            if (x >= WIDTH)  { return; }
            if (y >= HEIGHT) { return; }

            uint8 *pixels = &buffer[(y * WIDTH + x) / 2];

            uint8 value = *pixels;

            if (x % 2)
            {
                value &= 0x0F;
                value |= (Color::GetCurrent() << 4);
            }
            else
            {
                value &= 0xF0;
                value |= Color::GetCurrent();
            }

            *pixels = value;
        }

        static void Fill(Color::E color)
        {
            uint8 value = (uint8)((int)(color) | (int)(color << 4));

            std::memset(buffer, value, WIDTH * HEIGHT / 2);
        }
    }
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


void Display::Update()
{
    Color::E color2 = Color::WHITE;
    Color::E color1 = Color::BLACK;

    BeginScene(color1);

    Rectangle(140, 30).Fill(10, 5, color2);

    static int x0 = 10;

    VLine(7).Draw(x0, 23, color1);

    x0++;
    
    if (x0 == 150)
    {
        x0 = 0;
    }

    static int y0 = 40;

    HLine(20).Draw(5, y0, color2);

    y0++;

    if (y0 == HEIGHT)
    {
        y0 = 40;
    }

    Font::Set(TypeFont::_8);

    String<> test_string;
    test_string.SetFormat("Тестовая строка");
    test_string.Draw(40, 10, color1);

    int y = 45;
    int x = 30;
    int dY = 15;

    String<>("Давление : 100 МПa").Draw(x, y, color2);
    String<>("Освещённость : 100 люкс").Draw(x, y + dY);
    String<>("Скорость : 10 км/сек").Draw(x, y + 2 * dY);
    String<>("Температура : 23 С").Draw(x, y + 3 * dY);
    String<>("Влажность : 100%").Draw(x, y + 4 * dY);

    EndScene();
}


void Display::BeginScene(Color::E color)
{
    Buffer::Fill(color);
}


void Display::EndScene()
{
    Display::SetWindow((uint8)0, (uint8)0, (uint8)WIDTH, (uint8)HEIGHT);

    Display::SendCommand(0x2C);         // RAMWR

    uint8* points = Buffer::FirstPixels();

    SPI2->CR1 |= SPI_CR1_DFF;
    SET_DC;
    RESET_CS;

    for (int i = 0; i < WIDTH * HEIGHT / 2; i++)
    {
        while (!(SPI2->SR & SPI_SR_TXE));
        SPI2->DR = COLOR((*points) & 0x0F);

        while (!(SPI2->SR & SPI_SR_TXE));
        while ((SPI2->SR & SPI_SR_BSY));

        while (!(SPI2->SR & SPI_SR_TXE));
        SPI2->DR = COLOR(((*points) >> 4) & 0x0F);

        while (!(SPI2->SR & SPI_SR_TXE));
        while ((SPI2->SR & SPI_SR_BSY));

        points++;
    }

    SET_CS;

    SPI2->CR1 &= ~SPI_CR1_DFF;
}


void Rectangle::Fill(int x0, int y0, Color::E color)
{
    Color::SetCurrent(color);

    for (int x = x0; x < x0 + width; x++)
    {
        VLine(height).Draw(x, y0);
    }
}


void Rectangle::Draw(int x, int y, Color::E color)
{
    HLine(width).Draw(x, y, color);
    HLine(width).Draw(x, y + height);
    VLine(height).Draw(x, y);
    VLine(height).Draw(x + width, y);
}


void HLine::Draw(int x0, int y, Color::E color)
{
    Color::SetCurrent(color);

    for (int x = x0; x < x0 + width; x++)
    {
        Display::Buffer::SetPoint(x, y);
    }
}


void VLine::Draw(int x, int y0, Color::E color)
{
    Color::SetCurrent(color);

    for (int y = y0; y < y0 + height; y++)
    {
        Display::Buffer::SetPoint(x, y);
    }
}


void Point::Set(int x, int y, Color::E color)
{
    Color::SetCurrent(color);

    Display::Buffer::SetPoint(x, y);
}


void Display::SetWindow(uint8 x, uint8 y, uint8 width, uint8 height)
{
    int stopX = x + width - 1;
    int stopY = y + height - 1;

    SendCommand(0x2A);      // CASET
    SendData8(0x00);
    SendData8(x);
    SendData8(0x00);
    SendData8((uint8)stopX);

    SendCommand(0x2B);      // RASET
    SendData8(0x00);
    SendData8(y);
    SendData8(0x00);
    SendData8((uint8)stopY);
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
