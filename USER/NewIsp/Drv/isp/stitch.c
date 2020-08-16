#include <string.h>
#include "sys.h"
#include "isp.h"
#include "stitch.h"

void set_Stitch_enable(unsigned char en)
{
    if (en)
    {
        STITCH_EN = STITCH_EN | 0x80;
    }
    else
    {
        STITCH_EN = STITCH_EN & 0xffffff7f;
    }
}

void set_Stitch_param(unsigned int       ch_a_param,unsigned int ch_b_param,unsigned int ch_c_param, unsigned int ch_d_param)
{
    STITCH_CH_A_KB = ch_a_param;
    STITCH_CH_B_KB = ch_b_param;
    STITCH_CH_C_KB = ch_c_param;
    STITCH_CH_D_KB = ch_d_param;
}

int get_Stitch_regionsum(unsigned int* region_sum)
{
    if(region_sum==NULL)
    {
        return -1;
    }
    region_sum[0] = STITCH_CH_A_L;
    region_sum[1] = STITCH_CH_A_R;
    region_sum[2] = STITCH_CH_B_L;
    region_sum[3] = STITCH_CH_B_R;
    region_sum[4] = STITCH_CH_C_L;
    region_sum[5] = STITCH_CH_C_R;
    region_sum[6] = STITCH_CH_D_L;
    region_sum[7] = STITCH_CH_D_R;
    return 0;
}




