#ifndef __SHAPE_H
#define __SHAPE_H

#include <stdio.h>
#include <stdlib.h>

#define SHAPE_MAX_RAW   5
#define SHAPE_MAX_COL   5
#define SHAPE_8x8_RAW   8
#define SHAPE_8x8_COL   8
#define SHAPE_5x6_RAW   6
#define SHAPE_5x6_COL   5

#define SHAPE_8x8_COLOR_1   0x001000
#define SHAPE_8x8_COLOR_2   0x100000
#define SHAPE_8x8_COLOR_3   0x000010

#define SHAPE_5x6_COLOR_1   0x100000
#define SHAPE_5x6_COLOR_2   0x001000
#define SHAPE_5x6_COLOR_3   0x000010

typedef struct 
{
    uint8_t *shape; 
}icon_shape_t;

typedef struct 
{
    uint8_t *shape; 
}weather_shape_t;

int weather_shape_init(weather_shape_t *shape);

int shape_8x8_init(icon_shape_t *shape);
int shape_5x6_init(icon_shape_t *shape);

#endif