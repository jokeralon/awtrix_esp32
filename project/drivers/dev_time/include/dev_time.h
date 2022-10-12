#ifndef __DEV_TIME_H__
#define __DEV_TIME_H__

#include <time.h>

int dev_time_init();

int dev_time_get_timeinfo(struct tm * _tm);

#endif