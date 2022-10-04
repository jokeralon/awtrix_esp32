#include "awtrix.h"
#include "awtrix_api.h"
#include "shape.h"

// static uint8_t awtrix_point_map[AWTRIX_MAX_RAW][AWTRIX_MAX_COL] = {
//     {0, 15, 16, 31, 32, 47, 48, 63, 64, 79, 80, 95, 96, 111, 112, 127, 128, 143, 144, 159, 160, 175, 176, 191, 192, 207, 208, 223, 224, 239, 240, 255},
//     {1, 14, 17, 30, 33, 46, 49, 62, 65, 78, 81, 94, 97, 110, 113, 126, 129, 142, 145, 158, 161, 174, 177, 190, 193, 206, 209, 222, 225, 238, 241, 254},
//     {2, 13, 18, 29, 34, 45, 50, 61, 66, 77, 82, 93, 98, 109, 114, 125, 130, 141, 146, 157, 162, 173, 178, 189, 194, 205, 210, 221, 226, 237, 242, 253},
//     {3, 12, 19, 28, 35, 44, 51, 60, 67, 76, 83, 92, 99, 108, 115, 124, 131, 140, 147, 156, 163, 172, 179, 188, 195, 204, 211, 220, 227, 236, 243, 252},
//     {4, 11, 20, 27, 36, 43, 52, 59, 68, 75, 84, 91, 100, 107, 116, 123, 132, 139, 148, 155, 164, 171, 180, 187, 196, 203, 212, 219, 228, 235, 244, 251},
//     {5, 10, 21, 26, 37, 42, 53, 58, 69, 74, 85, 90, 101, 106, 117, 122, 133, 138, 149, 154, 165, 170, 181, 186, 197, 202, 213, 218, 229, 234, 245, 250},
//     {6, 9, 22, 25, 38, 41, 54, 57, 70, 73, 86, 89, 102, 105, 118, 121, 134, 137, 150, 153, 166, 169, 182, 185, 198, 201, 214, 217, 230, 233, 246, 249},
//     {7, 8, 23, 24, 39, 40, 55, 56, 71, 72, 87, 88, 103, 104, 119, 120, 135, 136, 151, 152, 167, 168, 183, 184, 199, 200, 215, 216, 231, 232, 247, 248},
// };

static int awtrix_pixel_cursor_x = 0;
static int awtrix_pixel_cursor_y = 0;

ascii_5_3_font_t ascii_font[FONTS_ASCII_5_3_NUMBER];
weather_shape_t weather_shape[8];
icon_shape_t icon_shape[8];
awtrix_t awtrix_api;

int awtrix_pixel_set_cursor(int x, int y)
{
    if ((x < 0) || (x >= AWTRIX_MAX_COL) || (y < 0) || (y >= AWTRIX_MAX_RAW))
        return -1;
    awtrix_pixel_cursor_x = x;
    awtrix_pixel_cursor_y = y;

    return 0;
}
int awtrix_pixel_get_cursor(int *x, int *y)
{
    if ((x == NULL) || (y == NULL))
        return -1;
    *x = awtrix_pixel_cursor_x;
    *y = awtrix_pixel_cursor_y;

    return 0;
}

awtrix_t awtrix_pixel_init(pixel_u *pixel)
{
    fonts_ascii_5_3_init(ascii_font);
    weather_shape_init(weather_shape);
    icon_shape_init(icon_shape);

    for (int i = 0; i < AWTRIX_MAX_RAW; i++)
    {
        for (int j = 0; j < AWTRIX_MAX_COL; j++)
        {
            pixel[i * AWTRIX_MAX_COL + j].rgb = 0;
        }
    }

    awtrix_api.clear = &awtrix_pixel_clear;
    awtrix_api.getCursor = &awtrix_pixel_get_cursor;
    awtrix_api.setCursor = &awtrix_pixel_set_cursor;
    awtrix_api.showChar = &awtrix_pixel_add_char;
    awtrix_api.showString = &awtrix_pixel_add_string;

    return awtrix_api;
}

int awtrix_pixel_add_weather(pixel_u *local_pixel, uint8_t index, uint8_t cover, uint8_t red, uint8_t green, uint8_t blue)
{

    pixel_u *pixel[AWTRIX_MAX_RAW];

    for (int i = 0; i < AWTRIX_MAX_RAW; i++)
        pixel[i] = &local_pixel[i * AWTRIX_MAX_COL];

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (weather_shape[index].shape[i * 8 + j] == 1)
            {
                pixel[i + awtrix_pixel_cursor_y][j + awtrix_pixel_cursor_x].r = red;
                pixel[i + awtrix_pixel_cursor_y][j + awtrix_pixel_cursor_x].g = green;
                pixel[i + awtrix_pixel_cursor_y][j + awtrix_pixel_cursor_x].b = blue;
            }
            else
            {
                if (cover == 1)
                {
                    pixel[i + awtrix_pixel_cursor_y][j + awtrix_pixel_cursor_x].rgb = 0;
                }
            }
        }
    }
    awtrix_pixel_cursor_x += 4;
    return 0;
}


int awtrix_pixel_add_icon(pixel_u *local_pixel, uint8_t index, uint8_t cover, uint8_t red, uint8_t green, uint8_t blue)
{

    pixel_u *pixel[AWTRIX_MAX_RAW];

    for (int i = 0; i < AWTRIX_MAX_RAW; i++)
        pixel[i] = &local_pixel[i * AWTRIX_MAX_COL];

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (icon_shape[index].shape[i * 8 + j] == 1)
            {
                pixel[i + awtrix_pixel_cursor_y][j + awtrix_pixel_cursor_x].r = red;
                pixel[i + awtrix_pixel_cursor_y][j + awtrix_pixel_cursor_x].g = green;
                pixel[i + awtrix_pixel_cursor_y][j + awtrix_pixel_cursor_x].b = blue;
            }
            else if(icon_shape[index].shape[i * 8 + j] == 2)
            {
                pixel[i + awtrix_pixel_cursor_y][j + awtrix_pixel_cursor_x].r = green;
                pixel[i + awtrix_pixel_cursor_y][j + awtrix_pixel_cursor_x].g = blue;
                pixel[i + awtrix_pixel_cursor_y][j + awtrix_pixel_cursor_x].b = red;
            }
            else
            {
                if (cover == 1)
                {
                    pixel[i + awtrix_pixel_cursor_y][j + awtrix_pixel_cursor_x].rgb = 0;
                }
            }
        }
    }
    awtrix_pixel_cursor_x += 4;
    return 0;
}

int awtrix_pixel_add_char(pixel_u *local_pixel, uint8_t ch, uint8_t cover, uint8_t red, uint8_t green, uint8_t blue)
{

    pixel_u *pixel[AWTRIX_MAX_RAW];

    for (int i = 0; i < AWTRIX_MAX_RAW; i++)
        pixel[i] = &local_pixel[i * AWTRIX_MAX_COL];

    if ((ch < ' ') || (ch > '`'))
        return -1;

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (ascii_font[ch - ' '].font[i * 3 + j] == 1)
            {
                pixel[i + awtrix_pixel_cursor_y][j + awtrix_pixel_cursor_x].r = red;
                pixel[i + awtrix_pixel_cursor_y][j + awtrix_pixel_cursor_x].g = green;
                pixel[i + awtrix_pixel_cursor_y][j + awtrix_pixel_cursor_x].b = blue;
            }
            else
            {
                if (cover == 1)
                {
                    pixel[i + awtrix_pixel_cursor_y][j + awtrix_pixel_cursor_x].rgb = 0;
                }
            }
        }
    }
    awtrix_pixel_cursor_x += 4;
    return 0;
}

int awtrix_pixel_add_string(pixel_u *pixel, char *str, uint8_t cover, uint8_t red, uint8_t green, uint8_t blue)
{
    int ret = -1;
    for (int i = 0; i < strlen(str); i++)
    {
        ret = awtrix_pixel_add_char(pixel, str[i], cover, red, green, blue);
        if (ret != 0)
            return ret;
    }
    return 0;
}

int awtrix_pixel_clear(pixel_u *pixel)
{
    for (int i = 0; i < AWTRIX_MAX_RAW; i++)
    {
        for (int j = 0; j < AWTRIX_MAX_COL; j++)
        {
            pixel[i * AWTRIX_MAX_COL + j].rgb = 0;
        }
    }
    return 0;
}
