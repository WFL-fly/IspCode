#pragma once
#ifndef SSIM_H
#define SSIM_H
#include "ErrorTypeDef.h"
#include "BmpTypeDef.h"
typedef struct {
  double c1 ;                /**< 写方差 */
  double c2 ;                /**< 写方差 */
  double c3 ;                /**< 写方差 */
  double avg_x ;            /**均值 */
  double variance_x  ;      /**< 方差 */
  double avg_y  ;           /**均值 */
  double variance_y ;       /**< 方差 */
  double covariance ;       /**< 写方差 */
  double l ;                /**< 亮度相似度 */
  double c ;                /**< 对比度相似度 */
  double s ;                /**< 结构相似度 */
  double res;
} SSIM_Prama;
typedef struct {
  unsigned char* p_data ; /**图像数据指针 */
  int w  ;       /**< 图像宽度 */
  int  h  ;      /**< 图像高度 */
} Data_Prama;
typedef struct {
  double ssimRes[3];  /**结果数组 */
  int count;/**结果个数 8bit图像：1；24bit图像：3； */
} SSIM_FinalRes;

/*******************************************************************************
* 函数名   : getSsimRes
* 描  述   : 获取两幅图的相似度
* 输  入   : 
			 pBmp_x   : 图1 bmp文件指针
		     pBmp_y   : 图2 bmp文件指针
* 输  出   : 
			 res ：相似度结果;范围[-1,1]值越大相似度越高
* 返回值   : ErrorInfoType，0：成功；其他失败。
*******************************************************************************/
ErrorInfoType getSsimRes(Bmp* pBmp_x,Bmp* pBmp_y,SSIM_FinalRes* res );
#endif