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
#include "esp_dsp.h"

#include "awtrix_api.h"
#include "awtrix_weather.h"
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

long map(long x, long in_min, long in_max, long out_min, long out_max)
{
	const long run = in_max - in_min;
	if (run == 0)
	{
		ESP_LOGE(TAG, "map(): Invalid input range, min == max");
		return -1; // AVR returns -1, SAM returns 0
	}
	const long rise = out_max - out_min;
	const long delta = x - in_min;
	return (delta * rise) / run + out_min;
}



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

#define SAMPLE_RATE (16000)
#define I2S_NUM (0)
#define WAVE_FREQ_HZ (100)
#define PI (3.14159265)
#define I2S_BCK_IO (GPIO_NUM_20)
#define I2S_WS_IO (GPIO_NUM_21)
#define I2S_DO_IO (-1)
#define I2S_DI_IO (GPIO_NUM_10)

void awtrix_i2s_init()
{
	i2s_config_t i2s_config = {
		.mode = (I2S_MODE_MASTER | I2S_MODE_RX),
		.sample_rate = 16000,
		.bits_per_sample = I2S_BITS_PER_SAMPLE_32BIT,
		.channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
		.communication_format = (I2S_COMM_FORMAT_I2S | I2S_COMM_FORMAT_I2S_MSB), // I2S_COMM_FORMAT_STAND_I2S,
		.tx_desc_auto_clear = false,
		.dma_buf_count = 4,
		.dma_buf_len = 8};

	i2s_pin_config_t pin_config = {
		.mck_io_num = I2S_PIN_NO_CHANGE, .bck_io_num = I2S_BCK_IO, .ws_io_num = I2S_WS_IO, .data_out_num = I2S_DO_IO,
		.data_in_num = I2S_DI_IO // Not used
	};
	i2s_driver_install(I2S_NUM, &i2s_config, 0, NULL);
	i2s_set_pin(I2S_NUM, &pin_config);
}

#define N_SAMPLES 512
#define xres 32 // Total number of  columns in the display
#define yres 8	// Total number of  rows in the display

int Displacement = 1; // Create LED Object

int N = N_SAMPLES;
int32_t sample[N_SAMPLES];
float y_cf[N_SAMPLES];
float sum_y[N_SAMPLES];
int16_t freq_offset[16] = {0, 1, 2, 3, 4, 5, 8, 11, 17, 25, 30, 41, 44, 87, 175, 711};
float tempraw[18];

double vReal[N_SAMPLES]; // 实部 FFT采样输入样本数组
double vImag[N_SAMPLES]; // 虚部 FFT运算输出数组
double fft_bin[N_SAMPLES];
double fft_data[32];
int fft_result[32];
uint8_t sens = 16;
int freq_gain2[xres] = {30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30};
double fft_freq_boost[32] = {1.02,1.03,1.04,1.06,1.08,1.10,1.10,1.11,1.12,1.13,1.15,1.16,1.17,1.18,1.20,1.21,1.30,1.51,2.11,2.22,3.25,3.26,3.52,3.55,4.22,4.24,5.52,5.55,6.53,6.55,8.82,8.88};
int gain = 30;			  // adjust it to set the gain
int Intensity[xres] = {}; // initialize Frequency Intensity to zero
unsigned long lastTime = 0;
int fft_value_old[32];

uint8_t bar_height[]  = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
uint8_t peak_height[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
uint8_t prev_fft_value[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

double fft_add(int from, int to)
{
	int i = from;
	double result = 0;
	while (i <= to)
	{
		result += fft_bin[i++];
	}
	return result;
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
		size_t i2s_bytes_read;
		i2s_read(I2S_NUM_0, (char *)&sample, sizeof(int32_t) * N_SAMPLES, &i2s_bytes_read, portMAX_DELAY); // no timeout
		if ((i2s_bytes_read > 0) && (i2s_bytes_read = N_SAMPLES * 4))
		{

			for (int i = 0; i < N_SAMPLES; i++)
			{
				sample[i] = abs(sample[i] >> sens);
				vReal[i] = sample[i];
				vImag[i] = 0;
			}

			bool reduce = false;
			unsigned long millis = (unsigned long)(esp_timer_get_time() / 1000ULL);
			if ((millis - lastTime) > 25)
			{
				lastTime = millis;
				reduce = true;
			}
			// fft
			fft_windowing(vReal, 1, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
			fft_compute(vReal, vImag, N_SAMPLES, FFT_FORWARD);
			fft_complexToMagnitude(vReal, vImag, N_SAMPLES);
			// Update Intensity Array

			for (int i = 0; i < N_SAMPLES; i++)
			{
				double t = 0.0;
				t = abs(vReal[i]);
				t = t / 32.0;
				fft_bin[i] = t;
			}

			fft_data[0] = (fft_add(3, 4)) / 2;		 // 60-100Hz
			fft_data[1] = (fft_add(4, 5)) / 2;		 // 80-120Hz
			fft_data[2] = (fft_add(5, 6)) / 2;		 // 100-140Hz
			fft_data[3] = (fft_add(6, 7)) / 2;		 // 120-160Hz
			fft_data[4] = (fft_add(7, 8)) / 2;		 // 140-180Hz
			fft_data[5] = (fft_add(8, 9)) / 2;		 // 160-200Hz
			fft_data[6] = (fft_add(9, 10)) / 2;		 // 180-220Hz
			fft_data[7] = (fft_add(10, 11)) / 2;	 // 200-240Hz
			fft_data[8] = (fft_add(11, 12)) / 2;	 // 220-260Hz
			fft_data[9] = (fft_add(12, 13)) / 2;	 // 240-280Hz
			fft_data[10] = (fft_add(13, 14)) / 2;	 // 260-300Hz
			fft_data[11] = (fft_add(14, 16)) / 3;	 // 280-340Hz
			fft_data[12] = (fft_add(16, 18)) / 3;	 // 320-380Hz
			fft_data[13] = (fft_add(18, 20)) / 3;	 // 360-420Hz
			fft_data[14] = (fft_add(20, 24)) / 5;	 // 400-500Hz
			fft_data[15] = (fft_add(24, 28)) / 5;	 // 480-580Hz
			fft_data[16] = (fft_add(28, 32)) / 5;	 // 560-660Hz
			fft_data[17] = (fft_add(32, 36)) / 5;	 // 640-740Hz
			fft_data[18] = (fft_add(36, 42)) / 7;	 // 720-860Hz
			fft_data[19] = (fft_add(42, 48)) / 7;	 // 840-980Hz
			fft_data[20] = (fft_add(48, 56)) / 9;	 // 960-1140Hz
			fft_data[21] = (fft_add(56, 64)) / 9;	 // 1120-1300Hz
			fft_data[22] = (fft_add(64, 74)) / 11;	 // 1280-1500Hz
			fft_data[23] = (fft_add(74, 84)) / 11;	 // 1480-1700Hz
			fft_data[24] = (fft_add(84, 97)) / 14;	 // 1680-1960Hz
			fft_data[25] = (fft_add(97, 110)) / 14;	 // 1940-2240Hz
			fft_data[26] = (fft_add(110, 128)) / 19; // 2200-2580Hz
			fft_data[27] = (fft_add(128, 146)) / 19; // 2560-2940Hz
			fft_data[28] = (fft_add(146, 170)) / 25; // 2920-3420Hz
			fft_data[29] = (fft_add(170, 194)) / 25; // 3400-3900Hz
			fft_data[30] = (fft_add(194, 224)) / 31; // 3880-4500Hz
			fft_data[31] = (fft_add(224, 255)) / 32; // 4520-5120Hz

			// adjust single frequency curves.
			for (int i = 0; i < 32; i++)
			{
				fft_data[i] = fft_data[i] * fft_freq_boost[i];
			}

			// adjust overall frequency curves.
			for (int i = 0; i < 32; i++)
			{
				fft_data[i] = fft_data[i] * gain / 50;
			}

			// constraint function
			for (int i = 0; i < 32; i++)
			{
				fft_result[i] = constrain((int)fft_data[i], 0, 255);
			}

			for (int i = 0; i < 32; i = i + 1)
			{
				uint8_t fft_value;
				fft_value = fft_result[i];
				fft_value = ((prev_fft_value[i] * 3) + fft_value) / 4;
				bar_height[i] = fft_value / (255 / (8 - 1)); // scale bar height
				if (bar_height[i] > peak_height[i])						 // peak up
					peak_height[i] = ((8-1) > ((int)bar_height[i]) ? (int)bar_height[i] : (8-1));
				prev_fft_value[i] = fft_value;
			}

			// int t = 16;
			// for (int i = t; i < (xres * Displacement) + t; i += Displacement)
			// {
			// 	vReal[i] = constrain(vReal[i], 0, 3596);									 // set max value for input data
			// 	vReal[i] = map(vReal[i], freq_gain2[(i - t) / Displacement], 1848, 0, yres); // map data to fit our display
			// 	if (reduce)
			// 	{
			// 		Intensity[(i - t) / Displacement]--; // Decrease displayed value
			// 	}
			// 	if (vReal[i] > Intensity[(i - t) / Displacement]) // Match displayed value to measured value
			// 		Intensity[(i - t) / Displacement] = vReal[i];
			// }
			for (int i = 0; i < 32; i++)
			{
				for (int j = 0; j < 8; j++)
				{
					if ((j <= bar_height[i]))
						pixel[7 - j][i].g = 0x10;
					else
						pixel[7 - j][i].rgb = 0;
				}
			}
			// printf("%d ", fft_result[i]);
			// printf("\r\n");
		}
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
