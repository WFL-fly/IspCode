#ifndef _STITCH_H_
#define _STITCH_H_
/* ========================================================================== */
/*                             头文件区                                       */
/* ========================================================================== */
#include "isp.h"
#include "isp_base.h"

/*========================================================================== */
/*                            宏定义区                                  */
/* ========================================================================== */
#if defined(XILINX_FPGA)
	#define ISP_STITCH_BASE     INVALID_BASE   //XILINX下不支持该功能
#else
	#define ISP_STITCH_BASE     0x8e000d00   //Stitch模块基地址
#endif


/***Stitch模块使能控制***/

#define STITCH_EN          *(volatile unsigned int *)((ISP_STITCH_BASE +0x8c) | (1 << 31)) 

/***Stitch模块参数寄存器***/

#define STITCH_CH_A_KB     *(volatile unsigned int *)((ISP_STITCH_BASE +0xb0) | (1 << 31))
#define STITCH_CH_B_KB     *(volatile unsigned int *)((ISP_STITCH_BASE +0xb4) | (1 << 31))
#define STITCH_CH_C_KB     *(volatile unsigned int *)((ISP_STITCH_BASE +0xb8) | (1 << 31))
#define STITCH_CH_D_KB     *(volatile unsigned int *)((ISP_STITCH_BASE +0xbc) | (1 << 31))

/***Stitch模块区域统计和寄存器***/

#define STITCH_CH_A_L       *(volatile unsigned int *)((ISP_STITCH_BASE +0xc0) | (1 << 31))
#define STITCH_CH_A_R       *(volatile unsigned int *)((ISP_STITCH_BASE +0xc4) | (1 << 31))
#define STITCH_CH_B_L       *(volatile unsigned int *)((ISP_STITCH_BASE +0xc8) | (1 << 31))
#define STITCH_CH_B_R       *(volatile unsigned int *)((ISP_STITCH_BASE +0xcc) | (1 << 31))
#define STITCH_CH_C_L       *(volatile unsigned int *)((ISP_STITCH_BASE +0xd0) | (1 << 31))
#define STITCH_CH_C_R       *(volatile unsigned int *)((ISP_STITCH_BASE +0xd4) | (1 << 31))
#define STITCH_CH_D_L       *(volatile unsigned int *)((ISP_STITCH_BASE +0xd8) | (1 << 31))
#define STITCH_CH_D_R       *(volatile unsigned int *)((ISP_STITCH_BASE +0xdc) | (1 << 31))

/* ========================================================================== */
/*                          函数声明区                                        */
/* ========================================================================== */
/*******************************************************************************
* 函数名  : set_Stitch_enable
* 描  述  : Stitch模块使能设置
* 输  入  : 无
			
* 输  出  : 无
* 返回值  : 无
*******************************************************************************/

void set_Stitch_enable(unsigned char en);

/*******************************************************************************
* 函数名  : set_Stitch_param
* 描  述  : 配置Stitch模块矫正参数
* 输  入  : 
          ch_a_param:通道a矫正系数
          ch_b_param:通道b矫正系数
          ch_c_param:通道c矫正系数
          ch_d_param:通道d矫正系数
			
* 输  出  : 无
* 返回值  : 无
*******************************************************************************/

void set_Stitch_param(unsigned int       ch_a_param, unsigned int ch_b_param, unsigned int ch_c_param, unsigned int ch_d_param);

/*******************************************************************************
* 函数名  : get_Stitch_regionsum
* 描  述  : 获取Stitch区域统计和
* 输  入  : 无		
* 输  出  :
            region_sum：统计和数组，8块区域8个统计结果
* 返回值  : 无
*******************************************************************************/

int get_Stitch_regionsum(unsigned int* region_sum);

#endif /* _STA_H_ */

