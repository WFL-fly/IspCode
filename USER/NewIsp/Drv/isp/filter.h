#ifndef _FILTER_H_
#define _FILTER_H_

#include "isp_base.h"

#define FILTER_BASE ISP_NR2D_BASE
#define FILTER_MEDIAN_EN  *(volatile unsigned char *) ((FILTER_BASE + COV_CHAR(0x00)) | (1 << 31))
#define FILTER_GAUSS_EN   *(volatile unsigned char *) ((FILTER_BASE + COV_CHAR(0x13)) | (1 << 31))

#define FILTER_BILATERAL_ALPHA  *(volatile unsigned char *) ((FILTER_BASE + COV_CHAR(0x04)) | (1 << 31))
#define FILTER_BILATERAL_EN		*(volatile unsigned char *) ((FILTER_BASE + COV_CHAR(0x05)) | (1 << 31))
#define FILTER_BILATERAL_SLOPE  *(volatile unsigned short *) ((FILTER_BASE + COV_SHORT(0x06)) | (1 << 31))
#define FILTER_BILATERAL_WEIGHT *(volatile unsigned int *) ((FILTER_BASE + 0x08) | (1ul << 31))

//u.4.0       
#define FILTER_GAUSS_A  *(volatile unsigned char *) ((FILTER_BASE + COV_CHAR(0x12)) | (1 << 31))
#define FILTER_GAUSS_B  *(volatile unsigned char *) ((FILTER_BASE + COV_CHAR(0x11)) | (1 << 31))
#define FILTER_GAUSS_C  *(volatile unsigned char *) ((FILTER_BASE + COV_CHAR(0x10)) | (1 << 31))
//U.0.14
#define FILTER_GAUSS_SUM_INV  *(volatile unsigned short *) ((FILTER_BASE + COV_SHORT(0x14)) | (1 << 31))

void filter_median(unsigned char enable);
void filter_gauss(unsigned char enable);
void filter_gauss_param(unsigned char param_a, unsigned char param_b,
	unsigned char param_c, unsigned short sum_inv);
void filter_bilateral(unsigned char enable);
void filter_bilateral_param(unsigned short slope, unsigned char alpha, 
	unsigned char weight_0, unsigned char weight_1, unsigned char weight_2);

#endif
