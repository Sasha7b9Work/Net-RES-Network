#include "main.h"
#include "i2c.h"
#include "usb_device.h"
#include "bme280_application.h"
#include "Modules/HC12/HC12.h"
#include "Hardware/HAL/HAL.h"


int main(void)
{
    HAL::Init();
    MX_I2C1_Init();
    MX_USB_DEVICE_Init();

    HC12_Init();

    struct bme280_dev dev;

    dev.dev_id = BME280_I2C_ADDR_SEC;
    dev.intf = BME280_I2C_INTF;
    dev.read = user_i2c_read;
    dev.write = user_i2c_write;
    dev.delay_ms = user_delay_ms;

    bme280_init(&dev);

    while (1)
    {
        stream_sensor_data_normal_mode(&dev);
    }
}


void _Error_Handler(char *file, int line)
{
  while(1)
  {
  }
}


#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
