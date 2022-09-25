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

#include "esp_err.h"

#define NUMBER_FONT_START_X (2) // 字体偏移，左上角为原点
#define NUMBER_FONT_START_Y (1)
#define NUMBER_FONT_COL (5) // 数字字体行数
#define NUMBER_FONT_RAW (3) // 数字字体列数
#define AWTRIX_MAX_RAW (8) // 屏幕像素点行数
#define AWTRIX_MAX_COL (32)  // 屏幕像素点列数

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

void init_led();

void set_rgb(int led_num, uint16_t Red, uint16_t Green, uint16_t Blue);

int awtrix_init(void);

void awtrix_map_pixel_init();

pixel_u *awrtix_map_get_pixel(void);

int awtrix_map_set_clock(int hours, int minutes, int seconds);

int awtrix_map_wifi_init();

int awtrix_map_display_clear();


int awtrix_effect_scroll(pixel_u *pixel);

#ifdef __cplusplus
}
#endif
