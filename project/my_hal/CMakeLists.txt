idf_component_register(SRCS "adc/adc.c"
                            "i2c/hal_i2c.c"
                    INCLUDE_DIRS "adc/include"
                                 "i2c/include"
                    PRIV_REQUIRES "driver"
                                  "esp_adc_cal"
                    )
