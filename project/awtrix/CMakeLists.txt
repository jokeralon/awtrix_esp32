idf_component_register(SRCS "awtrix_clock.c"
                            "awtrix_effect.c"
                            "awtrix_api.c"
                            "awtrix_weather.c"
                            "awtrix.c"
                            
                        INCLUDE_DIRS "./include"
                        PRIV_REQUIRES "driver"
                                  "drivers"
                                nvs_flash
                                esp_http_client
                                esp_http_server
                                mbedtls
                                esp-tls
                                json
                                esp_adc_cal
                    )
