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

