#ifndef _AWB_STATICS_H_
#define _AWB_STATICS_H_

#include <sys/_stdint.h>
#include "isp_base.h"


/* define register name of AWB stastic module
 *
 * ST_AWB_BASE:				base address of	AWB statistics module
 * ST_AWB_RAM_Copy_Flag:	flag of RAM copy
 * ST_AWB_Block_Size:		sampling block size
 * ST_AWB_Ky_R:				KY_r:parameter for RGB to YUV conversion
 * ST_AWB_Ky_B:				Ky_b:parameter for RGB to YUV conversion
 * ST_AWB_Start_X:			Stat region's start position on x axis
 * ST_AWB_Start_Y:			Stat region's start position on y axis
 * ST_AWB_End_X：			Stat region's end position on x axis
 * ST_AWB_End_Y：			Stat region's end position on y axis
 * */

#define ST_AWB_BASE ISP_AWE_BASE

#define ST_AWB_RAM_Copy_Flag *(volatile unsigned char *)((ST_AWB_BASE + COV_CHAR(0x00)) | (1 << 31))
#define ST_AWB_Block_Size *(volatile unsigned char *)((ST_AWB_BASE + COV_CHAR(0x04)) | (1 << 31))
#define ST_AWB_Ky_R *(volatile unsigned char *)((ST_AWB_BASE + COV_CHAR(0x08)) | (1 << 31))
#define ST_AWB_Ky_B *(volatile unsigned char *)((ST_AWB_BASE + COV_CHAR(0x0A)) | (1 << 31))
#define ST_AWB_Start_X *(volatile unsigned short *)((ST_AWB_BASE + COV_SHORT(0x0C)) | (1 << 31))
#define ST_AWB_Start_Y *(volatile unsigned short *)((ST_AWB_BASE + COV_SHORT(0x0E)) | (1 << 31))
#define ST_AWB_End_X *(volatile unsigned short *)((ST_AWB_BASE + COV_SHORT(0x10)) | (1 << 31))
#define ST_AWB_End_Y *(volatile unsigned short *)((ST_AWB_BASE + COV_SHORT(0x12)) | (1 << 31))
#define ST_AWB_ENABLE *(volatile unsigned int *)((ST_AWB_BASE + 0x14) | (1 << 31))

/*
 * set, get and init value for AWB stastic module
 * */
//init ST_AWB module
void INIT_ST_AWB(void);

/*
 * flag if statistic data copy has completed
 * 1:module is copying and cpu can't read the value from ram
 * 0:cpu can read the value from ram
 * parameter list：
 * ram_copy_flag:		flag
 * */
void set_value_RAM_Copy_Flag_ST_AWB(unsigned char ram_copy_flag);
void get_value_RAM_Copy_Flag_ST_AWB(unsigned char *ram_copy_flag);

/*
 * set and get the sampling block size
 *
 */
void set_value_Block_Size_ST_AWB(unsigned char block_size);
void get_value_Block_Size_ST_AWB(unsigned char *block_size);

/*
 * set parameters for RGB to YUV conversion
 *  parameter list：
 * ky_r:		parameter for Y -> R conversion, float input ，which is then converted to u.0.8
 * ky_b:		parameter for Y -> B conversion，float input,  which is then converted to u.0.8
 * */
void set_value_Ky_RB_ST_AWB(float ky_r, float ky_b);
void get_value_Ky_RB_ST_AWB(unsigned char *ky_r, unsigned char *ky_b);

/*
 * set rect of region for Stat
 * parameter list：
 * start_x:		Stat region's start position on x axis
 * start_y:		Stat region's start position on y axis
 * end_x:		  Stat region's end position on x axis
 * end_y:		  Stat region's end position on y axis
 * */
void set_value_Start_XY_ST_AWB(unsigned short start_x, unsigned short start_y, unsigned short end_x, unsigned short end_y);
void get_value_Start_XY_ST_AWB(unsigned short *start_x, unsigned short *start_y, unsigned short *end_x, unsigned short *end_y);

void enable_ST_AWB(void);
void disable_ST_AWB(void);

void get_data_ST_AWB(uint32_t *data, uint32_t count);

#endif
