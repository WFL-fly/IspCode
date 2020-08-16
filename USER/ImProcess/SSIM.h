#pragma once
#ifndef SSIM_H
#define SSIM_H
#include "ErrorTypeDef.h"
#include "BmpTypeDef.h"
typedef struct {
  double c1 ;                /**< д���� */
  double c2 ;                /**< д���� */
  double c3 ;                /**< д���� */
  double avg_x ;            /**��ֵ */
  double variance_x  ;      /**< ���� */
  double avg_y  ;           /**��ֵ */
  double variance_y ;       /**< ���� */
  double covariance ;       /**< д���� */
  double l ;                /**< �������ƶ� */
  double c ;                /**< �Աȶ����ƶ� */
  double s ;                /**< �ṹ���ƶ� */
  double res;
} SSIM_Prama;
typedef struct {
  unsigned char* p_data ; /**ͼ������ָ�� */
  int w  ;       /**< ͼ���� */
  int  h  ;      /**< ͼ��߶� */
} Data_Prama;
typedef struct {
  double ssimRes[3];  /**������� */
  int count;/**������� 8bitͼ��1��24bitͼ��3�� */
} SSIM_FinalRes;

/*******************************************************************************
* ������   : getSsimRes
* ��  ��   : ��ȡ����ͼ�����ƶ�
* ��  ��   : 
			 pBmp_x   : ͼ1 bmp�ļ�ָ��
		     pBmp_y   : ͼ2 bmp�ļ�ָ��
* ��  ��   : 
			 res �����ƶȽ��;��Χ[-1,1]ֵԽ�����ƶ�Խ��
* ����ֵ   : ErrorInfoType��0���ɹ�������ʧ�ܡ�
*******************************************************************************/
ErrorInfoType getSsimRes(Bmp* pBmp_x,Bmp* pBmp_y,SSIM_FinalRes* res );
#endif