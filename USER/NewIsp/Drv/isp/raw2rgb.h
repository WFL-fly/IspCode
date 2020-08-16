#ifndef _RAW2RGB_H_
#define _RAW2RGB_H_

/*
 * define the register name  of  RAW2RGB module
 *
 * RAW2RGB_BASE：		base address of RAW2RGB module
 * RAW2RGB_Level:		used to elimate symbol placement of input by argumenting raw data
 * RAW2RGB_RB_invert:	Rb_invert
 * RAW2RGB_Sel_Mode: 	mode select
 * RAW2RGB_COLOR_MONO_Mode:=1, 黑白模式R=G=B， =0， 彩色
 * */

#include "isp_base.h"

#define RAW2RGB_BASE ISP_2RGB_BASE
#define RAW2RGB_Level *(volatile unsigned char *) ((RAW2RGB_BASE + COV_CHAR(0x00)) | (1 << 31))
#define RAW2RGB_RB_invert *(volatile unsigned char *) ((RAW2RGB_BASE + COV_CHAR(0x02)) | (1 << 31))
#define RAW2RGB_Sel_Mode *(volatile unsigned char *) ((RAW2RGB_BASE + COV_CHAR(0x03)) | (1 << 31))
#define RAW2RGB_COLOR_MONO_Mode *(volatile unsigned char *) ((RAW2RGB_BASE + COV_CHAR(0x04)) | (1 << 31))

/*
 * set, get and init value for ENHANCE module
 * */
//init RAW2RGB module
void INIT_RAW2RGB(void);

/*
* set sensor_mode for cfa,=1, 黑白模式R=G=B， =0， 彩色
* */
void set_color_mono_mode_RAW2RGB(unsigned char sensor_mode);

/*
 * set level ,used to elimate symbol placement of input by argumenting raw data
 * parameter list:
 * level:	level
 * */
void set_value_Level_RAW2RGB(unsigned char level);

void get_value_Level_RAW2RGB(unsigned char *level);

/*
 * set Rb_invert,  if(Rb_invert=0,rb_flag=1) :R line (default)
 *				   if(Rb_invert=1,rb_flag =1) : B line
 * parameter list:
 * rb_invert:	Rb_invert
 * */
void set_value_RB_invert_RAW2RGB(unsigned char rb_invert);

void get_value_RB_invert_RAW2RGB(unsigned char *rb_invert);

/*
 * set Sel_Mode, 1:select R when G rebirth ;	0:don't select R
 * parameter list:
 * sel_mode:	mode_sel
 * */
void set_value_Sel_Mode_RAW2RGB(unsigned char sel_mode);

void get_value_Sel_Mode_RAW2RGB(unsigned char *sel_mode);

#endif
