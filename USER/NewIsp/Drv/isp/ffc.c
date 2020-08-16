#include <stdio.h>
#include <string.h>
#include "sys.h"
#include "ffc.h"
#include "isp.h"

void set_ffc_data_info(unsigned int baseAddr, unsigned int len, unsigned int RD_width)
{
    FFC_DATA_BASE_ADDR = (baseAddr >> 16) & 0xffff;;
    FFC_DATA_LEN_ADDR = len;
    FFC_BUF_RD_WIDTH_ADDR = RD_width;
}

void set_ffc_enable(unsigned int enable)
{
	if(0 != enable)
    {
		FFC_ENABLE_ADDR = 1;
	}
    else
    {
		FFC_ENABLE_ADDR = 0;
	}
}

void set_ffc_size(unsigned short width, unsigned short heigth)
{
	FFC_HEIGTH_ADDR = heigth&0xffff;
	FFC_WIDTH_ADDR = width&0xffff;
}

void get_ffc_SkipIsp(unsigned int *ffc_enable, unsigned int *skip_data)
{
	*ffc_enable = FFC_ENABLE_ADDR;
	*skip_data = SKIP_ISP_ADDR;
}

void set_ffc_SkipIsp(unsigned int ffc_enable, unsigned int skip_data)
{
	FFC_ENABLE_ADDR = ffc_enable;
	SKIP_ISP_ADDR = skip_data;
}


