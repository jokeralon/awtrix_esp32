#include "awtrix_weather.h"
#include "esp_http_client.h"
#include <stdbool.h>
#include "awtrix.h"
#include "awtrix_api.h"
#include "fonts.h"

#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "esp_event.h"
#include "esp_netif.h"
#include "esp_crt_bundle.h"
#include "esp_tls.h"
#include "esp_http_client.h"
#include "cJSON.h"

static const char *TAG = "awtrix_weather";

char *weather_post_buff = NULL;

int awtrix_weather_init()
{
    int p = 0;
    weather_post_buff = malloc(sizeof(char) * 150);
    p += snprintf(weather_post_buff + p, 150, "http://%s%s", AWTRIX_WEATHER_SERVER_HOST, AWTRIX_WEATHER_SERVER_URL);
    p += snprintf(weather_post_buff + p, 150, "/now.json?key=%s", AWTRIX_WEATHER_SERVER_PRI_KEY);
    p += snprintf(weather_post_buff + p, 150, "&location=%s", AWTRIX_WEATHER_SERVER_CITY);
    p += snprintf(weather_post_buff + p, 150, "&language=%s&unit=c", AWTRIX_WEATHER_SERVER_LANG);
    p += snprintf(weather_post_buff + p, 150, "&unit=%s", AWTRIX_WEATHER_SERVER_UNIT);
    p += snprintf(weather_post_buff + p, 150, "\0");

    ESP_LOGI(TAG, "post_buff: %s", weather_post_buff);

    return 0;
}

esp_err_t _http_event_handler(esp_http_client_event_t *evt)
{
    static char *output_buffer; // Buffer to store response of http request from event handler
    static int output_len;      // Stores number of bytes read
    switch (evt->event_id)
    {
    case HTTP_EVENT_ERROR:
        ESP_LOGI(TAG, "HTTP_EVENT_ERROR");
        break;
    case HTTP_EVENT_ON_CONNECTED:
        ESP_LOGI(TAG, "HTTP_EVENT_ON_CONNECTED");
        break;
    case HTTP_EVENT_HEADER_SENT:
        ESP_LOGI(TAG, "HTTP_EVENT_HEADER_SENT");
        break;
    case HTTP_EVENT_ON_HEADER:
        ESP_LOGI(TAG, "HTTP_EVENT_ON_HEADER, key=%s, value=%s", evt->header_key, evt->header_value);
        break;
    case HTTP_EVENT_ON_DATA:
        ESP_LOGI(TAG, "HTTP_EVENT_ON_DATA, len=%d", evt->data_len);
        /*
         *  Check for chunked encoding is added as the URL for chunked encoding used in this example returns binary data.
         *  However, event handler can also be used in case chunked encoding is used.
         */
        if (!esp_http_client_is_chunked_response(evt->client))
        {
            // If user_data buffer is configured, copy the response into the buffer
            if (evt->user_data)
            {
                memcpy(evt->user_data + output_len, evt->data, evt->data_len);
            }
            else
            {
                if (output_buffer == NULL)
                {
                    output_buffer = (char *)malloc(esp_http_client_get_content_length(evt->client));
                    output_len = 0;
                    if (output_buffer == NULL)
                    {
                        ESP_LOGE(TAG, "Failed to allocate memory for output buffer");
                        return ESP_FAIL;
                    }
                }
                memcpy(output_buffer + output_len, evt->data, evt->data_len);
            }
            output_len += evt->data_len;
        }

        break;
    case HTTP_EVENT_ON_FINISH:
        ESP_LOGI(TAG, "HTTP_EVENT_ON_FINISH");
        if (output_buffer != NULL)
        {
            // Response is accumulated in output_buffer. Uncomment the below line to print the accumulated response
            // ESP_LOG_BUFFER_HEX(TAG, output_buffer, output_len);
            free(output_buffer);
            output_buffer = NULL;
        }
        output_len = 0;
        break;
    case HTTP_EVENT_DISCONNECTED:
        ESP_LOGI(TAG, "HTTP_EVENT_DISCONNECTED");
        int mbedtls_err = 0;
        esp_err_t err = esp_tls_get_and_clear_last_error(evt->data, &mbedtls_err, NULL);
        if (err != 0)
        {
            if (output_buffer != NULL)
            {
                free(output_buffer);
                output_buffer = NULL;
            }
            output_len = 0;
            ESP_LOGI(TAG, "Last esp error code: 0x%x", err);
            ESP_LOGI(TAG, "Last mbedtls failure: 0x%x", mbedtls_err);
        }
        break;
    }
    return ESP_OK;
}

int awtrix_weather_get(weather_t *weather)
{
    if (weather == NULL)
        return -1;
    char local_response_buffer[256] = {0};
    esp_http_client_config_t config = {
        .url = weather_post_buff,
        .event_handler = _http_event_handler,
        .user_data = local_response_buffer, // Pass address of local buffer to get response
    };
    esp_http_client_handle_t client = esp_http_client_init(&config);

    // GET
    esp_err_t err = esp_http_client_perform(client);
    if (err == ESP_OK)
    {
        ESP_LOGI(TAG, "HTTP GET Status = %d, content_length = %d",
                 esp_http_client_get_status_code(client),
                 esp_http_client_get_content_length(client));
    }
    else
    {
        ESP_LOGE(TAG, "HTTP GET request failed: %s", esp_err_to_name(err));
        esp_http_client_cleanup(client);
        return -1;
    }

    cJSON *root = cJSON_Parse(local_response_buffer); //读取心知天气回调包
    if (root == NULL)
        return -1;
    cJSON *array = cJSON_GetObjectItem(root, "results"); //读取关键字
    if (array == NULL)
        return -1;
    cJSON *results0 = cJSON_GetArrayItem(array, 0); //判断位置
    if (results0 == NULL)
        return -1;
    cJSON *location = cJSON_GetObjectItem(results0, "location"); //读取关键字
    if (location == NULL)
        return -1;
    cJSON *now = cJSON_GetObjectItem(results0, "now"); //读取关键字
    if (now == NULL)
        return -1;
    cJSON *now_code = cJSON_GetObjectItem(now, "code");
    if (now_code == NULL)
        return -1;
    cJSON *now_text = cJSON_GetObjectItem(now, "text");
    if (now_text == NULL)
        return -1;
    cJSON *now_temperature = cJSON_GetObjectItem(now, "temperature");
    if (now_temperature == NULL)
        return -1;

    memset(weather->type, '\0', sizeof(weather->type));
    memcpy(weather->type, now_text->valuestring, strlen(now_text->valuestring));
    weather->temperature = atoi(now_temperature->valuestring);

    printf("weather->type: %s\n", weather->type);
    printf("weather->temperature: %d\n", weather->temperature);

    cJSON_Delete(root);

    return 0;
}
