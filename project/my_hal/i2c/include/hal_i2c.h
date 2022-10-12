#ifndef __HAL_I2C_H__
#define __HAL_I2C_H__

#include <stdlib.h>
#include "esp_err.h"
#include "driver/i2c.h"

#define I2C_OK      ESP_OK
#define I2C_FAIL    ESP_FAIL

typedef enum{
    HAL_I2C_MODE_SLAVE = I2C_MODE_SLAVE,   /*!< I2C slave mode */
    HAL_I2C_MODE_MASTER = I2C_MODE_MASTER,      /*!< I2C master mode */
    HAL_I2C_MODE_MAX = I2C_MODE_MAX,
} hal_i2c_mode_t;



#define I2C_MAX_NUM     2

typedef void(*hal_i2c_callback_t)(void *);

typedef struct 
{
    hal_i2c_mode_t mode;
    int8_t port;
    int8_t sda_pin;
    int8_t scl_pin;
    int8_t tx_len;
    int8_t rx_len;
    uint32_t clk_speed;
    int timeout;
    hal_i2c_callback_t callback;
}hal_i2c_config_t;

int hal_i2c_init(hal_i2c_config_t _i2c);
int hal_i2c_write_byte(int8_t port, uint8_t dev_addr, uint8_t reg_addr, uint8_t write_buf);
int hal_i2c_write_string(int8_t port, uint8_t dev_addr, uint8_t *write_buf, int write_len);
int hal_i2c_read_byte(int8_t port, uint8_t dev_addr, uint8_t *reg_addr, int reg_len, uint8_t read_buf);
int hal_i2c_read_string(int8_t port, uint8_t dev_addr, uint8_t *reg_addr, int reg_len, uint8_t *read_buf, int read_len);
#endif