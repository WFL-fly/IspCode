#ifndef _RGB2RAW_H_
#define _RGB2RAW_H_

/*
 * define the register name  of  RGB2RAW module
 *
 * RGB2RAW_BASE		base address of RGB2RAW module
 * RGB2RAW_RB_horizontal:   RB_horizontal
 * RGB2RAW_RB_vertical:     RB_vertical
 * */

#include "isp_base.h"

#define RGB2RAW_BASE ISP_2RAW_BASE
#define RGB2RAW_RB_horizontal *(volatile unsigned char *) ((RGB2RAW_BASE + COV_CHAR(0x00)) | (1 << 31))
#define RGB2RAW_RB_vertical *(volatile unsigned char *) ((RGB2RAW_BASE + COV_CHAR(0x02)) | (1 << 31))



/*
 * set, get and init value for ENHANCE module
 * */
//init RGB2RAW module
void INIT_RGB2RAW(void);

/*
 * set RB_horizontal,  if(RB_horizontal=1) :R line (default)
 *				   if(Rb_horizontal=0): B line
 * parameter list:
 * rb_horizontal:	Rb_horizontal
 * */
void set_value_RB_horizontal_RGB2RAW(unsigned char rb_horizontal);

void get_value_RB_horizontal_RGB2RAW(unsigned char *rb_horizontal);

/*
 * set RB_vertical,  if(RB_vertical=1) : B col (default)
 *				   if(Rb_vertical=0): R col
 * parameter list:
 * rb_vertical:	Rb_vertical
 * */
void set_value_RB_vertical_RGB2RAW(unsigned char rb_vertical);

void get_value_RB_vertical_RGB2RAW(unsigned char *rb_vertical);


#endif
