#ifndef _DGC_H_
#define _DGC_H_

#include "isp_base.h"

/*
 * define the register name  for Digital Gain module
 *
 * DG_BASE:		the base for  Digital Gain module
 * DG_Gr:		Gr piexel's gain coef
 * DG_R:		R  piexel's gain coef
 * DG_B:		B  piexel's gain coef
 * DG_Gb:		Gb piexel's gain coef
 * */
#define __DEBUG_TEST__
#ifdef __DEBUG_TEST__
#define ISP_DGC_BASE 0x9a000000 
#endif

#define DG_BASE ISP_DGC_BASE

#define DG_Gr *(volatile unsigned short *) ((DG_BASE + COV_SHORT(0x00)) | (1 << 31))
#define DG_R  *(volatile unsigned short *) ((DG_BASE + COV_SHORT(0x02)) | (1 << 31))
#define	DG_B  *(volatile unsigned short *) ((DG_BASE + COV_SHORT(0x04)) | (1 << 31))
#define DG_Gb *(volatile unsigned short *) ((DG_BASE + COV_SHORT(0x06)) | (1 << 31))


/*******************************************************************************
* 函数名  : Dg_Init
* 描  述  : 初始化mono数字增益
* 输  入  : 无
* 输  出  : 无
* 返回值  : 无
*******************************************************************************/
void DrvIspDgcDg_Init(void);
/*******************************************************************************
* 函数名  : Gg_setVal
* 描  述  : 设置mono数字增益
* 输  入  : 无
* 输  出  : 增益设置值
* 返回值  : 无
*******************************************************************************/
void DrvIspDgcGg_setVal(float coff);
/*******************************************************************************
* 函数名  : Dg_getVal
* 描  述  : 获取mono数字增益
* 输  入  : 无
* 输  出  : 增益设置值
* 返回值  : 无
*******************************************************************************/
void DrvIspDgcDg_getVal(unsigned short *coff);
/*******************************************************************************
* 函数名  : Dgc_Init
* 描  述  : 彩色数字增益初始化
            默认设置1倍增益
* 输  入  : 无
* 输  出  : 无
* 返回值  : 无
*******************************************************************************/
void DrvIspDgcDgc_Init(void);
/*******************************************************************************
* 函数名  : Dgc_Init
* 描  述  : 设置彩色数字增益
* 输  入  : 各通道增益设置值
* 输  出  : 无
* 返回值  : 无
*******************************************************************************/
void DrvIspDgc_setVal(float gr, float r, float b, float gb);
/*******************************************************************************
* 函数名  : Dgc_getVal
* 描  述  : 获取彩色数字增益
* 输  入  : 无
* 输  出  : 各通道增益设置值
* 返回值  : 无
*******************************************************************************/
void DrvIspDgcDgc_getVal(float *gr, float *r, float *b, float *gb);
#endif
