#include <stdio.h>
#include <stdlib.h>
#include "awtrix.h"
#include "driver/rmt.h"
#include "ws2812.h"
#include "esp_system.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "wifi.h"

#include <time.h>
#include <sys/time.h>

static const char *TAG = "awtrix";

#define EXAMPLE_ESP_WIFI_SSID "pppppp"
#define EXAMPLE_ESP_WIFI_PASS "11223344"
// #define EXAMPLE_ESP_WIFI_SSID "ChinaNet-BVBi"
// #define EXAMPLE_ESP_WIFI_PASS "e6s7tmuq"

#define RMT_TX_NUM 8				 //发送口
#define RMT_TX_CHANNEL RMT_CHANNEL_0 //发送频道
#define LED_STRIP_NUM 257			 //灯珠数量

static led_strip_t *strip;

int awtrix_status_flag = 0;

TaskHandle_t awtrix_display_handle = NULL;
TaskHandle_t awtrix_status_handle = NULL;

time_t now;
struct tm timeinfo;
pixel_u *pixel = NULL;

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

void awtrix_display(void *pvParameters) //任务函数
{
	while (1)
	{

		pixel = awrtix_map_get_pixel();

		if (pixel == NULL)
			break;

		uint8_t flag = 0;
		int num = 0;

		printf("\n");

		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 32; j++)
			{
				if (pixel[(i * 32) + j].rgb > 0)
				{
					strip->set_pixel(strip, num, pixel[(j * 32) + i].r, pixel[(j * 32) + i].g, pixel[(j * 32) + i].b);
					printf("* ");
				}
				else
				{
					strip->set_pixel(strip, num, 0, 0, 0);
					printf("  ");
				}
			}
			printf("\n");
		}

		for (int i = 0; i < 32; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (!flag)
				{
					if (pixel[(j * 32) + i].rgb > 0)
					{
						strip->set_pixel(strip, num, pixel[(j * 32) + i].r, pixel[(j * 32) + i].g, pixel[(j * 32) + i].b);
					}
					else
					{
						strip->set_pixel(strip, num, 0, 0, 0);
					}
				}
				else
				{
					if (pixel[(7 - j) * 32 + i].rgb > 0)
					{
						strip->set_pixel(strip, num, pixel[(7 - j) * 32 + i].r, pixel[(7 - j) * 32 + i].g, pixel[(7 - j) * 32 + i].b);
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
		vTaskDelay(pdMS_TO_TICKS(500));
	}
	vTaskDelete(awtrix_display_handle);
	awtrix_display_handle = NULL;
}
void awtrix_status(void *pvParameters) //任务函数
{
	while (1)
	{
		switch (awtrix_status_flag)
		{
		case 0:
			awtrix_effect_scroll(pixel);
			vTaskDelay(pdMS_TO_TICKS(100));
			break;
		case 1:
			time(&now);
			localtime_r(&now, &timeinfo);
			awtrix_map_set_clock(timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);
			vTaskDelay(pdMS_TO_TICKS(1000));
			break;
		case 2:
			
			break;
		default:
			break;
		}
	}
}

int awtrix_init(void)
{
	init_led();

	awtrix_map_pixel_init();

	awtrix_map_wifi_init();

	if (awtrix_display_handle == NULL)
	{
		xTaskCreate(awtrix_display, "awtrix_display", 4096, NULL, 5, NULL);
	}
	if (awtrix_status_handle == NULL)
	{
		xTaskCreate(awtrix_status, "awtrix_status", 4096, NULL, 5, NULL);
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

	awtrix_status_flag = 1;

	awtrix_map_display_clear();

	return 0;
}
