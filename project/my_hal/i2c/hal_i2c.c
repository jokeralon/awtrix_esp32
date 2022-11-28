#include "hal_i2c.h"
#include "driver/i2c.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static hal_i2c_callback_t _i2c_callback[I2C_MAX_NUM] = {NULL};

static int8_t i2c_status[I2C_MAX_NUM] = {0};
static int8_t i2c_timeout[I2C_MAX_NUM] = {0};

/**
 * @brief     i2c init
 * @param[in] _i2c i2c init config
 * @return    status code
 *            - 0 success
 *            - -1 failed
 * @note      none
 */
int hal_i2c_init(hal_i2c_config_t _i2c)
{
    if ((_i2c.port > (I2C_MAX_NUM - 1)) || (_i2c.port < 0))
        return I2C_FAIL;

    if (_i2c.callback != NULL)
        _i2c_callback[_i2c.port] = _i2c.callback;

    i2c_config_t conf = {
        .mode = _i2c.mode,
        .scl_io_num = _i2c.scl_pin,
        .sda_io_num = _i2c.sda_pin,
        .master.clk_speed = _i2c.clk_speed,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
    };

    if (i2c_param_config(_i2c.port, &conf) != I2C_OK)
    {
        _i2c_callback[_i2c.port]( HAL_I2C_EVENT_INIT_ERROR, "i2c_param_config error" );
        return I2C_FAIL;
    }else
        _i2c_callback[_i2c.port]( HAL_I2C_EVENT_INIT, NULL );


    if (i2c_driver_install(_i2c.port, _i2c.mode, _i2c.rx_len, _i2c.tx_len, 0) != I2C_OK)
    {
        _i2c_callback[_i2c.port]( HAL_I2C_EVENT_INIT_ERROR, "i2c_driver_install error");
        return I2C_FAIL;
    }else
        _i2c_callback[_i2c.port]( HAL_I2C_EVENT_INIT, NULL );

    i2c_timeout[_i2c.port] = _i2c.timeout;
    i2c_status[_i2c.port] = 1;

    return I2C_OK;
}

/**
 * @brief     write memory byte
 * @param[in] port
 * @param[in] dev_addr
 * @param[in] reg_addr
 * @param[in] write_buf
 * @return    status code
 *            - 0 success
 *            - -1 failed
 * @note      none
 */
int hal_i2c_write_byte(int8_t port, uint8_t dev_addr, uint8_t reg_addr, uint8_t write_buf)
{

    esp_err_t ret = ESP_FAIL;

    if (i2c_status[port] != 1)
    {
        printf("err: i2c not init\n");
        return I2C_FAIL;
    }

    uint8_t buf[2] = {reg_addr, write_buf};

    ret = (i2c_master_write_to_device(port, dev_addr, buf, sizeof(buf), pdMS_TO_TICKS(i2c_timeout[port])));
    if (_i2c_callback[port] != NULL)
        _i2c_callback[port]((ret == ESP_OK) ? HAL_I2C_EVENT_SEND_OK : HAL_I2C_EVENT_SEND_ERROR, NULL);

    return ret;
}

/**
 * @brief     write memory string
 * @param[in] port
 * @param[in] dev_addr
 * @param[in] *write_buf
 * @param[in] write_len 
 * @return    status code
 *            - 0 success
 *            - -1 failed
 * @note      none
 */
int hal_i2c_write_string(int8_t port, uint8_t dev_addr, uint8_t *write_buf, int write_len)
{
    if (i2c_status[port] != 1)
    {
        printf("err: i2c not init\n");
        return I2C_FAIL;
    }

    return (i2c_master_write_to_device(port, dev_addr, write_buf, write_len, pdMS_TO_TICKS(i2c_timeout[port])));
}

/**
 * @brief     read memory byte
 * @param[in] port
 * @param[in] dev_addr
 * @param[in] *reg_addr
 * @param[in] reg_len
 * @param[in] read_buf
 * @return    status code
 *            - 0 success
 *            - -1 failed
 * @note      none
 */
int hal_i2c_read_byte(int8_t port, uint8_t dev_addr, uint8_t *reg_addr, int reg_len, uint8_t read_buf)
{
    esp_err_t ret = ESP_FAIL;
    if (i2c_status[port] != 1)
    {
        printf("err: i2c not init\n");
        return I2C_FAIL;
    }
    ret = (i2c_master_write_read_device(port, dev_addr, reg_addr, reg_len, &read_buf, 1, pdMS_TO_TICKS(i2c_timeout[port])));
    if (_i2c_callback[port] != NULL)
        _i2c_callback[port]((ret == ESP_OK) ? HAL_I2C_EVENT_RECV_OK : HAL_I2C_EVENT_RECV_ERROR, NULL);

    return ret;
}

/**
 * @brief     read memory string
 * @param[in] port
 * @param[in] dev_addr
 * @param[in] *reg_addr
 * @param[in] reg_len
 * @param[in] read_buf
 * @param[in] read_len
 * @return    status code
 *            - 0 success
 *            - -1 failed
 * @note      none
 */
int hal_i2c_read_string(int8_t port, uint8_t dev_addr, uint8_t *reg_addr, int reg_len, uint8_t *read_buf, int read_len)
{
    esp_err_t ret = ESP_FAIL;

    if (i2c_status[port] != 1)
    {
        printf("err: i2c not init\n");
        return I2C_FAIL;
    }
    ret = (i2c_master_write_read_device(port, dev_addr, reg_addr, reg_len, read_buf, read_len, pdMS_TO_TICKS(i2c_timeout[port])));
    if (_i2c_callback[port] != NULL)
        _i2c_callback[port]((ret == ESP_OK) ? HAL_I2C_EVENT_RECV_OK : HAL_I2C_EVENT_RECV_ERROR, NULL);

    return ret;
}
