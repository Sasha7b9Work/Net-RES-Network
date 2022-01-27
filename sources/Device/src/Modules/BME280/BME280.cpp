#include "Modules/BME280/BME280.h"
#include "Hardware/I2C/i2c.h"
#include "Modules/BME280/bme280_driver.h"


static bme280_dev dev;


void BME280::Init()
{
    dev.dev_id = BME280_I2C_ADDR_SEC;
    dev.intf = BME280_I2C_INTF;
    dev.read = user_i2c_read;
    dev.write = user_i2c_write;
    dev.delay_ms = user_delay_ms;

    bme280_init(&dev);

    uint8_t settings_sel;

    dev.settings.osr_h = BME280_OVERSAMPLING_1X;
    dev.settings.osr_p = BME280_OVERSAMPLING_16X;
    dev.settings.osr_t = BME280_OVERSAMPLING_2X;
    dev.settings.filter = BME280_FILTER_COEFF_16;
    dev.settings.standby_time = BME280_STANDBY_TIME_62_5_MS;

    settings_sel = BME280_OSR_PRESS_SEL;
    settings_sel |= BME280_OSR_TEMP_SEL;
    settings_sel |= BME280_OSR_HUM_SEL;
    settings_sel |= BME280_STANDBY_SEL;
    settings_sel |= BME280_FILTER_SEL;

    bme280_set_sensor_settings(settings_sel, &dev);

    bme280_set_sensor_mode(BME280_NORMAL_MODE, &dev);

    /* Delay while the sensor completes a measurement */
    dev.delay_ms(70);
}


void BME280::GetMeasure(char buffer[128])
{
    bme280_data comp_data;

    bme280_get_sensor_data(BME280_ALL, &comp_data, &dev);

    sprintf(buffer, "t:%0.2f*C   p:%0.2fhPa, %0.2fmmHg   h:%0.2f%%\n",
        comp_data.temperature, comp_data.pressure/100, comp_data.pressure/133.3223684, comp_data.humidity);
}
