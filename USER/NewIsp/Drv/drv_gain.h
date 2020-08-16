/*******************************************************************************
* app_gain.h
*
* Copyright (C) 2019-2021 ZheJiang Dahua Technology CO.,LTD.
*
* Author : Yan Hongsheng  <yan_hongsheng@dahuatech.com>
* Version: V1.0.0  2019-9-1 Create
*
* Desc: 
*
* Modification:
*    Date    :
*    Revision:
*    Author  :
*    Contents:
*******************************************************************************/
#ifndef _DRV_ISP_GAIN_H_
#define _DRV_ISP_GAIN_H_

/* ========================================================================== */
/*                          ���ݽṹ������                                    */
/* ========================================================================== */
/*********Gain �Ĵ�������*****/
/*
 * define the register name  for Digital Gain module
 *
 * DG_BASE:		the base for  Digital Gain module
 * DG_Gr:		Gr piexel's gain coef
 * DG_R:		R  piexel's gain coef
 * DG_B:		B  piexel's gain coef
 * DG_Gb:		Gb piexel's gain coef
 * ���ݸ�ʽ:u8.8
 * */

void DrvIspGain_paraDefault(void);
void DrvIspGain_Run(void);
#endif/*** **/
