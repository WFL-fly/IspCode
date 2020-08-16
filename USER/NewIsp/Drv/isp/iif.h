#ifndef _IIF_H_
#define _IIF_H_

#include "isp.h"
#include "isp_base.h"

/* 采集模式配置 */
/**********
 * VI_RPG_valid 
 *   bit0: test image enable 
 *   bit1: flip x enable 
 *   bit2: 0 - static test image 
 *         1 - dynamic test image 
 *   bit3: 0 - bayer test image 
 *         1 - mono test image 
 *   bit4: 0 - cut last line when flipping 
 *         1 - don't cut and copy last line. 
**********/
#define VI_BASE ISP_IIF_BASE

#define VI_H_Size *(volatile unsigned short *) ((VI_BASE + COV_SHORT(0x00)) | (1 << 31))
#define VI_V_Size *(volatile unsigned short *) ((VI_BASE + COV_SHORT(0x02)) | (1 << 31))
#define VI_H_Dummy *(volatile unsigned short *) ((VI_BASE + COV_SHORT(0x04)) | (1 << 31))
#define VI_V_Dummy *(volatile unsigned short *) ((VI_BASE + COV_SHORT(0x06)) | (1 << 31))
#define VI_H_Size_Valid *(volatile unsigned short *) ((VI_BASE + COV_SHORT(0x08)) | (1 << 31))
#define VI_V_Size_Valid *(volatile unsigned short *) ((VI_BASE + COV_SHORT(0x0A)) | (1 << 31))
#define VI_R_B_Flag *(volatile unsigned char *) ((VI_BASE + COV_CHAR(0x0C)) | (1 << 31))
#define VI_RPG_valid *(volatile unsigned char *) ((VI_BASE + COV_CHAR(0x0D)) | (1 << 31))//IIF test img 
#define VI_Ram_RD_Start *(volatile unsigned short *) ((VI_BASE + COV_SHORT(0x0E)) | (1 << 31))
#define VI_V_TYPE *(volatile unsigned char *) ((VI_BASE + COV_CHAR(0x14)) | (1 << 31))
#define INPUT_MASK *(volatile unsigned int *) ((VI_BASE + 0x10) | (1 << 31))
#define SENSOR_R_B_FLAG *(volatile unsigned int *) ((VISP_BASE + 0x700) | (1 << 31))

typedef struct tagIspIifConfig
{
	short hsize_all;
	short vsize_all;
	short hsize_valid;
	short vsize_valid;
	short h_start;
	short v_start;
	char rb_flag;
	char default_rb;
	char reverse_rb;
	char v_type;
	char is_odd_offset;

	unsigned char reserved[7];
} IspIifConfig;

void iif_conf(IspIifConfig* iifConfig);
unsigned int iif_get_mask(void);
void iif_set_mask(unsigned int mask);
void iif_set_width_All(unsigned short width);
void iif_set_height_All(unsigned short height);
void iif_set_width_Dummy(unsigned short width);
void iif_set_height_Dummy(unsigned short height);
void iif_set_width_Valid(unsigned short width);
void iif_set_height_Valid(unsigned short height);
void iif_set_R_B_Flag(unsigned char rb_flag);
void iif_set_V_Type(unsigned char v_type);
void iif_set_flipX(unsigned char flipX);
void setIIFRPG(unsigned char enable);
void iif_set_flipx_cut(unsigned char enable);



#endif
