#include "system.h"
#include "isp.h"
#include "iif.h"
#include "sys.h"

//rb_flag:'1'-> R ; '0'-> B
void iif_conf(IspIifConfig *iifConfig)
{
	char tmp_rb_flag;

	VI_H_Size = iifConfig->hsize_all / SysChannelNum();
	VI_V_Size = iifConfig->vsize_all;
	VI_H_Dummy = iifConfig->h_start;
	VI_V_Dummy = iifConfig->v_start;
	VI_H_Size_Valid = iifConfig->hsize_valid / SysChannelNum();
	VI_V_Size_Valid = iifConfig->vsize_valid;

	tmp_rb_flag = iifConfig->is_odd_offset ? (!iifConfig->rb_flag) : iifConfig->rb_flag;
	VI_R_B_Flag = tmp_rb_flag ? 1 : 0;  //1:B;0:R

	/* set VI_RPG_valid register to enable isp test image */
//	VI_RPG_valid = 0x1;
	VI_Ram_RD_Start = iifConfig->hsize_valid / SysChannelNum();
	VI_V_TYPE = iifConfig->v_type;
}

void setIIFRPG(unsigned char enable)
{
#ifndef WIN32
	VI_RPG_valid = enable;
#endif
}
/****
modify by wang_fulai 2019_08_28:
对于 AX5B51MT250 ISP 8ch mono的相机，在ISP做X翻转是比较特殊，需要关闭X轴翻转时最后一列的裁剪功能，与CameraLink一致
在其他相机下，默认在ISP做X轴翻转时，会进行最后一行的裁剪

isp 在X周翻转时，是否进行最后一列的裁剪
0：不做裁剪
1：做裁剪
配置一次即可

***/
void iif_set_flipx_cut(unsigned char enable)
{
    if(enable)
    {
        VI_RPG_valid = VI_RPG_valid & 0x10;
    }
    else
    {
        VI_RPG_valid = VI_RPG_valid | 0x10;
    }
}

unsigned int iif_get_mask(void)
{
	return INPUT_MASK;
}

void iif_set_mask(unsigned int mask)
{
	INPUT_MASK = mask;
}


void iif_set_width_All(unsigned short width)
{
#ifndef WIN32
	VI_H_Size = width;
#endif
}

void iif_set_height_All(unsigned short height)
{
#ifndef WIN32
	VI_V_Size = height;
#endif
}

void iif_set_width_Dummy(unsigned short width)
{
#ifndef WIN32
	VI_H_Dummy = width;
#endif
}

void iif_set_height_Dummy(unsigned short height)
{
#ifndef WIN32
	VI_V_Dummy = height;
#endif
}

void iif_set_width_Valid(unsigned short width)
{
#ifndef WIN32
	VI_H_Size_Valid = width;
	VI_Ram_RD_Start = width;
#endif
}

void iif_set_height_Valid(unsigned short height)
{
#ifndef WIN32
	VI_V_Size_Valid = height;
#endif
}

void iif_set_R_B_Flag(unsigned char rb_flag)
{
#ifndef WIN32
	VI_R_B_Flag = rb_flag ? 1 : 0; 
	SENSOR_R_B_FLAG = rb_flag ? 0 : 0xffffffff;
#endif
}

void iif_set_V_Type(unsigned char v_type)
{
#ifndef WIN32
	VI_V_TYPE = v_type ? 1 : 0; 
#endif
}


void iif_set_flipX(unsigned char flipX)
{
	if (flipX)
	{
		VI_RPG_valid = VI_RPG_valid | 0x02;
	}
	else
	{
		VI_RPG_valid = VI_RPG_valid & 0xfd;	/* bit9 H_Turn */
	}
}
