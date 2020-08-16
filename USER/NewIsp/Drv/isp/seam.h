#ifndef SEAM_H_
#define SEAM_H_
#include "sys.h"

#if defined(XILINX_FPGA)
	//xilinx不支持该功能，定义无效地址
	#define SEAM_Param_Base		(INVALID_BASE)
#else
	#define SEAM_Param_Base		(0x8E000000)
#endif


#define SEAM_Switch			*(volatile unsigned   int *)((SEAM_Param_Base + 0xD90)|(1<<31)) 
#define MEM_LE2BE_INT(x) ((((unsigned int)(x) & 0x000000ff) << 24) | (((unsigned int)(x) & 0x0000ff00) << 8 ) | (((unsigned int)(x) & 0x00ff0000) >> 8) | (((unsigned int)(x) & 0xff000000) >> 24)) 

void set_fixed_value_Data_Seam(unsigned int count);
void set_value_Data_Seam(unsigned int *data, unsigned int count);
void set_value_Sync_Seam(unsigned char enable);
void set_value_Pinp_Seam(unsigned char enable);

#endif 
