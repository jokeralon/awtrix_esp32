#include "awtrix_api.h"
#include "awtrix.h"
#include <stdbool.h>
#include <string.h>
#include "fonts.h"
#include "shape.h"
#include "sht30.h"

static const char *TAG = "awtrix_temp";

int awtrix_display_set_temp(pixel_u *pixel, sht30_value_t *sht30_temp)
{
    if (sht30_temp == NULL)
        return -1;

    int temp_low = (int)sht30_temp->cTemp % 10;
    int temp_high = (int)sht30_temp->cTemp / 10;
    int temp_point = (int)((sht30_temp->cTemp-(int)sht30_temp->cTemp)*10) % 10;

    awtrix_pixel_clear(pixel);
    awtrix_pixel_set_cursor(1, 0);
    awtrix_pixel_add_icon(pixel, 2, 1, 0x00, 0x00, 0x10);
    awtrix_pixel_set_cursor(11, 1);
    awtrix_pixel_add_char(pixel, temp_high+'0', 1, 0x00, 0x00, 0x10);
    awtrix_pixel_set_cursor(15, 1);
    awtrix_pixel_add_char(pixel, temp_low+'0', 1, 0x00, 0x00, 0x10);
    awtrix_pixel_set_cursor(18, 2);
    awtrix_pixel_add_char(pixel, '.', 0, 0x00, 0x00, 0x10);
    awtrix_pixel_set_cursor(21, 1);
    awtrix_pixel_add_char(pixel, temp_point+'0', 1, 0x00, 0x00, 0x10);
    awtrix_pixel_set_cursor(25, 1);
    awtrix_pixel_add_char(pixel, '\'', 1, 0x00, 0x00, 0x10);

    return 0;
}
