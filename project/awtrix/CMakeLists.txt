idf_component_register(SRCS "awtrix.c"
                            "awtrix_clock.c"
                            "awtrix_effect.c"
                    INCLUDE_DIRS "./include"
                    PRIV_REQUIRES "driver"
                    PRIV_REQUIRES "drivers"
                    )
