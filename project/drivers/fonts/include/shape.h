#ifndef __SHAPE_H
#define __SHAPE_H

#include <stdio.h>
#include <stdlib.h>

#define SHAPE_MAX_RAW   5
#define SHAPE_MAX_COL   5

typedef struct 
{
    uint8_t *shape; 
}icon_shape_t;

typedef struct 
{
    uint8_t *shape; 
}weather_shape_t;

int weather_shape_init(weather_shape_t *shape);

int icon_shape_init(icon_shape_t *shape);

#endif