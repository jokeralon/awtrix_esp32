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

#define XINZHI_WEATHER         0
#define HEFENG_WEATHER         1

#define AWTRIX_WEATHER_SERVICE_VENDOR   XINZHI_WEATHER

#if (AWTRIX_WEATHER_SERVICE_VENDOR == XINZHI_WEATHER)
#define AWTRIX_WEATHER_SERVER_HOST      "api.seniverse.com"
#define AWTRIX_WEATHER_SERVER_URL       "/v3/weather"
#define AWTRIX_WEATHER_SERVER_KEY       "S95aobioJH_vZfDlB"
#define AWTRIX_WEATHER_SERVER_CITY      "tianjin"
#define AWTRIX_WEATHER_SERVER_LANG      "en"//"zh-Hans"
#define AWTRIX_WEATHER_SERVER_UNIT      "c"
#elif (AWTRIX_WEATHER_SERVICE_VENDOR == HEFENG_WEATHER)
#define AWTRIX_WEATHER_SERVER_HOST      "devapi.qweather.com"
#define AWTRIX_WEATHER_SERVER_URL       "/v7/weather"
#define AWTRIX_WEATHER_SERVER_KEY   "94f0039e742d4341a7bd3a560815b315"
#define AWTRIX_WEATHER_SERVER_CITY      "101031500" // 天津市 南开区
#define AWTRIX_WEATHER_SERVER_LANG      "en"//"zh-Hans"
#define AWTRIX_WEATHER_SERVER_UNIT      "c"
#endif

#define AWTRIX_WEATHER_MIN_SUNNY        0
#define AWTRIX_WEATHER_MAX_SUNNY        3

#define AWTRIX_WEATHER_MIN_CLOUDY       4
#define AWTRIX_WEATHER_MAX_CLOUDY       9

#define AWTRIX_WEATHER_MIN_RAIN         10
#define AWTRIX_WEATHER_MAX_RAIN         19

#define AWTRIX_WEATHER_MIN_SNOW         20
#define AWTRIX_WEATHER_MAX_SNOW         25

#define AWTRIX_WEATHER_MIN_DUST         26
#define AWTRIX_WEATHER_MAX_DUST         29

#define AWTRIX_WEATHER_MIN_WINDY        30
#define AWTRIX_WEATHER_MAX_WINDY        36

#define AWTRIX_WEATHER_MIN_CLOD         37
#define AWTRIX_WEATHER_MAX_CLOD         37

#define AWTRIX_WEATHER_MIN_HOT          38
#define AWTRIX_WEATHER_MAX_HOT          38

#define AWTRIX_WEATHER_MIN_UNKONW           39
#define AWTRIX_WEATHER_MAX_UNKONW           39


enum awtrix_weather_type
{
    WEATHER_SUN = 0,
    WEATHER_CLOUDY,
    WEATHER_RAIN,
    WEATHER_SNOW,
    WEATHER_DUST,
    WEATHER_WINDY,
    WEATHER_COLD,
    WEATHER_HOT,
    WEATHER_UNKONW,
};



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
    char text[20];      // 天气类型
    int temperature;    // 温度
    int type;
    int level;
}weather_t;


void init_led();

int	awtrix_init();

void set_rgb(int led_num, uint16_t Red, uint16_t Green, uint16_t Blue);

int awtrix_display_set_clock(pixel_u *pixel, int hours, int minutes, int seconds);

int awtrix_effect_scroll(pixel_u *pixel);

int awtrix_display_set_wifi(pixel_u *pixel);


int awtrix_weather_init();

int awtrix_weather_get(weather_t * weather);

int awtrix_display_set_temp(pixel_u *pixel, weather_t *weather);

#ifdef __cplusplus
}
#endif
