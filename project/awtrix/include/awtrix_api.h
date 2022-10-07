#ifndef __AWTRIX_API_H__
#define __AWTRIX_API_H__
#include "awtrix.h"
#include "esp_log.h"
#include "fonts.h"

typedef int(*_showChar)(pixel_u *local_pixel, uint8_t ch, uint8_t cover, uint8_t red, uint8_t green, uint8_t blue);
typedef int(*_showString)(pixel_u *pixel, char *str, uint8_t cover, uint8_t red, uint8_t green, uint8_t blue);
typedef int(*_clear)(pixel_u *pixel);
typedef int(*_setCursor)(int x, int y);
typedef int(*_getCursor)(int *x, int *y);

typedef struct 
{
    _clear clear;
    _showChar showChar;
    _showString showString;
    _setCursor setCursor;
    _getCursor getCursor;
}awtrix_t;



awtrix_t awtrix_pixel_init(pixel_u *pixel);

int awtrix_pixel_set_cursor(int x, int y);

int awtrix_pixel_get_cursor(int *x, int *y);

int awtrix_pixel_add_weather(pixel_u *local_pixel, uint8_t index, uint8_t cover, uint8_t red, uint8_t green, uint8_t blue);

int awtrix_pixel_add_icon(pixel_u *local_pixel, uint8_t index, uint8_t cover, uint8_t red, uint8_t green, uint8_t blue);

int awtrix_pixel_add_char(pixel_u *local_pixel,  uint8_t ch, uint8_t cover, uint8_t red, uint8_t green, uint8_t blue);

int awtrix_pixel_add_string(pixel_u *pixel,  char *str, uint8_t cover, uint8_t red, uint8_t green, uint8_t blue);

int awtrix_pixel_clear(pixel_u *pixel);

int awtrix_pixel_send_data(pixel_u *pixel);

#endif