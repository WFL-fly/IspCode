#ifndef _STITCH_H_
#define _STITCH_H_
/* ========================================================================== */
/*                             ͷ�ļ���                                       */
/* ========================================================================== */
#include "isp.h"
#include "isp_base.h"

/*========================================================================== */
/*                            �궨����                                  */
/* ========================================================================== */
#if defined(XILINX_FPGA)
	#define ISP_STITCH_BASE     INVALID_BASE   //XILINX�²�֧�ָù���
#else
	#define ISP_STITCH_BASE     0x8e000d00   //Stitchģ�����ַ
#endif


/***Stitchģ��ʹ�ܿ���***/

#define STITCH_EN          *(volatile unsigned int *)((ISP_STITCH_BASE +0x8c) | (1 << 31)) 

/***Stitchģ������Ĵ���***/

#define STITCH_CH_A_KB     *(volatile unsigned int *)((ISP_STITCH_BASE +0xb0) | (1 << 31))
#define STITCH_CH_B_KB     *(volatile unsigned int *)((ISP_STITCH_BASE +0xb4) | (1 << 31))
#define STITCH_CH_C_KB     *(volatile unsigned int *)((ISP_STITCH_BASE +0xb8) | (1 << 31))
#define STITCH_CH_D_KB     *(volatile unsigned int *)((ISP_STITCH_BASE +0xbc) | (1 << 31))

/***Stitchģ������ͳ�ƺͼĴ���***/

#define STITCH_CH_A_L       *(volatile unsigned int *)((ISP_STITCH_BASE +0xc0) | (1 << 31))
#define STITCH_CH_A_R       *(volatile unsigned int *)((ISP_STITCH_BASE +0xc4) | (1 << 31))
#define STITCH_CH_B_L       *(volatile unsigned int *)((ISP_STITCH_BASE +0xc8) | (1 << 31))
#define STITCH_CH_B_R       *(volatile unsigned int *)((ISP_STITCH_BASE +0xcc) | (1 << 31))
#define STITCH_CH_C_L       *(volatile unsigned int *)((ISP_STITCH_BASE +0xd0) | (1 << 31))
#define STITCH_CH_C_R       *(volatile unsigned int *)((ISP_STITCH_BASE +0xd4) | (1 << 31))
#define STITCH_CH_D_L       *(volatile unsigned int *)((ISP_STITCH_BASE +0xd8) | (1 << 31))
#define STITCH_CH_D_R       *(volatile unsigned int *)((ISP_STITCH_BASE +0xdc) | (1 << 31))

/* ========================================================================== */
/*                          ����������                                        */
/* ========================================================================== */
/*******************************************************************************
* ������  : set_Stitch_enable
* ��  ��  : Stitchģ��ʹ������
* ��  ��  : ��
			
* ��  ��  : ��
* ����ֵ  : ��
*******************************************************************************/

void set_Stitch_enable(unsigned char en);

/*******************************************************************************
* ������  : set_Stitch_param
* ��  ��  : ����Stitchģ���������
* ��  ��  : 
          ch_a_param:ͨ��a����ϵ��
          ch_b_param:ͨ��b����ϵ��
          ch_c_param:ͨ��c����ϵ��
          ch_d_param:ͨ��d����ϵ��
			
* ��  ��  : ��
* ����ֵ  : ��
*******************************************************************************/

void set_Stitch_param(unsigned int       ch_a_param, unsigned int ch_b_param, unsigned int ch_c_param, unsigned int ch_d_param);

/*******************************************************************************
* ������  : get_Stitch_regionsum
* ��  ��  : ��ȡStitch����ͳ�ƺ�
* ��  ��  : ��		
* ��  ��  :
            region_sum��ͳ�ƺ����飬8������8��ͳ�ƽ��
* ����ֵ  : ��
*******************************************************************************/

int get_Stitch_regionsum(unsigned int* region_sum);

#endif /* _STA_H_ */

