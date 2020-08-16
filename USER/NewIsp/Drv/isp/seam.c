#include <stdio.h>
#include <string.h>
#include "seam.h"

void set_fixed_value_Data_Seam(unsigned int count)
{
	int i;
	volatile unsigned int *ram_addr = NULL;

	ram_addr = SEAM_Param_Base;
	
	for(i = 0; i < (int)count; i++)
	{
		*(ram_addr + i) = 0x04000000;//k:1.0,b:0
	} 
	
}

void set_value_Data_Seam(unsigned int *data, unsigned int count)
{
    int i;
    volatile unsigned int *ram_addr = NULL;
    unsigned int ptrValue = 0;
    
    ram_addr = SEAM_Param_Base;
    
    for(i = 0; i < (int)count; i++)
	{
        ptrValue = *(data + i);
		//*(ram_addr + i) = MEM_LE2BE_INT(ptrValue);
		*(ram_addr + i) = (ptrValue);
	} 
    
}
void set_value_Sync_Seam(unsigned char enable)
{
    if (enable) //pinp立即生效
    {
        SEAM_Switch |= 0x8; 
    }
    else    //pinp下帧生效
    {
        SEAM_Switch &= 0xfffffff7; 
    }
}

void set_value_Pinp_Seam(unsigned char enable)
{
    if (enable) 
    {
        SEAM_Switch |= 0x2; 
    }
    else //写
    {
        SEAM_Switch &= 0xfffffffd; 
    }
}


