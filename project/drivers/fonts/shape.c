#include "shape.h"
#include <stdlib.h>


/*
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
*/


/*
        * * * * 
      *   *     * 
    *     *       *
    *     *       *
    *     * * *   *
    *             *
      *         * 
        * * * * 
*/
static uint8_t shape_clock[8][8] =
{
    {0,0,1,1,1,1,0,0},
    {0,1,2,1,2,2,1,0},
    {1,2,2,1,2,2,2,1},
    {1,2,2,1,2,2,2,1},
    {1,2,2,1,1,1,2,1},
    {1,2,2,2,2,2,2,1},
    {0,1,2,2,2,2,1,0},
    {0,0,1,1,1,1,0,0},
};

/*
        * * * * 
      *   *     * 
    *     *       *
    *     *       *
    *     * * *   *
    *             *
      *         * 
        * * * * 
*/
static uint8_t shape_degree[8][8] =
{
    {1,1,1,0,0,0,0,0},
    {1,1,1,0,0,0,0,0},
    {1,1,1,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
};

/*
         * * *
       *       *
     *     *     *
         *   *
           *
*/
static uint8_t shape_wifi[8][8] =
{
    {0,0,0,0,0,0,0,0},
    {0,0,1,1,1,0,0,0},
    {0,1,0,0,0,1,0,0},
    {1,0,0,1,0,0,1,0},
    {0,0,1,0,1,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,1,0,0,0,0},
    {0,0,0,0,0,0,0,0},
};
/*
           * 
         *   *
         *   *
         *   *
         *   *
       *       *
       *       *
         * * *
*/
static uint8_t shape_temp[8][8] = 
{
    {0,0,0,1,0,0,0,0},
    {0,0,1,2,1,0,0,0},
    {0,0,1,2,1,0,0,0},
    {0,0,1,2,1,0,0,0},
    {0,0,1,2,1,0,0,0},
    {0,1,2,2,2,1,0,0},
    {0,1,2,2,2,1,0,0},
    {0,0,1,1,1,0,0,0},
};

/*

         * * 
       * * * * * *
     * * * * * * * *
     * * * * * * * * 
     * * * * * * * *
       * * * * * *
*/

static uint8_t shape_cloudy[8][8] = 
{
    {0,0,0,0,0,0,0,0},
    {0,0,1,1,0,0,0,0},
    {0,1,1,1,1,1,0,0},
    {1,1,1,1,1,1,1,0},
    {1,1,1,1,1,1,1,0},
    {1,1,1,1,1,1,1,0},
    {0,1,1,1,1,1,0,0},
    {0,0,0,0,0,0,0,0},
};

/*
        *     * 
    
    *     * *     *
        * * * *   
    *     * *     *

        *     *  
*/

static uint8_t shape_sunny[8][8] = 
{
    {0,0,1,0,0,1,0,0},
    {0,0,0,0,0,0,0,0},
    {1,0,0,1,1,0,0,1},
    {0,0,1,1,1,1,0,0},
    {0,0,1,1,1,1,0,0},
    {1,0,0,1,1,0,0,1},
    {0,0,0,0,0,0,0,0},
    {0,0,1,0,0,1,0,0},
};

/*
          *
      *   *   *
        * * *
    * * *   * * * 
        * * *
      *   *   *
          *
          
*/
static uint8_t shape_snow[8][8] = 
{
    {0,0,0,1,0,0,0,0},
    {0,1,0,1,0,1,0,0},
    {0,0,1,1,1,0,0,0},
    {1,1,1,0,1,1,1,0},
    {0,0,1,1,1,0,0,0},
    {0,1,0,1,0,1,0,0},
    {0,0,0,1,0,0,0,0},
    {0,0,0,0,0,0,0,0},
};

int weather_shape_init(weather_shape_t *shape)
{
  shape[0].shape = (uint8_t *)&shape_sunny;
  shape[1].shape = (uint8_t *)&shape_cloudy;
  shape[2].shape = (uint8_t *)&shape_snow;

  return 0;
}

int shape_8x8_init(icon_shape_t *shape)
{
  shape[0].shape = (uint8_t *)&shape_clock;
  shape[1].shape = (uint8_t *)&shape_wifi;
  shape[2].shape = (uint8_t *)&shape_temp;
  shape[3].shape = (uint8_t *)&shape_degree;

  return 0;
}