#ifndef FPN_H_
#define FPN_H_

#include "isp_base.h"

#define FPN_PAGE_SEL				*(volatile unsigned   int *)((ISP_FPN_BASE + 0x00)|(1<<31))
#define FPN_Correct_En				*(volatile unsigned   int *)((ISP_FPN_BASE + 0x40)|(1<<31)) 
#define FPN_Dark_Avg				*(volatile unsigned   int *)((ISP_FPN_BASE + 0x44)|(1<<31))
#define FPN_Satu_Avg				*(volatile unsigned short *)((ISP_FPN_BASE + COV_SHORT(0x48))|(1<<31))
#define FPN_X_Axis_Flip_En			*(volatile unsigned   int *)((ISP_FPN_BASE + 0x4C)|(1<<31))
#define FPN_X_Axis_Offset			*(volatile unsigned   int *)((ISP_FPN_BASE + 0x50)|(1<<31))
#define FPN_X_Axis_FlipMode_En		*(volatile unsigned int *)((ISP_FPN_BASE + 0x04 )|(1<<31))
#define FPN_Threshold				*(volatile unsigned   int *)((ISP_FPN_BASE + 0x54)|(1<<31))

#define FPN_Avg_Calc_En             *(volatile unsigned   int *)((ISP_FPN_BASE + 0x80 )|(1<<31))
#define FPN_Avg_Line_Interval       *(volatile unsigned   int *)((ISP_FPN_BASE + 0x84 )|(1<<31))  // line interlace for color
#define FPN_Avg_Calc_Line_Start     *(volatile unsigned short *)((ISP_FPN_BASE + COV_SHORT(0x88) )|(1<<31))
#define FPN_Avg_Calc_Line_End       *(volatile unsigned short *)((ISP_FPN_BASE + COV_SHORT(0x8A) )|(1<<31))
#define FPN_Avg_Calc_Fram_Intelace  *(volatile unsigned short *)((ISP_FPN_BASE + COV_SHORT(0x8C) )|(1<<31))
#define FPN_Avg_Calc_Mult_Frame     *(volatile unsigned short *)((ISP_FPN_BASE + COV_SHORT(0x8E) )|(1<<31))
#define FPN_Avg_Calc_Sum_Inv        *(volatile unsigned   int *)((ISP_FPN_BASE + 0x90 )|(1<<31))
#define FPN_Avg_Calc_Updt_Clr       *(volatile unsigned short *)((ISP_FPN_BASE + COV_SHORT(0x94) )|(1<<31))
#define FPN_Avg_Calc_Updt_Indic     *(volatile unsigned short *)((ISP_FPN_BASE + COV_SHORT(0x96) )|(1<<31))

#define FPN_Img_Fix_En				*(volatile unsigned short *)((ISP_FPN_BASE + COV_SHORT(0x98)) | (1ul << 31))
#define FPN_Img_Fix_Base			*(volatile unsigned short *)((ISP_FPN_BASE + COV_SHORT(0x9A)) | (1ul << 31))
#define FPN_Img_Fix_Low				*(volatile unsigned short *)((ISP_FPN_BASE + COV_SHORT(0x9C)) | (1ul << 31))
#define FPN_Img_Fix_High			*(volatile unsigned short *)((ISP_FPN_BASE + COV_SHORT(0x9E)) | (1ul << 31))

#define FPN_RAM_Param_Base			(volatile unsigned int *)((ISP_FPN_BASE + 0x4000 )|(1<<31))

void FPN_Correct_Enable(void);
void FPN_Correct_Disable(void);
void FPN_Statics_Enable(void);
void FPN_Statics_Disable(void);
int FPN_Statics_Param_Set(unsigned int line_start, unsigned int line_end,
	unsigned int line_interval, unsigned int para_mult_frame);
int FPN_Set_Pixel_Param(unsigned int *FPN_Pixel_Param, unsigned int count, 
	unsigned int Param_FPN_Satu_Avg, unsigned int Param_FPN_Dark_Avg, 
	unsigned int Param_FPN_Threshold,unsigned int param_flip);
int FPN_Get_Pixel_Avg(unsigned short *FPN_Pixel_Avg, unsigned int count);
void FPN_Set_Flip_Offset(unsigned int flip, unsigned int offset);
void FPN_Img_Fix_Param_Set(unsigned short base, unsigned short high, unsigned short low);
void FPN_Img_Fix_Enable(void);
void FPN_Img_Fix_Disable(void);
unsigned char FPN_Get_Version(void);

#endif /* FPN_H_ */
