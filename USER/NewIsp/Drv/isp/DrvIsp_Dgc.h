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
* ������  : Dg_Init
* ��  ��  : ��ʼ��mono��������
* ��  ��  : ��
* ��  ��  : ��
* ����ֵ  : ��
*******************************************************************************/
void DrvIspDgcDg_Init(void);
/*******************************************************************************
* ������  : Gg_setVal
* ��  ��  : ����mono��������
* ��  ��  : ��
* ��  ��  : ��������ֵ
* ����ֵ  : ��
*******************************************************************************/
void DrvIspDgcGg_setVal(float coff);
/*******************************************************************************
* ������  : Dg_getVal
* ��  ��  : ��ȡmono��������
* ��  ��  : ��
* ��  ��  : ��������ֵ
* ����ֵ  : ��
*******************************************************************************/
void DrvIspDgcDg_getVal(unsigned short *coff);
/*******************************************************************************
* ������  : Dgc_Init
* ��  ��  : ��ɫ���������ʼ��
            Ĭ������1������
* ��  ��  : ��
* ��  ��  : ��
* ����ֵ  : ��
*******************************************************************************/
void DrvIspDgcDgc_Init(void);
/*******************************************************************************
* ������  : Dgc_Init
* ��  ��  : ���ò�ɫ��������
* ��  ��  : ��ͨ����������ֵ
* ��  ��  : ��
* ����ֵ  : ��
*******************************************************************************/
void DrvIspDgc_setVal(float gr, float r, float b, float gb);
/*******************************************************************************
* ������  : Dgc_getVal
* ��  ��  : ��ȡ��ɫ��������
* ��  ��  : ��
* ��  ��  : ��ͨ����������ֵ
* ����ֵ  : ��
*******************************************************************************/
void DrvIspDgcDgc_getVal(float *gr, float *r, float *b, float *gb);
#endif
