#include "awtrix.h"
#include "awtrix_api.h"
#include <string.h>
#include "fonts.h"

static int awtrix_clock_num = 0;
static uint8_t awtrix_clock_bar_effect = 0x01;

int awtrix_map_set_clock(pixel_u *pixel, int hours, int minutes, int seconds)
{
    int hours_high = 0;
    int hours_low = 0;
    int minutes_high = 0;
    int minutes_low = 0;
    int seconds_high = 0;
    int seconds_low = 0;

    if ((hours > 24) || (hours < 0) || (minutes > 60) || (minutes < 0) || (seconds > 60) || (seconds < 0))
        return -1;

    if (AWTRIX_DISPLAY_CLOCK_HOURS_12 == 1)
        awtrix_clock_num++;
    else
        awtrix_clock_num = 0;

    if (awtrix_clock_num >= 35)
    {
        awtrix_clock_num = 0;
    }

    for (int i = 0; i < 7; i++)
    {
        if ((awtrix_clock_bar_effect >> i) & 0x01)
        {
            ESP_ERROR_CHECK(awtrix_pixel_add_char(pixel, 3, (2 + (i * 4)), '_', 1, 0x10, 0x00, 0x00));
        }
        else
        {
            ESP_ERROR_CHECK(awtrix_pixel_add_char(pixel, 3, (2 + (i * 4)), '_', 1, 0, 0x00, 0x00));
        }
    }

    awtrix_clock_bar_effect = awtrix_clock_bar_effect << 1;

    if (awtrix_clock_bar_effect & 0x80)
    {
        awtrix_clock_bar_effect = 0x01;
    }

    if (awtrix_clock_num < 30)
    {
        hours_high = hours / 10;
        hours_low = hours % 10;
        minutes_high = minutes / 10;
        minutes_low = minutes % 10;
        seconds_high = seconds / 10;
        seconds_low = seconds % 10;

        awtrix_pixel_add_char(pixel, 1, 2, (hours_high + '0'), 1, 0x10, 0x00, 0x00);
        awtrix_pixel_add_char(pixel, 1, 6, (hours_low + '0'), 1, 0x10, 0x00, 0x00);
        awtrix_pixel_add_char(pixel, 1, 9, ':', 0, 0x10, 0x00, 0x00);
        awtrix_pixel_add_char(pixel, 1, 12, (minutes_high + '0'), 1, 0x10, 0x00, 0x00);
        awtrix_pixel_add_char(pixel, 1, 16, (minutes_low + '0'), 1, 0x10, 0x00, 0x00);
        awtrix_pixel_add_char(pixel, 1, 19, ':', 0, 0x10, 0x00, 0x00);
        awtrix_pixel_add_char(pixel, 1, 22, (seconds_high + '0'), 1, 0x10, 0x00, 0x00);
        awtrix_pixel_add_char(pixel, 1, 26, (seconds_low + '0'), 1, 0x10, 0x00, 0x00);
    }
    else
    {

        hours_high = ((hours >= 12) ? ((hours - 12) / 10) : (hours / 10));
        hours_low = ((hours >= 12) ? ((hours - 12) % 10) : (hours % 10));
        minutes_high = minutes / 10;
        minutes_low = minutes % 10;
        seconds_high = seconds / 10;
        seconds_low = seconds % 10;

        awtrix_pixel_add_char(pixel, 1, 2, ((hours < 12) ? 'A' : 'P'), 1, 0x10, 0x00, 0x00);
        awtrix_pixel_add_char(pixel, 1, 6, 'M', 1, 0x10, 0x00, 0x00);
        awtrix_pixel_add_char(pixel, 1, 10, ' ', 1, 0x10, 0x00, 0x00);
        awtrix_pixel_add_char(pixel, 1, 12, (hours_high + '0'), 1, 0x10, 0x00, 0x00);
        awtrix_pixel_add_char(pixel, 1, 16, (hours_low + '0'), 1, 0x10, 0x00, 0x00);
        awtrix_pixel_add_char(pixel, 1, 19, ':', 0, 0x10, 0x00, 0x00);
        awtrix_pixel_add_char(pixel, 1, 22, (minutes_high + '0'), 1, 0x10, 0x00, 0x00);
        awtrix_pixel_add_char(pixel, 1, 26, (minutes_low + '0'), 1, 0x10, 0x00, 0x00);
    }

    return 0;
}

int awtrix_map_wifi_init(pixel_u *pixel)
{
    awtrix_pixel_add_string(pixel, 1, 2, "WIFI INIT\0", 1, 0x00, 0x00, 0x10);

    return 0;
}
