#ifndef __WIFI__
#define __WIFI__

#include "esp_err.h"

esp_err_t wifi_init_sta(const char *ssid, const char *passwd);

int wifi_get_ip_flag();

int wifi_wait_for_connect();

#endif