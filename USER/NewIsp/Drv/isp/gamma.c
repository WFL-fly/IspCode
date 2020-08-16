#include "gamma.h"
#include "isp.h"
#include "isp_utils.h"

//set, get and init value for GAMMA module

static int s_table_size = 0;

void set_value_DATA_GAMMA(int *gamma_data, int count)
{
	s_table_size = count;
	
    short i = 0;

	for (i = 0; i < count; i++)
    {
        *(GAMMA_RAM_BASE + i) = (*(gamma_data + i));
        	//printf("[%d]=[%d]\t",i, *(GAMMA_RAM_BASE+i) );
    }
}

void get_value_DATA_GAMMA(int *gamma_data, short i)
{
    *gamma_data = *(GAMMA_RAM_BASE + i);
}

void disable_GAMMA(void)
{
	if (s_table_size == 1024)
	{
		*(volatile unsigned int *)(GAMMA_BASE + 0x1000) = 0x80000000;
	}
	else if (s_table_size == 4096)
	{
		*(volatile unsigned int *)(GAMMA_BASE + 0x4000) = 0x80000000;
	}
	disableIspModel(ISP_LUT2D);
}

void enable_GAMMA(void)
{
	if (s_table_size == 1024)
	{
		*(volatile unsigned int *)(GAMMA_BASE + 0x1000) = 0;
	}
	else if (s_table_size == 4096)
	{
		*(volatile unsigned int *)(GAMMA_BASE + 0x4000) = 0;
	}
	enableIspModel(ISP_LUT2D);
}
