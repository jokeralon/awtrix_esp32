#ifndef __ADC__
#define __ADC__

typedef enum
{
    HAL_ADC_EVENT_INIT  = 0,
    HAL_ADC_EVENT_INIT_ERROR,
    HAL_ADC_EVENT_TIMEOUT,
    HAL_ADC_EVENT_DEINIT,
}hal_adc_event_e;

typedef void(*hal_adc_callback_t)(hal_adc_event_e, void *);

typedef struct 
{
    int channel;

    hal_i2c_callback_t callback;
}hal_i2c_config_t;


int adc_init();
uint32_t adc_get_raw(void);

#endif 