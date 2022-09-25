#include "awtrix.h"
#include "fonts.h"

int awtrix_effect_scroll(pixel_u *pixel)
{
    uint32_t temp = 0;
    for (int raw = 0; raw < AWTRIX_MAX_RAW; raw++)
    {
        temp = pixel[raw * AWTRIX_MAX_COL].rgb;

        for (int i = 0; i < AWTRIX_MAX_COL; i++)
        {
            if (i == (AWTRIX_MAX_COL - 1))
            {
                pixel[raw * AWTRIX_MAX_COL + i].rgb = temp;
            }
            else
            {
                pixel[raw * AWTRIX_MAX_COL + i].rgb = pixel[raw * AWTRIX_MAX_COL + i + 1].rgb;
            }
        }
    }

    return 0;
}