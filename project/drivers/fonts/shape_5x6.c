#include "shape.h"

static uint8_t shape_rabb[6][5] =
{
    {0,3,0,3,0},
    {2,3,2,3,2},
    {2,2,2,2,2},
    {1,1,1,1,1},
    {1,0,1,0,1},
    {1,1,1,1,1},
};

int shape_5x6_init(icon_shape_t *shape)
{
    shape[0].shape = (uint8_t *)&shape_rabb;

    return 0;
}