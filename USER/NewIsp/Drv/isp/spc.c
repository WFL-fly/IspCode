#include <stdio.h>
#include <string.h>
#include "spc.h"
#include "isp_utils.h"

static char s_inited = 0;
static unsigned char s_spc_version = 0;
static unsigned int s_spc_base_offset = 0x4000;

//SPC correction enable
void set_SPC_enable(unsigned char en)
{
	*(volatile unsigned char *)((SPC_BASE + COV_CHAR(s_spc_base_offset + SPC_ENABLE)) | (1 << 31)) = en;
}

//set SPC line ram offset
void set_SPC_line_ram_offset(unsigned char oft)
{
	*(volatile unsigned char *)((SPC_BASE + COV_CHAR(s_spc_base_offset + SPC_RAM_OFFSET)) | (1 << 31)) = oft;
}

//set bug sum
void set_SPC_bug_sum(unsigned short sum)
{

	*(volatile unsigned short *)((SPC_BASE + COV_SHORT(s_spc_base_offset + BUG_SUM)) | (1 << 31)) = sum;
}

//set offset origin
void set_SPC_origin(unsigned short H_origin, unsigned short V_origin)
{

	*(volatile unsigned short *)((SPC_BASE + COV_SHORT(s_spc_base_offset + H_ORIGIN)) | (1 << 31)) = H_origin;
	*(volatile unsigned short *)((SPC_BASE + COV_SHORT(s_spc_base_offset + V_ORIGIN)) | (1 << 31)) = V_origin;
}

//set bug location
void set_SPC_bug_location(unsigned short sum, unsigned int* buf)
{
	unsigned int i,j;
	unsigned int * bug_addr;

    if ((sum > 8191) || buf == NULL)
	{
		printf("spc set : invalid parameter(s)\n");
		return;
	}
    
	bug_addr = (unsigned int *)BUG_PARAM_RAM_BASE;

	for (i = 0,j = 0; i < sum; i++,j++)
	{
	    j = j > 4095 ? 1 : j;
		*(bug_addr + j) = *(buf + i);
	}
	*(bug_addr + j) = 0xffffffff;
}

void set_SPC_bug_cell(short addr, char type, short x, short y)
{
	*(unsigned int *)(BUG_PARAM_RAM_BASE + (addr)) = (type << 28) + (y << 14) + x;
}

unsigned short get_SPC_bug_sum(void)
{
	return *(volatile unsigned short *)((SPC_BASE + COV_SHORT(s_spc_base_offset + BUG_SUM)) | (1 << 31));
}

unsigned char get_SPC_version(void)
{
	unsigned int readValue = 0;
	
	if (!s_inited)
	{
		readValue = *(volatile unsigned int *)(VISP_BASE + 0x0024);
	
		if ((readValue & 0xFFFF) == 0x1001)
		{
			s_spc_version = 1;
		}
		else if ((readValue & 0xFFFF) == 0x2001)
		{
			s_spc_version = 2;
		}
		s_inited = 1;
	}

	return s_spc_version;
	
}

void set_SPC_sensortype(unsigned int sensorType)
{
	unsigned int readValue = 0;

	readValue = *(volatile unsigned int *)(SPC_BASE + s_spc_base_offset + 0x0008);
	readValue = readValue & 0xFEFFFFFF;//bit24
	
	*(volatile unsigned int *)((SPC_BASE + s_spc_base_offset + 0x0008) | (1 << 31)) = (readValue | sensorType<<24);
} 

void set_image_height(unsigned int height)
{
	unsigned int readValue = 0;
	
	readValue = *(volatile unsigned int *)(SPC_BASE + s_spc_base_offset + 0x0008);
	readValue = readValue & 0xFFFFC000;//bit13-bit0
		
	*(volatile unsigned int *)((SPC_BASE + s_spc_base_offset + 0x0008) | (1 << 31)) = (readValue | height);
}

void set_badColum_sum(unsigned short sum)
{
	unsigned int readValue = 0;
	
	readValue = *(volatile unsigned int *)(SPC_BASE + s_spc_base_offset + 0x0008);
	readValue = readValue & 0xFF00FFFF;//bit23-bit16
		
	*(volatile unsigned int *)((SPC_BASE + s_spc_base_offset + 0x0008) | (1 << 31)) = (readValue | sum <<16);
}

void set_badColumn_bug_loaction(unsigned short sum,unsigned short *buf)
{
	unsigned short i = 0;
	unsigned int *badCol_bug_addr;

	if ((sum > 32) || (buf == NULL))
	{
		printf("badColumn set : invalid parameter(s)\n");
	}

	badCol_bug_addr = (unsigned int *)BADCOLUMN_PARAM_RAM_BASE;

	for (i = 0; i < sum; i++)
	{
		*(badCol_bug_addr + i) = *(buf + i);
	}

	*(badCol_bug_addr + i) = 0xffffffff;
}
