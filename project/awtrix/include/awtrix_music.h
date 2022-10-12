#ifndef __AWTRIX_MUSIC_H__
#define __AWTRIX_MUSIC_H__
#include "awtrix.h"

#define SAMPLE_RATE (16000)
#define I2S_NUM (0)
#define WAVE_FREQ_HZ (100)
#define PI (3.14159265)
#define I2S_BCK_IO (GPIO_NUM_20)
#define I2S_WS_IO (GPIO_NUM_21)
#define I2S_DO_IO (-1)
#define I2S_DI_IO (GPIO_NUM_10)

#define N_SAMPLES 512
#define xres 32 // Total number of  columns in the display
#define yres 8  // Total number of  rows in the display

void awtrix_i2s_init();
int awtrix_music(pixel_u *local_pixel);

#endif