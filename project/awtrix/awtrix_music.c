#include "awtrix.h"
#include "awtrix_music.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "driver/rmt.h"
#include "esp_system.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "wifi.h"
#include "esp_sntp.h"
#include <time.h>
#include <sys/time.h>

#include "driver/adc.h"
#include "driver/i2s.h"
#include "esp_adc_cal.h"

#include "awtrix_api.h"
#include "awtrix_weather.h"
#include "ws2812.h"
#include "arduinoFFT.h"
#include "adc.h"




int32_t sample[N_SAMPLES];
int16_t freq_offset[16] = {0, 1, 2, 3, 4, 5, 8, 11, 17, 25, 30, 41, 44, 87, 175, 711};

double vReal[N_SAMPLES]; // 实部 FFT采样输入样本数组
double vImag[N_SAMPLES]; // 虚部 FFT运算输出数组
double fft_bin[N_SAMPLES];
double fft_data[32];
int fft_result[32];
uint8_t sens = 16;
int freq_gain2[xres] = {30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30};
double fft_freq_boost[32] = {1.02, 1.03, 1.04, 1.06, 1.08, 1.10, 1.10, 1.11, 1.12, 1.13, 1.15, 1.16, 1.17, 1.18, 1.20, 1.21, 1.30, 1.51, 2.11, 2.22, 3.25, 3.26, 3.52, 3.55, 4.22, 4.24, 5.52, 5.55, 6.53, 6.55, 8.82, 8.88};
int gain = 41;            // adjust it to set the gain
int Intensity[xres] = {}; // initialize Frequency Intensity to zero
unsigned long lastTime = 0;

uint8_t bar_height[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
uint8_t peak_height[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
uint8_t prev_fft_value[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};


void awtrix_i2s_init()
{
    i2s_config_t i2s_config = {
        .mode = (I2S_MODE_MASTER | I2S_MODE_RX),
        .sample_rate = 16000,
        .bits_per_sample = I2S_BITS_PER_SAMPLE_32BIT,
        .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
        .communication_format = (I2S_COMM_FORMAT_I2S | I2S_COMM_FORMAT_I2S_MSB), // I2S_COMM_FORMAT_STAND_I2S,
        .tx_desc_auto_clear = false,
        .dma_buf_count = 4,
        .dma_buf_len = 8};

    i2s_pin_config_t pin_config = {
        .mck_io_num = I2S_PIN_NO_CHANGE, .bck_io_num = I2S_BCK_IO, .ws_io_num = I2S_WS_IO, .data_out_num = I2S_DO_IO,
        .data_in_num = I2S_DI_IO // Not used
    };
    i2s_driver_install(I2S_NUM, &i2s_config, 0, NULL);
    i2s_set_pin(I2S_NUM, &pin_config);
}


uint32_t hsv2rgb(uint16_t hue, uint8_t saturation, uint8_t value)
{
    uint8_t red = 0;
    uint8_t green = 0;
    uint8_t blue = 0;
    uint16_t hi = (hue / 60) % 6;
    uint16_t F = 100 * hue / 60 - 100 * hi;
    uint16_t P = value * (100 - saturation) / 100;
    uint16_t Q = value * (10000 - F * saturation) / 10000;
    uint16_t T = value * (10000 - saturation * (100 - F)) / 10000;

    switch (hi)
    {
    case 0:
        red = value;
        green = T;
        blue = P;
        break;
    case 1:
        red = Q;
        green = value;
        blue = P;
        break;
    case 2:
        red = P;
        green = value;
        blue = T;
        break;
    case 3:
        red = P;
        green = Q;
        blue = value;
        break;
    case 4:
        red = T;
        green = P;
        blue = value;
        break;
    case 5:
        red = value;
        green = P;
        blue = Q;
        break;
    default:
        return 0;
    }
    red = red * 255 / 100;
    green = green * 255 / 100;
    blue = blue * 255 / 100;

    return (((uint32_t)blue << 16) | (uint32_t)(green << 8) | (uint32_t)(red));
}

int awtrix_music(pixel_u *local_pixel)
{

    pixel_u *pixel[AWTRIX_MAX_RAW];

    for (int i = 0; i < AWTRIX_MAX_RAW; i++)
        pixel[i] = &local_pixel[i * AWTRIX_MAX_COL];

    size_t i2s_bytes_read;
    i2s_read(I2S_NUM_0, (char *)&sample, sizeof(int32_t) * N_SAMPLES, &i2s_bytes_read, portMAX_DELAY); // no timeout
    if ((i2s_bytes_read > 0) && (i2s_bytes_read = N_SAMPLES * 4))
    {

        for (int i = 0; i < N_SAMPLES; i++)
        {
            sample[i] = abs(sample[i] >> sens);
            vReal[i] = sample[i];
            vImag[i] = 0;
        }

        bool reduce = false;
        unsigned long millis = (unsigned long)(esp_timer_get_time() / 1000ULL);
        if ((millis - lastTime) > 25)
        {
            lastTime = millis;
            reduce = true;
        }
        // fft
        fft_windowing(vReal, 1, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
        fft_compute(vReal, vImag, N_SAMPLES, FFT_FORWARD);
        fft_complexToMagnitude(vReal, vImag, N_SAMPLES);
        // Update Intensity Array

        for (int i = 0; i < N_SAMPLES; i++)
        {
            double t = 0.0;
            t = abs(vReal[i]);
            t = t / 32.0;
            fft_bin[i] = t;
        }

        fft_data[0] = (fft_add(3, 4, fft_bin)) / 2;       // 60-100Hz
        fft_data[1] = (fft_add(4, 5, fft_bin)) / 2;       // 80-120Hz
        fft_data[2] = (fft_add(5, 6, fft_bin)) / 2;       // 100-140Hz
        fft_data[3] = (fft_add(6, 7, fft_bin)) / 2;       // 120-160Hz
        fft_data[4] = (fft_add(7, 8, fft_bin)) / 2;       // 140-180Hz
        fft_data[5] = (fft_add(8, 9, fft_bin)) / 2;       // 160-200Hz
        fft_data[6] = (fft_add(9, 10, fft_bin)) / 2;      // 180-220Hz
        fft_data[7] = (fft_add(10, 11, fft_bin)) / 2;     // 200-240Hz
        fft_data[8] = (fft_add(11, 12, fft_bin)) / 2;     // 220-260Hz
        fft_data[9] = (fft_add(12, 13, fft_bin)) / 2;     // 240-280Hz
        fft_data[10] = (fft_add(13, 14, fft_bin)) / 2;    // 260-300Hz
        fft_data[11] = (fft_add(14, 16, fft_bin)) / 3;    // 280-340Hz
        fft_data[12] = (fft_add(16, 18, fft_bin)) / 3;    // 320-380Hz
        fft_data[13] = (fft_add(18, 20, fft_bin)) / 3;    // 360-420Hz
        fft_data[14] = (fft_add(20, 24, fft_bin)) / 5;    // 400-500Hz
        fft_data[15] = (fft_add(24, 28, fft_bin)) / 5;    // 480-580Hz
        fft_data[16] = (fft_add(28, 32, fft_bin)) / 5;    // 560-660Hz
        fft_data[17] = (fft_add(32, 36, fft_bin)) / 5;    // 640-740Hz
        fft_data[18] = (fft_add(36, 42, fft_bin)) / 7;    // 720-860Hz
        fft_data[19] = (fft_add(42, 48, fft_bin)) / 7;    // 840-980Hz
        fft_data[20] = (fft_add(48, 56, fft_bin)) / 9;    // 960-1140Hz
        fft_data[21] = (fft_add(56, 64, fft_bin)) / 9;    // 1120-1300Hz
        fft_data[22] = (fft_add(64, 74, fft_bin)) / 11;   // 1280-1500Hz
        fft_data[23] = (fft_add(74, 84, fft_bin)) / 11;   // 1480-1700Hz
        fft_data[24] = (fft_add(84, 97, fft_bin)) / 14;   // 1680-1960Hz
        fft_data[25] = (fft_add(97, 110, fft_bin)) / 14;  // 1940-2240Hz
        fft_data[26] = (fft_add(110, 128, fft_bin)) / 19; // 2200-2580Hz
        fft_data[27] = (fft_add(128, 146, fft_bin)) / 19; // 2560-2940Hz
        fft_data[28] = (fft_add(146, 170, fft_bin)) / 25; // 2920-3420Hz
        fft_data[29] = (fft_add(170, 194, fft_bin)) / 25; // 3400-3900Hz
        fft_data[30] = (fft_add(194, 224, fft_bin)) / 31; // 3880-4500Hz
        fft_data[31] = (fft_add(224, 255, fft_bin)) / 32; // 4520-5120Hz

        // adjust single frequency curves.
        for (int i = 0; i < 32; i++)
        {
            fft_data[i] = fft_data[i] * fft_freq_boost[i];
        }

        // adjust overall frequency curves.
        for (int i = 0; i < 32; i++)
        {
            fft_data[i] = fft_data[i] * gain / 50;
        }

        // constraint function
        for (int i = 0; i < 32; i++)
        {
            fft_result[i] = constrain((int)fft_data[i], 0, 255);
        }

        for (int i = 0; i < 32; i = i + 1)
        {
            uint8_t fft_value;
            fft_value = fft_result[i];
            fft_value = ((prev_fft_value[i] * 3) + fft_value) / 4;
            bar_height[i] = fft_value / (255 / (8 - 1)); // scale bar height
            if (bar_height[i] > peak_height[i])          // peak up
                peak_height[i] = ((8 - 1) > ((int)bar_height[i]) ? (int)bar_height[i] : (8 - 1));
            prev_fft_value[i] = fft_value;
        }

        // int t = 16;
        // for (int i = t; i < (xres * Displacement) + t; i += Displacement)
        // {
        // 	vReal[i] = constrain(vReal[i], 0, 3596);									 // set max value for input data
        // 	vReal[i] = map(vReal[i], freq_gain2[(i - t) / Displacement], 1848, 0, yres); // map data to fit our display
        // 	if (reduce)
        // 	{
        // 		Intensity[(i - t) / Displacement]--; // Decrease displayed value
        // 	}
        // 	if (vReal[i] > Intensity[(i - t) / Displacement]) // Match displayed value to measured value
        // 		Intensity[(i - t) / Displacement] = vReal[i];
        // }

        int color = 0;
        for (int i = 0; i < 32; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if ((j <= bar_height[i]))
                    pixel[7 - j][i].rgb = hsv2rgb(color, 100, 10);
                else
                    pixel[7 - j][i].rgb = 0;
            }
            color += 360 / 32;
        }
        // printf("%d ", fft_result[i]);
        // printf("\r\n");
    }

    return 0;
}
