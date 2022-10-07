#include "hal_i2c.h"
#include "driver/i2c.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static hal_i2c_callback_t _i2c_callback = NULL;

static int8_t i2c_status[I2C_MAX_NUM] = {0};
static int8_t i2c_timeout[I2C_MAX_NUM] = {0};

int hal_i2c_init(hal_i2c_config_t _i2c)
{
    if ((_i2c.port > (I2C_MAX_NUM - 1)) || (_i2c.port < 0))
        return I2C_FAIL;
    if (i2c_status[_i2c.port] != 0)
        return I2C_FAIL;

    i2c_config_t conf = {
        .mode = _i2c.mode,
        .scl_io_num = _i2c.scl_pin,
        .sda_io_num = _i2c.sda_pin,
        .master.clk_speed = _i2c.clk_speed,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
    };

    if (i2c_param_config(_i2c.port, &conf) != I2C_OK)
        return I2C_FAIL;

    if (i2c_driver_install(_i2c.port, _i2c.mode, _i2c.rx_len, _i2c.tx_len, 0) != I2C_OK)
        return I2C_FAIL;

    if (_i2c.callback != NULL)
        _i2c_callback = _i2c.callback;

    i2c_timeout[_i2c.port] = _i2c.timeout;
    i2c_status[_i2c.port] = 1;

    return I2C_OK;
}

int hal_i2c_write_byte(int8_t port, uint8_t dev_addr, uint8_t reg_addr, uint8_t write_buf)
{
    if (i2c_status[port] != 1)
    {
        printf("err: i2c not init\n");
        return I2C_FAIL;
    }

    uint8_t buf[2] = {reg_addr, write_buf};

    return (i2c_master_write_to_device(port, dev_addr, buf, sizeof(buf), pdMS_TO_TICKS(i2c_timeout[port])));
}

int hal_i2c_write_string(int8_t port, uint8_t dev_addr, uint8_t *write_buf, int write_len)
{
    if (i2c_status[port] != 1)
    {
        printf("err: i2c not init\n");
        return I2C_FAIL;
    }

    return (i2c_master_write_to_device(port, dev_addr, write_buf, write_len, pdMS_TO_TICKS(i2c_timeout[port])));
}

int hal_i2c_read_byte(int8_t port, uint8_t dev_addr, uint8_t *reg_addr, int reg_len, uint8_t read_buf)
{
    if (i2c_status[port] != 1)
    {
        printf("err: i2c not init\n");
        return I2C_FAIL;
    }
    return (i2c_master_write_read_device(port, dev_addr, reg_addr, reg_len, &read_buf, 1, pdMS_TO_TICKS(i2c_timeout[port])));
}

int hal_i2c_read_string(int8_t port, uint8_t dev_addr, uint8_t *reg_addr, int reg_len, uint8_t *read_buf, int read_len)
{
    if (i2c_status[port] != 1)
    {
        printf("err: i2c not init\n");
        return I2C_FAIL;
    }
    return (i2c_master_write_read_device(port, dev_addr, reg_addr, reg_len, read_buf, read_len, pdMS_TO_TICKS(i2c_timeout[port])));
}
