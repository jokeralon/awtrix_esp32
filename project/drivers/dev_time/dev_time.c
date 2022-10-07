#include "dev_time.h"
#include <time.h>
#include <esp_err.h>
#include <esp_log.h>

const static char *TAG = "dev_time";

time_t now;
struct tm timeinfo;

int dev_time_init()
{
    time(&now);
    localtime_r(&now, &timeinfo);

    char strftime_buf[64];

    // Set timezone to China Standard Time
    setenv("TZ", "CST-8", 1);
    tzset();
    localtime_r(&now, &timeinfo);
    strftime(strftime_buf, sizeof(strftime_buf), "%c", &timeinfo);
    ESP_LOGI(TAG, "The current date/time in Shanghai is: %s", strftime_buf);

    return ESP_OK;
}

int dev_time_get_timeinfo(struct tm * _tm)
{
    time(&now);
    localtime_r(&now, &timeinfo);

    *_tm = timeinfo;
    
    return ESP_OK;
}
