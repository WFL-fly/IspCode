#ifndef _RGB2YUV_H_
#define _RGB2YUV_H_

#include "isp_base.h"

#define CSC_CDC_BASE ISP_CDS_BASE
#define CSC_CDC_Module_Select *(volatile unsigned char *) ((CSC_CDC_BASE + COV_CHAR(0x00)) | (1 << 31))
#define CSC_CDC_Y_Switch *(volatile unsigned char *) ((CSC_CDC_BASE + COV_CHAR(0x01)) | (1 << 31))
#define CSC_CDC_UV_Select *(volatile unsigned char *) ((CSC_CDC_BASE + COV_CHAR(0x02)) | (1 << 31))
#define CSC_CDC_BW_Ena *(volatile unsigned char *) ((CSC_CDC_BASE + COV_CHAR(0x03)) | (1 << 31))
#define CSC_CDC_KY_B *(volatile unsigned char *) ((CSC_CDC_BASE + COV_CHAR(0x04)) | (1 << 31))
#define CSC_CDC_KY_R *(volatile unsigned char *) ((CSC_CDC_BASE + COV_CHAR(0x05)) | (1 << 31))
#define CSC_CDC_KY_G *(volatile unsigned char *) ((CSC_CDC_BASE + COV_CHAR(0x24)) | (1 << 31))
#define CSC_CDC_KCr_R *(volatile unsigned char *) ((CSC_CDC_BASE + COV_CHAR(0x06)) | (1 << 31))
#define CSC_CDC_KCb_B *(volatile unsigned char *) ((CSC_CDC_BASE + COV_CHAR(0x07)) | (1 << 31))
#define CSC_CDC_KCb_G *(volatile short *) ((CSC_CDC_BASE + COV_SHORT(0x08)) | (1 << 31))
#define CSC_CDC_KCb_R *(volatile short *) ((CSC_CDC_BASE + COV_SHORT(0x0A)) | (1 << 31))
#define CSC_CDC_KCr_B *(volatile short *) ((CSC_CDC_BASE + COV_SHORT(0x0C)) | (1 << 31))
#define CSC_CDC_KCr_G *(volatile short *) ((CSC_CDC_BASE + COV_SHORT(0x0E)) | (1 << 31))
#define CSC_CDC_Offset_Cr *(volatile unsigned char *) ((CSC_CDC_BASE + COV_CHAR(0x10)) | (1 << 31))
#define CSC_CDC_Offset_Cb *(volatile unsigned char *) ((CSC_CDC_BASE + COV_CHAR(0x11)) | (1 << 31))
#define CSC_CDC_Offset_Y *(volatile short *) ((CSC_CDC_BASE + COV_SHORT(0x12)) | (1<<31))
#define CSC_CDC_KNEE *(volatile unsigned short *) ((CSC_CDC_BASE + COV_SHORT(0x14)) | (1 << 31))
#define CSC_CDC_KNEEP *(volatile unsigned short *) ((CSC_CDC_BASE + COV_SHORT(0x16)) | (1 << 31))
#define CSC_CDC_Y_Gain *(volatile unsigned char *) ((CSC_CDC_BASE + COV_CHAR(0x18)) | (1 << 31))
#define CSC_CDC_Thres_l *(volatile unsigned char *) ((CSC_CDC_BASE + COV_CHAR(0x1A)) | (1 << 31))
#define CSC_CDC_Y_Level *(volatile unsigned short *) ((CSC_CDC_BASE + COV_SHORT(0x28)) | (1 << 31))
#define CSC_CDC_Brt *(volatile short *) ((CSC_CDC_BASE + COV_SHORT(0x1c)) | (1 << 31))
#define CSC_CDC_Ctr *(volatile unsigned char *) ((CSC_CDC_BASE + COV_CHAR(0x1E)) | (1 << 31))
#define CSC_CDC_Cos *(volatile char *) ((CSC_CDC_BASE + COV_CHAR(0x20)) | (1 << 31))
#define CSC_CDC_Sin *(volatile char *) ((CSC_CDC_BASE + COV_CHAR(0x21)) | (1 << 31))
#define CSC_CDC_Sat *(volatile unsigned char *) ((CSC_CDC_BASE + COV_CHAR(0x22)) | (1 << 31))

/*
 * set, get and init value for CSC_CDC module
 * */
//init the CSC_CDC module
void INIT_CSC_CDC(void);

/*
 * set conversion mode and set u or v signal output first
 * parameter list：
 * module：	YUV444-YUV422 conversion mode
 * uv:		 select u or v which signal output first
 * */
void set_value_module_UV_CSC_CDC(unsigned char module, unsigned char uv);
void get_value_module_UV_CSC_CDC(unsigned char *module, unsigned char *uv);

/*
 * set enable for Y and UV Saturation
 * parameter list：
 * y_switch:		1 :enable this function,
 *              0: disable
 */
void set_value_Y_Switch_CSC_CDC(unsigned char y_switch);

void get_value_Y_Switch_CSC_CDC(unsigned char *y_switch);

/*
 * set switch for black_white mode
 * parameter list:
 * bw_ena		1:black_white mode
 *							0:color mode
 *
 */
void set_value_BW_Ena_Switch_CSC_CDC(unsigned char bw_ena);

void get_value_BW_Ena_Switch_CSC_CDC(unsigned char *bw_ena);

/*
 * set the matrix coef for RGB to YUV conversion
 * parameter list：
 * y_g:		RGB2YUV  matrix's coef :  Ky_g, 	 float, converted to u.0.8
 * y_b:		RGB2YUV  matrix's coef :  Ky_b, 	 float, converted to u.0.8
 * y_r:		RGB2YUV  matrix's coef :  Ky_r, 	 float, converted to u.0.8
 * cr_r:	RGB2YUV  matrix's coef :  Kcr_r,	 float, converted to u.0.8
 * cb_b:	RGB2YUV  matrix's coef :  Kcb_b,	 float, converted to u.0.8
 * cb_g:	RGB2YUV  matrix's coef :  Kcb_g,	 float, converted to s.0.8
 * cb_r:	RGB2YUV  matrix's coef :  Kcb_r,	 float, converted to s.0.8
 * cr_b:	RGB2YUV  matrix's coef :  Kcr_b,	 float, converted to s.0.8
 * cr_g:	RGB2YUV  matrix's coef :  Kcr_g,	 float, converted to s.0.8
 * */
void set_value_module_RGB2YUV_CSC_CDC(float y_g, float y_b, float y_r, float cr_r, float cb_b, float cb_g, float cb_r, float cr_b, float cr_g);

void get_value_module_RGB2YUV_CSC_CDC(unsigned char *y_g, unsigned char *y_b, unsigned char *y_r, unsigned char *cr_r, unsigned char *cb_b, short *cb_g, short *cb_r, short *cr_b, short *cr_g);

/*
 * set signal offset and knee gain
 * parameter list：
 * cr: 			Cr offset,
 * cb:			Cb offset
 * y:			  Y  offset
 * */
void set_value_offset_CSC_CDC(unsigned char cr, unsigned char cb, short y);

void get_value_offset_CSC_CDC(unsigned char *cr, unsigned char *cb, short *y);

/*
 * set y gain after histogram Statand threshold of Thres
 * parameter list：
 * y_gain：		y gain ， float，  converted to u.1.7
 * thres_l:		offset of luma adjust,  width: u.8.0
 * */
void set_value_Hist_Gain_CSC_CDC(float y_gain, unsigned char thres_l);
void get_value_Hist_Gain_CSC_CDC(unsigned char *y_gain, unsigned char *thres_l);

/*
 * set threshold of y in Cb /Cr Saturation， if(y>y_level) Cb=Cr=128
 * parameter list：
 * y_level：		u.9.0
 * */
void set_value_Y_Level_CSC_CDC(unsigned short y_level);

void get_value_Y_Level_CSC_CDC(unsigned short *y_level);

/*
 * set contrast adjust coef
 * parameter list：
 * ctr：	float ，u.4.4
 * */
void set_value_Ctr_CSC_CDC(float ctr);

void get_value_Ctr_CSC_CDC(unsigned char *ctr);

/*
 * set chroma  adjust coef
 * parameter list：
 * cos：		float，s.2.5
 * sin：		float，s.2.5
 * */
void set_value_Hue_CSC_CDC(float cos, float sin);

void get_value_Hue_CSC_CDC(char *cos, char *sin);

/*
 * set saturation adjust coef
 * parameter list：
 * sat：	float  ，u.3.5
 * */
void set_value_Sat_CSC_CDC(float sat);

void get_value_Sat_CSC_CDC(unsigned char *sat);

/*
 * set lum adjust coef
 * parameter list：
 * brt：		s.8.0
 * */
void set_value_Brt_CSC_CDC(short brt);

void get_value_Brt_CSC_CDC(short *brt);

#endif

