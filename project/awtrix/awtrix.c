#include "awtrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "driver/rmt.h"
#include "esp_system.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "wifi.h"
#include "esp_sntp.h"
#include <time.h>
#include <sys/time.h>

#include "driver/adc.h"
#include "driver/i2s.h"
#include "esp_adc_cal.h"

#include "awtrix_api.h"
#include "awtrix_weather.h"
#include "awtrix_music.h"
#include "ws2812.h"
#include "arduinoFFT.h"
#include "adc.h"

static const char *TAG = "awtrix";

// #define EXAMPLE_ESP_WIFI_SSID "pppppp"
// #define EXAMPLE_ESP_WIFI_PASS "11223344"
#define EXAMPLE_ESP_WIFI_SSID "ChinaNet-BVBi"
#define EXAMPLE_ESP_WIFI_PASS "e6s7tmuq"

#define RMT_TX_NUM 2				 //发送口
#define RMT_TX_CHANNEL RMT_CHANNEL_0 //发送频道
#define LED_STRIP_NUM 257			 //灯珠数量

static led_strip_t *strip;

int awtrix_status_flag = 0;

TaskHandle_t awtrix_display_handle = NULL;
TaskHandle_t awtrix_status_handle = NULL;
TaskHandle_t awtrix_weather_handle = NULL;

time_t now;
struct tm timeinfo;

static pixel_u pixel[AWTRIX_MAX_RAW][AWTRIX_MAX_COL];
static weather_t weather;

awtrix_t awtrix;

void init_led()
{
	rmt_config_t config = RMT_DEFAULT_CONFIG_TX(RMT_TX_NUM, RMT_TX_CHANNEL);
	// set counter clock to 40MHz
	config.clk_div = 2;
	ESP_ERROR_CHECK(rmt_config(&config));
	ESP_ERROR_CHECK(rmt_driver_install(config.channel, 0, 0));

	// install ws2812 driver
	led_strip_config_t strip_config = LED_STRIP_DEFAULT_CONFIG(LED_STRIP_NUM, (led_strip_dev_t)config.channel);
	strip = led_strip_new_rmt_ws2812(&strip_config);
	if (!strip)
	{
		ESP_LOGE(TAG, "install WS2812 driver failed");
	}
	// Clear LED strip (turn off all LEDs)
	ESP_ERROR_CHECK(strip->clear(strip, 100));
}

void set_rgb(int led_num, uint16_t Red, uint16_t Green, uint16_t Blue)
{
	for (int i = 0; i < led_num; i++)
	{
		strip->set_pixel(strip, i, Red, Green, Blue); //设置颜色
	}
	strip->refresh(strip, LED_STRIP_NUM);
}

void awtrix_display_task(void *pvParameters) //任务函数
{
	while (1)
	{
		if (pixel == NULL)
			continue;

		uint8_t flag = 0;
		int num = 0;

		for (int i = 0; i < 32; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (!flag)
				{
					if (pixel[j][i].rgb > 0)
					{
						strip->set_pixel(strip, num, pixel[j][i].r, pixel[j][i].g, pixel[j][i].b);
					}
					else
					{
						strip->set_pixel(strip, num, 0, 0, 0);
					}
				}
				else
				{
					if (pixel[AWTRIX_MAX_RAW - j - 1][i].rgb > 0)
					{
						strip->set_pixel(strip, num, pixel[AWTRIX_MAX_RAW - j - 1][i].r, pixel[AWTRIX_MAX_RAW - j - 1][i].g, pixel[AWTRIX_MAX_RAW - j - 1][i].b);
					}
					else
					{
						strip->set_pixel(strip, num, 0, 0, 0);
					}
				}
				num++;
			}
			flag = ~flag;
		}
		strip->refresh(strip, num);
		vTaskDelay(pdMS_TO_TICKS(100));
	}
	vTaskDelete(awtrix_display_handle);
	awtrix_display_handle = NULL;
}
void awtrix_status_task(void *pvParameters) //任务函数
{
	while (1)
	{
		time(&now);
		localtime_r(&now, &timeinfo);

		switch (awtrix_status_flag)
		{
		case 0:
			awtrix_effect_scroll((pixel_u *)&pixel);
			vTaskDelay(pdMS_TO_TICKS(200));
			break;
		case 1:
			awtrix_display_set_clock((pixel_u *)&pixel, timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);
			if ((timeinfo.tm_hour == 0) && (timeinfo.tm_min == 0) && (timeinfo.tm_sec == 0))
			{
				struct timeval time;
				sntp_sync_time(&time);
				settimeofday(&time, NULL);
			}
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

void awtrix_weather_task(void *pvParameters) //任务函数
{
	while (1)
	{
		awtrix_weather_get(&weather);
		vTaskDelay(pdMS_TO_TICKS(10 * 60 * 1000));
	}
}


int awtrix_init(void)
{
	init_led();

	awtrix = awtrix_pixel_init((pixel_u *)&pixel);

	awtrix_weather_init();

	awtrix_display_set_wifi((pixel_u *)&pixel);

	awtrix_i2s_init();

	if (awtrix_display_handle == NULL)
	{
		xTaskCreate(awtrix_display_task, "awtrix_display", 4096, NULL, 5, &awtrix_display_handle);
	}

	esp_err_t ret;
	ESP_LOGI(TAG, "Start Example.");

	while (1)
	{
		awtrix_music((pixel_u *)&pixel);
	}
	

	

	if (awtrix_status_handle == NULL)
	{
		xTaskCreate(awtrix_status_task, "awtrix_status", 4096, NULL, 5, &awtrix_status_handle);
	}

	time(&now);
	localtime_r(&now, &timeinfo);
	if (timeinfo.tm_year < (2016 - 1900))
	{
		ESP_LOGI(TAG, "Time is not set yet. Connecting to WiFi and getting time over NTP.");
		wifi_init_sta(EXAMPLE_ESP_WIFI_SSID, EXAMPLE_ESP_WIFI_PASS);

		// update 'now' variable with current time
		time(&now);
	}

	char strftime_buf[64];

	// Set timezone to Eastern Standard Time and print local time
	setenv("TZ", "EST5EDT,M3.2.0/2,M11.1.0", 1);
	tzset();
	localtime_r(&now, &timeinfo);
	strftime(strftime_buf, sizeof(strftime_buf), "%c", &timeinfo);
	ESP_LOGI(TAG, "The current date/time in New York is: %s", strftime_buf);

	// Set timezone to China Standard Time
	setenv("TZ", "CST-8", 1);
	tzset();
	localtime_r(&now, &timeinfo);
	strftime(strftime_buf, sizeof(strftime_buf), "%c", &timeinfo);
	ESP_LOGI(TAG, "The current date/time in Shanghai is: %s", strftime_buf);

	if (awtrix_weather_handle == NULL)
	{
		xTaskCreate(awtrix_weather_task, "awtrix_weather", 4096, NULL, 5, &awtrix_weather_handle);
	}

	awtrix_status_flag = 2;

	awtrix.clear((pixel_u *)&pixel);

	return 0;
}
