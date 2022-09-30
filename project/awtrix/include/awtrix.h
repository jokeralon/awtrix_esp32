// Copyright 2019 Espressif Systems (Shanghai) PTE LTD
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "esp_err.h"

#define NUMBER_FONT_START_X (2) // 字体偏移，左上角为原点
#define NUMBER_FONT_START_Y (1)
#define NUMBER_FONT_COL (5) // 数字字体行数
#define NUMBER_FONT_RAW (3) // 数字字体列数
#define AWTRIX_MAX_RAW (8) // 屏幕像素点行数
#define AWTRIX_MAX_COL (32)  // 屏幕像素点列数


#define AWTRIX_WEATHER_SERVER_HOST      "api.seniverse.com"
#define AWTRIX_WEATHER_SERVER_URL       "/v3/weather"
#define AWTRIX_WEATHER_SERVER_PUB_KEY   "P5KX8Xuo9Uaf6NbAY"
#define AWTRIX_WEATHER_SERVER_PRI_KEY   "S95aobioJH_vZfDlB"
#define AWTRIX_WEATHER_SERVER_CITY      "tianjin"
#define AWTRIX_WEATHER_SERVER_LANG      "en"//"zh-Hans"
#define AWTRIX_WEATHER_SERVER_UNIT      "c"


#define AWTRIX_DISPLAY_CLOCK_HOURS_12   1   // 12小时制

enum
{   
    AWTRIX_DISPLAY_TYPE_CLOCK = 0,
    AWTRIX_DISPLAY_TYPE_WEATHER,
};

typedef union{
    struct{
        uint8_t b;
        uint8_t g;
        uint8_t r;
    };
    uint32_t rgb;
}pixel_u;


typedef struct 
{
    char type[10];      // 天气类型
    int temperature;    // 温度
}weather_t;


void init_led();

int	awtrix_init();

void set_rgb(int led_num, uint16_t Red, uint16_t Green, uint16_t Blue);

int awtrix_map_set_clock(pixel_u *pixel, int hours, int minutes, int seconds);

int awtrix_effect_scroll(pixel_u *pixel);

int awtrix_map_wifi_init(pixel_u *pixel);



void awtrix_pixel_init(pixel_u *pixel);

int awtrix_pixel_add_char(pixel_u *local_pixel, int raw, int col, uint8_t ch, uint8_t cover, uint8_t red, uint8_t green, uint8_t blue);

int awtrix_pixel_add_string(pixel_u *pixel, int raw, int col, char *str, uint8_t cover, uint8_t red, uint8_t green, uint8_t blue);

int awtrix_pixel_clear(pixel_u *pixel);

int awtrix_weather_init();




int awtrix_weather_init();

int awtrix_weather_get(weather_t * weather);



#ifdef __cplusplus
}
#endif
