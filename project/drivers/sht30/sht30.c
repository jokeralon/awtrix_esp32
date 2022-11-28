#include "sht30.h"
#include "esp_err.h"
#include "esp_log.h"
#include "hal_i2c.h"

const static char *TAG = "sth30";

/**
 * @brief     sht30 callback event
 * @param[in] *arge callback value
 * @return    none
 * @note      none
 */
void __sht30_callback(hal_i2c_event_e event, void *param)
{
    ESP_LOGI(TAG, "sht30 event : %d", event);
}

/**
 * @brief     write memory bytes
 * @param[in] *handle points to a mpu6050 handle structure
 * @param[in] addr is the memory address
 * @param[in] *buf points to a data buffer
 * @param[in] len is the data length
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 *            - 2 len is invalid
 * @note      none
 */
static void sht30_set_reg_addr(uint8_t *buf, sht30_reg_add_t reg_add)
{
    buf[0] = (uint8_t)(reg_add >> 8);
    buf[1] = (uint8_t)(reg_add);
}

/**
 * @brief     write memory bytes
 * @param[in] *handle points to a mpu6050 handle structure
 * @param[in] addr is the memory address
 * @param[in] *buf points to a data buffer
 * @param[in] len is the data length
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 *            - 2 len is invalid
 * @note      none
 */
int sht30_get_temp(sht30_value_t *sht30)
{

    if (sht30 == NULL)
        return I2C_FAIL;

    uint8_t cmd[2];
    uint8_t data[6];

    sht30_set_reg_addr(cmd, READOUT_FOR_PERIODIC_MODE);

    if (hal_i2c_read_string(SHT30_I2C_PORT, SHT30_I2C_BASE_ADDR, cmd, sizeof(cmd), data, sizeof(data)) != I2C_OK)
    {
        ESP_LOGE(TAG, "sht30 read data error");
        return I2C_FAIL;
    }

    // 摄氏度
    sht30->cTemp = ((((data[0] * 256.0) + data[1]) * 175) / 65535.0) - 45;
    // 华氏度
    sht30->fTemp = (sht30->cTemp * 1.8) + 32;
    // 十度
    sht30->humidity = ((((data[3] * 256.0) + data[4]) * 100) / 65535.0);

    return 0;
}

/**
 * @brief     write memory bytes
 * @param[in] *handle points to a mpu6050 handle structure
 * @param[in] addr is the memory address
 * @param[in] *buf points to a data buffer
 * @param[in] len is the data length
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 *            - 2 len is invalid
 * @note      none
 */
int sht30_device_init()
{
    hal_i2c_config_t hal_i2c_config;
    hal_i2c_config.mode = HAL_I2C_MODE_MASTER;
    hal_i2c_config.port = SHT30_I2C_PORT;
    hal_i2c_config.sda_pin = SHT30_I2C_SDA_PIN;
    hal_i2c_config.scl_pin = SHT30_I2C_SCL_PIN;
    hal_i2c_config.clk_speed = SHT30_I2C_CLK_SPEED;
    hal_i2c_config.tx_len = 0;
    hal_i2c_config.rx_len = 0;
    hal_i2c_config.timeout = 1000; // ms
    hal_i2c_config.callback = &(__sht30_callback);

    if (hal_i2c_init(hal_i2c_config) != I2C_OK)
    {
        ESP_LOGE(TAG, "i2c_init error");
        return I2C_FAIL;
    }

    uint8_t cmd[2];

    // 开启温度检测
    sht30_set_reg_addr(cmd, MEDIUM_2_CMD);
    if (hal_i2c_write_string(SHT30_I2C_PORT, SHT30_I2C_BASE_ADDR, cmd, sizeof(cmd)) != I2C_OK)
    {
        ESP_LOGE(TAG, "sht30 medium error");
        return I2C_FAIL;
    }
    vTaskDelay(pdMS_TO_TICKS(100));

    return I2C_OK;
}
