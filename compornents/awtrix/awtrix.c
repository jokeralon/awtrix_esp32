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

static const char *TAG = "awtrix";

#define RMT_TX_NUM 8				 //发送口
#define RMT_TX_CHANNEL RMT_CHANNEL_0 //发送频道
#define LED_STRIP_NUM 257			 //灯珠数量

typedef union
{
	struct __attribute__((packed))
	{
		uint8_t b;
		uint8_t g;
		uint8_t r;
	};
	uint32_t rgb;
} awtrix_color_t;

typedef struct
{
	uint32_t id;
	awtrix_color_t rgb;
	struct awtrix_map_t *next;
} awtrix_map_t;

static led_strip_t *strip;

awtrix_map_t *awtrix_map_head = NULL;
int awtrix_map_id = 0;

static void awtrix_map_add(awtrix_map_t **head, awtrix_map_t *map)
{
	awtrix_map_t *temp = NULL;

	if (NULL == *head)
	{
		*head = map;
		(*head)->next = NULL;
	}
	else
	{
		temp = *head;
		while (temp)
		{
			if (NULL == temp->next)
			{
				temp->next = map;
				map->next = NULL;
			}
			temp = temp->next;
		}
	}
}
static void awtrix_map_print(awtrix_map_t **head)
{
	awtrix_map_t *temp;
	temp = *head;
	printf("map information: \n");
	while (temp)
	{
		printf("\tmap[%d]:%x (r:%x, g:%x, b:%x)\n", temp->id, temp->rgb.rgb, temp->rgb.r, temp->rgb.g, temp->rgb.b);
		temp = temp->next;
	}
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

void awtrix_display(uint8_t *map)
{
	uint8_t flag = 0;
	int num = 0;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 32; j++)
		{
			printf("%d, ", map[i * 32 + j]);
		}
		printf("\n");
	}
	for (int i = 0; i < 32; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (!flag)
			{
				if (map[(j*32)+i] == 1)
				{
					// printf("num:%d\n",num);
					strip->set_pixel(strip, num, 0, 0, 0x10);
				}
			}
			else
			{
				if (map[(7-j)*32+i] == 1)
				{
					// printf("num:%d\n",num);
					strip->set_pixel(strip, num, 0, 0, 0x10);
				}
			}
			num++;
		}
		flag = ~flag;
	}
	strip->refresh(strip, num);
}

int awtrix_init(void)
{

	init_led();
	/* This helper function configures Wi-Fi or Ethernet, as selected in menuconfig.
	 * Read "Establishing Wi-Fi or Ethernet Connection" section in
	 * examples/protocols/README.md for more information about this function.
	 */

	awtrix_map_t *awtrix_map = malloc(sizeof(awtrix_map_t) * LED_STRIP_NUM);
	if (NULL == awtrix_map)
	{
		printf("malloc error!");
		return -1;
	}

	for (int i = 0; i < LED_STRIP_NUM; i++)
	{
		awtrix_map[i].id = awtrix_map_id++;
		awtrix_map[i].rgb.rgb = i;

		awtrix_map_add(&awtrix_map_head, &awtrix_map[i]);
	}

	/* 遍历链表，把链表中每个元素的信息都打印出来 */
	awtrix_map_print(&awtrix_map_head);

	uint8_t *map = NULL;
	map = awtrix_map_add_number(0, 0);
	map = awtrix_map_add_number(1, 1);
	map = awtrix_map_add_number(2, 2);
	map = awtrix_map_add_number(3, 3);
	map = awtrix_map_add_number(4, 4);
	map = awtrix_map_add_number(5, 5);
	map = awtrix_map_add_number(6, 6);
	map = awtrix_map_add_number(7, 7);

	// for (int i = 0; i < LED_STRIP_NUM; i++)
	// {
	// 	set_rgb(i, 0, 0, 0x10);
	// 	vTaskDelay(pdMS_TO_TICKS(10));
	// }
	// for (int i = 0; i < LED_STRIP_NUM; i++)
	// {
	// 	set_rgb(i, 0, 0, 0);
	// 	vTaskDelay(pdMS_TO_TICKS(10));
	// }
	vTaskDelay(pdMS_TO_TICKS(1000));

	awtrix_display(map);
	while (1)
	{
		vTaskDelay(pdMS_TO_TICKS(1000));
	}

	return 0;
}
