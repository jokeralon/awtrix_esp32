#include "sht30.h"
#include "esp_err.h"
#include "esp_log.h"
#include "hal_i2c.h"

const static char *TAG = "sth30";

static void sht30_set_reg_addr(uint8_t *buf, sht30_reg_add_t reg_add)
{
    buf[0] = (uint8_t)(reg_add >> 8);
    buf[1] = (uint8_t)(reg_add);
}
sht30_value_t sht30;
int sht30_get_temp(sht30_value_t *sht30)
{

    if (sht30 == NULL)
        return ESP_FAIL;

    uint8_t cmd[2];
    uint8_t data[6];

    sht30_set_reg_addr(cmd, READOUT_FOR_PERIODIC_MODE);

    if (hal_i2c_read_string(SHT30_I2C_PORT, SHT30_I2C_BASE_ADDR, cmd, sizeof(cmd), data, sizeof(data)) != ESP_OK)
    {
        ESP_LOGE(TAG, "sht30 read data error");
        return ESP_FAIL;
    }

    sht30->cTemp = ((((data[0] * 256.0) + data[1]) * 175) / 65535.0) - 45;
    sht30->fTemp = (sht30->cTemp * 1.8) + 32;
    sht30->humidity = ((((data[3] * 256.0) + data[4]) * 100) / 65535.0);

    // printf("相对湿度：");
    // printf("%f", humidity);
    // printf(" %RH\n");
    // printf("摄氏度温度：");
    // printf("%f", cTemp);
    // printf(" C\n");
    // printf("华氏度温度：");
    // printf("%f", fTemp);
    // printf(" F\n");

    return 0;
}

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

    if (hal_i2c_init(hal_i2c_config) != ESP_OK)
    {
        ESP_LOGE(TAG, "i2c_init error");
        return ESP_FAIL;
    }

    uint8_t cmd[2];

    // 开启温度检测
    sht30_set_reg_addr(cmd, MEDIUM_2_CMD);
    if (hal_i2c_write_string(SHT30_I2C_PORT, SHT30_I2C_BASE_ADDR, cmd, sizeof(cmd)) != ESP_OK)
    {
        ESP_LOGE(TAG, "sht30 medium error");
        return ESP_FAIL;
    }
    vTaskDelay(pdMS_TO_TICKS(100));

    return ESP_OK;
}
