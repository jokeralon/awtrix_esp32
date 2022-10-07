#include "awtrix.h"
#include <stdio.h>
#include <stdlib.h>
#include "driver/rmt.h"
#include "esp_system.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "wifi.h"
#include <time.h>
#include <sys/time.h>

#include "awtrix_api.h"
#include "awtrix_weather.h"
#include "ws2812.h"
#include <sntp.h>
#include "fft.h"
#include "adc.h"
#include "sht30.h"
#include "dev_time.h"

static const char *TAG = "awtrix";

// #define EXAMPLE_ESP_WIFI_SSID "pppppp"
// #define EXAMPLE_ESP_WIFI_PASS "11223344"
#define EXAMPLE_ESP_WIFI_SSID "ChinaNet-BVBi"
#define EXAMPLE_ESP_WIFI_PASS "e6s7tmuq"

#define SWTICH_KEY_PIN	(9)

int awtrix_status_flag = 0;

TaskHandle_t awtrix_display_handle = NULL;
TaskHandle_t awtrix_status_handle = NULL;
TaskHandle_t awtrix_update_handle = NULL;
TaskHandle_t awtrix_switch_handle = NULL;

static pixel_u pixel[AWTRIX_MAX_RAW][AWTRIX_MAX_COL];
static struct tm timeinfo;
static weather_t weather;
static sht30_value_t sht30;

awtrix_t awtrix;

void awtrix_display_task(void *pvParameters) //任务函数
{
	while (1)
	{
		awtrix_pixel_send_data((pixel_u *)&pixel);
		vTaskDelay(pdMS_TO_TICKS(100));
	}
	vTaskDelete(awtrix_display_handle);
	awtrix_display_handle = NULL;
}
void awtrix_status_task(void *pvParameters) //任务函数
{
	while (1)
	{
		switch (awtrix_status_flag)
		{
		case 0:
			awtrix_effect_scroll((pixel_u *)&pixel);
			vTaskDelay(pdMS_TO_TICKS(200));
			break;
		case 1:
			awtrix_display_set_clock((pixel_u *)&pixel, timeinfo);
			vTaskDelay(pdMS_TO_TICKS(1000));
			break;
		case 2:
			awtrix_display_set_temp((pixel_u *)&pixel, &weather);
			vTaskDelay(pdMS_TO_TICKS(1000));
			break;
		default:
			break;
		}
	}
}

void awtrix_update_task(void *pvParameters) //任务函数
{
	while (1)
	{
		dev_time_get_timeinfo(&timeinfo);
		if ((timeinfo.tm_hour == 0) && (timeinfo.tm_min == 0) && (timeinfo.tm_sec == 0))
		{
			struct timeval time;
			sntp_sync_time(&time);
			settimeofday(&time, NULL);
		}
		// 每5分钟更新天气信息
		if (((timeinfo.tm_min % 5) == 0) && (timeinfo.tm_sec == 0))
		{
			if (wifi_get_ip_flag() == 1)
				awtrix_weather_get(&weather);
		}
		// 每30s获取温湿度信息
		if ((timeinfo.tm_sec % 30 == 0))
		{
			sht30_get_temp(&sht30);
		}
		vTaskDelay(pdMS_TO_TICKS(1000));
	}

	vTaskDelete(awtrix_update_handle);
	awtrix_update_handle = NULL;
}

void awtrix_switch_task(void *pvParameters) //任务函数
{
	gpio_config_t io_conf = {};
	// interrupt of rising edge
	io_conf.intr_type = GPIO_INTR_POSEDGE;
	// bit mask of the pins, use GPIO4/5 here
	io_conf.pin_bit_mask = (1 << (SWTICH_KEY_PIN));
	// set as input mode
	io_conf.mode = GPIO_MODE_INPUT;
	// enable pull-up mode
	io_conf.pull_up_en = 1;
	gpio_config(&io_conf);

	while (1)
	{
		if (gpio_get_level(SWTICH_KEY_PIN) == 0)
		{
			vTaskDelay(pdMS_TO_TICKS(20));
			if (gpio_get_level(SWTICH_KEY_PIN) == 0)
			{
				ESP_LOGI(TAG, "key down");
				if (awtrix_status_flag == 1)
					awtrix_status_flag = 2;
				else
					awtrix_status_flag = 1;
			}
			while (gpio_get_level(SWTICH_KEY_PIN) == 0)
			{
				vTaskDelay(pdMS_TO_TICKS(10));
			}
		}

		vTaskDelay(pdMS_TO_TICKS(10));
	}

	vTaskDelete(awtrix_switch_handle);
	awtrix_switch_handle = NULL;
}

int awtrix_init(void)
{

	awtrix = awtrix_pixel_init((pixel_u *)&pixel);

	awtrix_display_set_wifi((pixel_u *)&pixel);

	if (awtrix_display_handle == NULL)
	{
		xTaskCreate(awtrix_display_task, "awtrix_display", 4096, NULL, 5, &awtrix_display_handle);
	}
	if (awtrix_status_handle == NULL)
	{
		xTaskCreate(awtrix_status_task, "awtrix_status", 4096, NULL, 5, &awtrix_status_handle);
	}
	if (awtrix_switch_handle == NULL)
	{
		xTaskCreate(awtrix_switch_task, "awtrix_switch", 4096, NULL, 5, &awtrix_switch_handle);
	}

	sht30_device_init();
	sht30_get_temp(&sht30);

	wifi_init_sta(EXAMPLE_ESP_WIFI_SSID, EXAMPLE_ESP_WIFI_PASS);

	dev_time_init();
	awtrix_weather_init();
	awtrix_weather_get(&weather);

	awtrix_pixel_clear((pixel_u *)&pixel);

	awtrix_status_flag = 1;

	if (awtrix_update_handle == NULL)
	{
		xTaskCreate(awtrix_update_task, "awtrix_update", 4096, NULL, 5, &awtrix_update_handle);
	}

	return 0;
}
