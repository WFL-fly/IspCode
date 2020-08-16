#include "rgb2raw.h"

//set, get and init value for RGB2RAW module
void INIT_RGB2RAW(void)
{
}

void set_value_RB_horizontal_RGB2RAW(unsigned char rb_horizontal)
{
    RGB2RAW_RB_horizontal = rb_horizontal;
}

void get_value_RB_horizontal_RGB2RAW(unsigned char *rb_horizontal)
{
    *rb_horizontal = RGB2RAW_RB_horizontal;
}

void set_value_RB_vertical_RGB2RAW(unsigned char rb_vertical)
{
    RGB2RAW_RB_vertical = rb_vertical;
}

void get_value_RB_vertical_RGB2RAW(unsigned char *rb_vertical)
{
    *rb_vertical = RGB2RAW_RB_vertical;
}

