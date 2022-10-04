#include "awtrix_weather.h"
#include <stdbool.h>
#include <string.h>
#include "awtrix.h"
#include "awtrix_api.h"
#include "fonts.h"
#include "shape.h"

#include "esp_http_client.h"
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

#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include "lwip/netdb.h"
#include "lwip/dns.h"

#include "esp_tls.h"
#include "esp_crt_bundle.h"

static const char *TAG = "awtrix_weather";

char *weather_post_buff = NULL;


// const char *weather_code[37] = {
//     "Sunny" /*晴（国内城市白天晴)*/, "Clear" /*晴（国内城市夜晚晴）*/, "Fair" /*晴（国外城市白天晴）*/,
//     "Cloudy" /*多云*/, "Partly Cloudy" /*晴间多云*/, "Mostly Cloudy" /*晴间多云*/,
//     "Overcast" /*阴*/, "Shower" /*阵雨*/, "Thundershower" /*雷阵雨*/,
//     "Thundershower with Hail" /*雷阵雨伴有冰雹*/, "Light Rain" /*小雨*/, "Moderate Rain" /*中雨*/,
//     "Heavy Rain" /*大雨*/, "Storm" /*暴雨*/, "Heavy Storm" /*大暴雨*/, "Severe Storm" /*特大暴雨*/,
//     "Ice Rain" /*冻雨*/, "Sleet" /*雨夹雪*/, "Snow Flurry" /*阵雪*/,
//     "Light Snow" /*小雪*/, "Moderate Snow" /*中雪*/, "Heavy Snow" /*大雪*/,
//     "Snowstorm" /*暴雪*/, "Dust" /*浮尘*/, "Sand" /*扬沙*/,
//     "Duststorm" /*沙尘暴*/, "Sandstorm" /*强沙尘暴*/, "Foggy" /*雾	Foggy*/,
//     "Haze" /*霾*/, "Windy" /*风*/, "Blustery" /*大风*/,
//     "Hurricane" /*飓风*/, "Tropical Storm" /*热带风暴*/, "Tornado" /*龙卷风*/,
//     "Cold" /*冷*/, "Hot" /*热	Hot*/, "Unknown" /*未知*/
// };

int awtrix_weather_init()
{
    int p = 0;
    weather_post_buff = malloc(sizeof(char) * 150);
    p += snprintf(weather_post_buff + p, 150, "http://%s%s", AWTRIX_WEATHER_SERVER_HOST, AWTRIX_WEATHER_SERVER_URL);
#if (AWTRIX_WEATHER_SERVICE_VENDOR == XINZHI_WEATHER)
    p += snprintf(weather_post_buff + p, 150, "/now.json?key=%s", AWTRIX_WEATHER_SERVER_KEY);
#elif (AWTRIX_WEATHER_SERVICE_VENDOR == HEFENG_WEATHER)
    p += snprintf(weather_post_buff + p, 150, "/now?key=%s", AWTRIX_WEATHER_SERVER_KEY);
#endif
    p += snprintf(weather_post_buff + p, 150, "&location=%s", AWTRIX_WEATHER_SERVER_CITY);
    p += snprintf(weather_post_buff + p, 150, "&language=%s", AWTRIX_WEATHER_SERVER_LANG);
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
        .method = HTTP_METHOD_GET,
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

    printf("%s\n", local_response_buffer);

    esp_http_client_cleanup(client); // 清除http client

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

    int code = atoi(now_code->valuestring);

    if ((code >= AWTRIX_WEATHER_MIN_SUNNY) && (code <= AWTRIX_WEATHER_MAX_SUNNY))
    {
        weather->type = WEATHER_SUN;
        weather->level = code - AWTRIX_WEATHER_MIN_SUNNY;
    }
    else if ((code >= AWTRIX_WEATHER_MIN_CLOUDY) && (code <= AWTRIX_WEATHER_MAX_CLOUDY))
    {
        weather->type = WEATHER_CLOUDY;
        weather->level = code - AWTRIX_WEATHER_MIN_CLOUDY;
    }
    else if ((code >= AWTRIX_WEATHER_MIN_RAIN) && (code <= AWTRIX_WEATHER_MAX_RAIN))
    {
        weather->type = WEATHER_RAIN;
        weather->level = code - AWTRIX_WEATHER_MIN_RAIN;
    }
    else if ((code >= AWTRIX_WEATHER_MIN_SNOW) && (code <= AWTRIX_WEATHER_MAX_SNOW))
    {
        weather->type = WEATHER_SNOW;
        weather->level = code - AWTRIX_WEATHER_MIN_SNOW;
    }
    else if ((code >= AWTRIX_WEATHER_MIN_DUST) && (code <= AWTRIX_WEATHER_MAX_DUST))
    {
        weather->type = WEATHER_DUST;
        weather->level = code - AWTRIX_WEATHER_MIN_DUST;
    }
    else if ((code >= AWTRIX_WEATHER_MIN_WINDY) && (code <= AWTRIX_WEATHER_MAX_WINDY))
    {
        weather->type = WEATHER_WINDY;
        weather->level = code - AWTRIX_WEATHER_MIN_WINDY;
    }
    else if ((code >= AWTRIX_WEATHER_MIN_CLOD) && (code <= AWTRIX_WEATHER_MAX_CLOD))
    {
        weather->type = WEATHER_COLD;
        weather->level = code - AWTRIX_WEATHER_MIN_CLOD;
    }
    else if ((code >= AWTRIX_WEATHER_MIN_HOT) && (code <= AWTRIX_WEATHER_MAX_HOT))
    {
        weather->type = WEATHER_HOT;
        weather->level = code - AWTRIX_WEATHER_MIN_HOT;
    }
    else if ((code >= AWTRIX_WEATHER_MIN_UNKONW) && (code <= AWTRIX_WEATHER_MAX_UNKONW))
    {
        weather->type = WEATHER_UNKONW;
        weather->level = code - AWTRIX_WEATHER_MIN_UNKONW;
    }
    else
    {
        weather->type = -1;
        weather->level = -1;
    }

    memset(weather->text, '\0', sizeof(weather->text));
    memcpy(weather->text, now_text->valuestring, strlen(now_text->valuestring));
    weather->temperature = atoi(now_temperature->valuestring);

    printf("weather->text: %s\n", weather->text);
    printf("weather->temperature: %d\n", weather->temperature);
    printf("weather->type: %d\n", weather->type);
    printf("weather->level: %d\n", weather->level);

    cJSON_Delete(root);

    // free(weather_post_buff);
    // weather_post_buff = NULL;
    
    return 0;
}

extern int awtrix_pixel_clear(pixel_u *pixel);
extern int awtrix_pixel_set_cursor(int x, int y);
extern int awtrix_pixel_add_weather(pixel_u *local_pixel, uint8_t index, uint8_t cover, uint8_t red, uint8_t green, uint8_t blue);
extern int awtrix_pixel_add_icon(pixel_u *local_pixel, uint8_t index, uint8_t cover, uint8_t red, uint8_t green, uint8_t blue);
extern int awtrix_pixel_add_char(pixel_u *local_pixel, uint8_t ch, uint8_t cover, uint8_t red, uint8_t green, uint8_t blue);

int awtrix_display_set_temp(pixel_u *pixel, weather_t *weather)
{
    if (weather == NULL)
        return -1;

    int temp_low = weather->temperature % 10;
    int temp_high = weather->temperature / 10;

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
    awtrix_pixel_add_char(pixel, '0', 1, 0x00, 0x00, 0x10);
    awtrix_pixel_set_cursor(25, 1);
    awtrix_pixel_add_char(pixel, '\'', 1, 0x00, 0x00, 0x10);

    return 0;
}
