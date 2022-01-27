#include "Modules/BME280/BME280.h"
#include "bme280_application.h"
#include "i2c.h"


static struct bme280_dev dev;


void BME280::Init()
{
    dev.dev_id = BME280_I2C_ADDR_SEC;
    dev.intf = BME280_I2C_INTF;
    dev.read = user_i2c_read;
    dev.write = user_i2c_write;
    dev.delay_ms = user_delay_ms;

    bme280_init(&dev);
}


void BME280::Update()
{
    stream_sensor_data_normal_mode(&dev);
}
