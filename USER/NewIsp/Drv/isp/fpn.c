#include <stdio.h>
#include <string.h>
#include "fpn.h"

#define FPNPARAM_MAXCOUNT 4096

static unsigned char s_inited = 0;
static unsigned char s_fpnVersion = 0;

unsigned char FPN_Get_Version(void)
{
	unsigned int currentValue;
	unsigned int readValue;

	if (!s_inited)
	{
		FPN_PAGE_SEL = 0;
		currentValue = *(volatile unsigned int *)(ISP_FPN_BASE + 0x4000);
		*(volatile unsigned int *)(ISP_FPN_BASE + 0x4000) = 0xFFFFFFFF;
		readValue = *(volatile unsigned int *)(ISP_FPN_BASE + 0x4000);
		*(volatile unsigned int *)(ISP_FPN_BASE + 0x4000) = currentValue;

		if ((readValue & 0xFFFF) == 0x1FFF)
		{
			s_fpnVersion = 0;
		}
		else if ((readValue & 0xFFFF) == 0x7FF)
		{
			s_fpnVersion = 1;
		}
		else    //((readValue & 0xFFFF) == 0xFFFF)
		{
		    s_fpnVersion = 2;
		}
		s_inited = 1;
	}

	return s_fpnVersion;
}

/*
 * FPN_Correct_Enable - FPN矫正使能
 */
void FPN_Correct_Enable(void)
{
	if (!s_inited)
	{
		FPN_Get_Version();
	}

	FPN_Correct_En = 1;
}

/*
 * FPN_Correct_Disable - FPN矫正关闭
 */
void FPN_Correct_Disable(void)
{
	FPN_Correct_En = 0;
}

/*
 * FPN_Statics_Enable - FPN统计使能
 */
void FPN_Statics_Enable(void)
{
	FPN_Avg_Calc_En = 1;
}

/*
 * FPN_Statics_Disable - FPN统计关闭
 */
void FPN_Statics_Disable(void)
{
	FPN_Avg_Calc_En = 0;
}

/*
 * FPN_Img_Fix_Enable - FPN坏点修正使能
 */
void FPN_Img_Fix_Enable(void)
{
	FPN_Img_Fix_En = 1;
}

/*
 * FPN_Img_Fix_Disable - FPN坏点修正关闭
 */
void FPN_Img_Fix_Disable(void)
{
	FPN_Img_Fix_En = 0;
}

/*
 * FPN_Img_Fix_Param_Set - 设置FPN坏点修正参数
 * 
 *   base - 矫正值
 *   high - 偏差上限
 *   low - 偏差下限
 */
void FPN_Img_Fix_Param_Set(unsigned short base, unsigned short high, unsigned short low)
{
	FPN_Img_Fix_Base = base;
	FPN_Img_Fix_High = high;
	FPN_Img_Fix_Low = low;
}

/*
 * FPN_Statics_Param_Set - 设置FPN统计参数
 * 
 *   line_start - 统计起始行
 *   line_end - 统计结束行
 *   line_interval - 统计行间隔
 *   para_mult_frame - 统计帧数，最小为1
 * 
 * Note :
 *
 *   通常黑白Sensor统计行间隔为0，彩色Sensor统计行间隔为1
 *   总的统计行数不得超过64k
 *   假如图像高度为1024，要取所有行做统计，则line_start为1，line_end为1024
 */
int FPN_Statics_Param_Set(unsigned int line_start, unsigned int line_end, 
	unsigned int line_interval, unsigned int para_mult_frame)
{
	unsigned int lines;
	unsigned int param_inv;

	if ((line_end <= line_start) || (para_mult_frame < 1))
	{
		printf("fpn statics : invalid param\n");
		return -1;
	}

	lines = (line_end - line_start) / (line_interval + 1) * para_mult_frame;

	if (lines > 64 * 1024)
	{
		printf("fpn statics : too many lines\n");
		return -1;
	}

	param_inv = (1ul << 28) / lines;

	FPN_Avg_Line_Interval = line_interval;   // 间隔行数 
	FPN_Avg_Calc_Line_Start = line_start;
	FPN_Avg_Calc_Line_End = line_end;
	FPN_Avg_Calc_Fram_Intelace = 0;
	FPN_Avg_Calc_Mult_Frame = para_mult_frame - 1;
	FPN_Avg_Calc_Sum_Inv = param_inv;

	return 0;
}

/*
 * FPN_Set_Pixel_Param - 写入FPN矫正参数
 * 
 *   FPN_Pixel_Param - FPN矫正系数
 *   count - 数据个数
 *   Param_FPN_Satu_Avg - 亮图统计平均值
 *   Param_FPN_Dark_Avg - 暗图统计平均值
 *   Param_FPN_Threshold - 矫正门限
 * *******************************************
 *
 *  wang_fulai modify 2019_08_28:
 *  修改FPN_Set_Pixel_Param函数接口：
 *  1.增加函数传参：
 *       param_flip，该参数表示在写入FPN参数到FPGA寄存器时，是否要倒着写入
 *      0：参数正序写入；1：参数倒序写入
 *  2.修改函数参数写入方式，使其支持正序写入和倒序写入
 ********************************************
 */
int FPN_Set_Pixel_Param(unsigned int *FPN_Pixel_Param, unsigned int count, 
	unsigned int Param_FPN_Satu_Avg, unsigned int Param_FPN_Dark_Avg, 
	unsigned int Param_FPN_Threshold,unsigned int param_flip)
{
	volatile unsigned int *ram_addr;
	unsigned char page;
	unsigned int fpn_param_count;
	unsigned int i;
    unsigned int index=0;
    unsigned int val=0;
    unsigned int index_1_val = 0;
    
	if ((count > 8192) || FPN_Pixel_Param == NULL)
	{
		printf("fpn set : invalid parameter(s)\n");
		return -1;
	}

	FPN_Dark_Avg = Param_FPN_Dark_Avg;
	FPN_Satu_Avg = Param_FPN_Satu_Avg;
	FPN_Threshold = Param_FPN_Threshold;
    index_1_val = *(FPN_Pixel_Param+1);

	page = 0;
	ram_addr = FPN_RAM_Param_Base;

	fpn_param_count = 0;
    if(param_flip)
    {
       
        FPN_Pixel_Param += (count-2);
        count = count-1;
    }
    index = 0;
    
    while(index<count)
    {
        FPN_PAGE_SEL = index/FPNPARAM_MAXCOUNT;
        if(param_flip)
        {
            val=*(FPN_Pixel_Param - index);
        }
        else
        {
            val=*(FPN_Pixel_Param + index);
        }
        *(ram_addr + index%FPNPARAM_MAXCOUNT)=val;
        index++;
    }
    if(param_flip)
    {
        FPN_PAGE_SEL = index/FPNPARAM_MAXCOUNT;
       *(ram_addr + index%FPNPARAM_MAXCOUNT)=index_1_val;
    }
	return 0;
}

/*
 * FPN_Set_Flip_Offset - 设置FPN的翻转及offset属性
 * 
 *   flip - 是否开启翻转
 *   offset - 位移像素数
 */
void FPN_Set_Flip_Offset(unsigned int flip, unsigned int offset)
{
	FPN_X_Axis_FlipMode_En = flip;
	FPN_X_Axis_Flip_En = flip;
	FPN_X_Axis_Offset = offset;
}

/*
 * FPN_Get_Pixel_Avg - 读取FPN统计值
 *
 *   FPN_Pixel_Avg - 各列像素平均值
 *   count - 列数
 */
int FPN_Get_Pixel_Avg(unsigned short *FPN_Pixel_Avg, unsigned int count)
{
	volatile unsigned int timeout = 100;
	volatile unsigned int *ram_addr;
	unsigned int i;

	if (FPN_Pixel_Avg == NULL || count > 8192)
	{
		printf("fpn get : invalid parameter(s)\n");
		return -1;
	}

	if (!FPN_Avg_Calc_Updt_Indic)
	{
		printf("fpn get : waiting for statics\n");
	}

	while ((timeout--) && !FPN_Avg_Calc_Updt_Indic) ;

	if (!timeout)
	{
		printf("fpn get : timeout\n");
		return -1;
	}

	ram_addr = FPN_RAM_Param_Base;

	if (count <= 4096)
	{
		FPN_PAGE_SEL = 0x10;
		for (i = 0; i < count; i++)
		{
			FPN_Pixel_Avg[i] = ram_addr[i];
		}
		//memcpy(FPN_Pixel_Avg, ram_addr, 4 * count);
	}
	else
	{
		FPN_PAGE_SEL = 0x10;
		for (i = 0; i < 4096; i++)
		{
			FPN_Pixel_Avg[i] = ram_addr[i];
		}
		//memcpy(FPN_Pixel_Avg, ram_addr, 4 * 4096);
		FPN_PAGE_SEL = 0x11;
		for (i = 0; i < (count - 4096); i++)
		{
			FPN_Pixel_Avg[i + 4096] = ram_addr[i];
		}
		//memcpy(FPN_Pixel_Avg + 4096, ram_addr, 4 * (count - 4096));
	}

	FPN_Avg_Calc_Updt_Clr = 1;
	FPN_Avg_Calc_Updt_Clr = 0;

	return 0;
}
