#include "awtrix.h"




#define NUMBER_FONT_START_X         (1)         // 字体偏移，左上角为原点
#define NUMBER_FONT_START_Y         (1)     
#define NUMBER_FONT_COL             (5)         // 数字字体行数
#define NUMBER_FONT_RAW             (3)         // 数字字体列数
#define AWTRIX_MAX_COL              (8)         // 屏幕像素点行数
#define AWTRIX_MAX_RAW              (32)        // 屏幕像素点列数
static uint8_t map[AWTRIX_MAX_COL][AWTRIX_MAX_RAW] = {0};
static uint8_t awtrix_point_map[AWTRIX_MAX_COL][AWTRIX_MAX_RAW] = {
    {0, 15, 16, 31, 32, 47, 48, 63, 64, 79, 80, 95, 96, 111, 112, 127, 128, 143, 144, 159, 160, 175, 176, 191, 192, 207, 208, 223, 224, 239, 240, 255}, 
    {1, 14, 17, 30, 33, 46, 49, 62, 65, 78, 81, 94, 97, 110, 113, 126, 129, 142, 145, 158, 161, 174, 177, 190, 193, 206, 209, 222, 225, 238, 241, 254}, 
    {2, 13, 18, 29, 34, 45, 50, 61, 66, 77, 82, 93, 98, 109, 114, 125, 130, 141, 146, 157, 162, 173, 178, 189, 194, 205, 210, 221, 226, 237, 242, 253 }, 
    {3, 12, 19, 28, 35, 44, 51, 60, 67, 76, 83, 92, 99, 108, 115, 124, 131, 140, 147, 156, 163, 172, 179, 188, 195, 204, 211, 220, 227, 236, 243, 252 },  
    {4, 11, 20, 27, 36, 43, 52, 59, 68, 75, 84, 91, 100, 107, 116, 123, 132, 139, 148, 155, 164, 171, 180, 187, 196, 203, 212, 219, 228, 235, 244, 251}, 
    {5, 10, 21, 26, 37, 42, 53, 58, 69, 74, 85, 90, 101, 106, 117, 122, 133, 138, 149, 154, 165, 170, 181, 186, 197, 202, 213, 218, 229, 234, 245, 250}, 
    {6, 9, 22, 25, 38, 41, 54, 57, 70, 73, 86, 89, 102, 105, 118, 121, 134, 137, 150, 153, 166, 169, 182, 185, 198, 201, 214, 217, 230, 233, 246, 249 },  
    {7, 8, 23, 24, 39, 40, 55, 56, 71, 72, 87, 88, 103, 104, 119, 120, 135, 136, 151, 152, 167, 168, 183, 184, 199, 200, 215, 216, 231, 232, 247, 248 },
};
uint8_t font_0[5][3] = 
{
    {1, 1, 1},
    {1, 0, 1}, 
    {1, 0, 1}, 
    {1, 0, 1},
    {1, 1, 1},
};
uint8_t font_1[5][3] = 
{
    {0, 1, 0},
    {1, 1, 0}, 
    {0, 1, 0}, 
    {0, 1, 0},
    {1, 1, 1},
};
uint8_t font_2[5][3] = 
{
    {1, 1, 1},
    {0, 0, 1}, 
    {1, 1, 1}, 
    {1, 0, 0},
    {1, 1, 1},
};
uint8_t font_3[5][3] = 
{
    {1, 1, 1},
    {0, 0, 1}, 
    {1, 1, 1}, 
    {0, 0, 1},
    {1, 1, 1},
};
uint8_t font_4[5][3] = 
{
    {1, 0, 1},
    {1, 0, 1}, 
    {1, 1, 1}, 
    {0, 0, 1},
    {0, 0, 1},
};
uint8_t font_5[5][3] = 
{
    {1, 1, 1},
    {1, 0, 0}, 
    {1, 1, 1}, 
    {0, 0, 1},
    {1, 1, 1},
};
uint8_t font_6[5][3] = 
{
    {1, 1, 1},
    {1, 0, 0}, 
    {1, 1, 1}, 
    {1, 0, 1},
    {1, 1, 1},
};
uint8_t font_7[5][3] = 
{
    {1, 1, 1},
    {0, 0, 1}, 
    {0, 0, 1}, 
    {0, 0, 1},
    {0, 0, 1},
};
uint8_t font_8[5][3] = 
{
    {1, 1, 1},
    {1, 0, 1}, 
    {1, 1, 1}, 
    {1, 0, 1},
    {1, 1, 1},
};
uint8_t font_9[5][3] = 
{
    {1, 1, 1},
    {1, 0, 1}, 
    {1, 1, 1}, 
    {0, 0, 1},
    {1, 1, 1},
};

struct awtrix_number_s
{
    uint8_t *font;
};

typedef struct awtrix_number_s awtrix_number_t;

awtrix_number_t awtrix_number[10];


uint8_t *awtrix_map_add_number(int position, int number)
{

    awtrix_number[0].font = &font_0;
    awtrix_number[1].font = &font_1;
    awtrix_number[2].font = &font_2;
    awtrix_number[3].font = &font_3;
    awtrix_number[4].font = &font_4;
    awtrix_number[5].font = &font_5;
    awtrix_number[6].font = &font_6;
    awtrix_number[7].font = &font_7;
    awtrix_number[8].font = &font_8;
    awtrix_number[9].font = &font_9;

    for( int i=0;i<5;i++ )
    {
        for( int j=0;j<3;j++)
        {
            if( awtrix_number[number].font[i*3+j] == 1 )
            {
                printf("* ");
                map[i+NUMBER_FONT_START_Y][j+NUMBER_FONT_START_X + (position*(NUMBER_FONT_RAW+1))] = 1;
                // 添加坐标偏移，position: 字体向左偏移，NUMBER_FONT_RAW: 3个像素点，一个数字字体列数
            }else
                printf("  ");
        }
        printf("\n");
    }
    return map;
}
