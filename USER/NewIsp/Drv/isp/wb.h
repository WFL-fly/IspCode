#ifndef _WB_H_
#define _WB_H_

#include "isp_base.h"

/*
 * define the register names of  WB module
 *
 * WB_BASE: 	base address of WB module
 * WB_Gr:		gain coef of Gr pixel
 * WB_R:		gain coef of R pixel
 * WB_B:		gain coef of B pixel
 * WB_Gb:		gain coef of Gb pixel
 * WB_Gr_CLIP:	Gr saturation
 * WB_R_CLIP:	R  saturation
 * WB_B_CLIP:	B  saturation
 * WB_Gb_CLIP:	Rb saturation
 * */
#define WB_BASE ISP_WB_BASE

#define WB_Gr *(volatile unsigned short *) ((WB_BASE + COV_SHORT(0x00)) | (1 << 31))
#define WB_R *(volatile unsigned short *) ((WB_BASE + COV_SHORT(0x02)) | (1 << 31))
#define WB_B *(volatile unsigned short *) ((WB_BASE + COV_SHORT(0x04)) | (1 << 31))
#define WB_Gb *(volatile unsigned short *) ((WB_BASE + COV_SHORT(0x06)) | (1 << 31))
#define WB_Gr_CLIP *(volatile unsigned short *) ((WB_BASE + COV_SHORT(0x08)) | (1 << 31))
#define WB_R_CLIP *(volatile unsigned short *) ((WB_BASE + COV_SHORT(0x0a)) | (1 << 31))
#define WB_B_CLIP *(volatile unsigned short *) ((WB_BASE + COV_SHORT(0x0c)) | (1 << 31))
#define WB_Gb_CLIP *(volatile unsigned short *) ((WB_BASE + COV_SHORT(0x0e)) | (1 << 31))

void INIT_WB(void);

/*
 * set gain coef of RGB channels in WB module
 * parameter list:
 * gr:	gain coef of Gr pixel, float , converted to u.8.8
 * r:	gain coef of R pixel,  float , converted to u.8.8
 * b:	gain coef of B pixel,  float , converted to u.8.8
 * gb:	gain coef of Gb pixel, float , converted to u.8.8
 * */
void set_value_Gain_WB(float gr, float r, float b, float gb);

void get_value_Gain_WB(unsigned short *gr, unsigned short *r, unsigned short *b, unsigned short *gb);

/*
 * set CLIP value of RGB channels in WB(thred for lum saturation)
 * parameter list:
 * gr:	Gr CLIP,  unsigned short, converted to u.14.0
 * r:	R  CLIP,  unsigned short, converted to u.14.0
 * b:	B  CLIP,  unsigned short, converted to u.14.0
 * gb:	Gb CLIP,  unsigned short, converted to u.14.0
 * */
void set_value_Gain_WB_thrd(unsigned short gr, unsigned short r, unsigned short b, unsigned short gb);

#endif
