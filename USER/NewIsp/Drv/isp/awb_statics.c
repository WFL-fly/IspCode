#include "isp_utils.h"
#include "awb_statics.h"

/*
 * set, get and init value for stastical AWB module
 * */

void INIT_ST_AWB(void)
{
	ST_AWB_RAM_Copy_Flag = 0x00;
	ST_AWB_Block_Size = 0x01;
	ST_AWB_Ky_R = 0x4C;
	ST_AWB_Ky_B = 0x1D;
	ST_AWB_Start_X = 0x0000;
	ST_AWB_Start_Y = 0x0000;
	ST_AWB_End_X = 0x0FFF;
	ST_AWB_End_Y = 0x0FFF;

	enable_ST_AWB();
}

void set_value_RAM_Copy_Flag_ST_AWB(unsigned char ram_copy_flag)
{
	ST_AWB_RAM_Copy_Flag = ram_copy_flag;
}

void get_value_RAM_Copy_Flag_ST_AWB(unsigned char *ram_copy_flag)
{
	*ram_copy_flag = ST_AWB_RAM_Copy_Flag;
}

void set_value_Block_Size_ST_AWB(unsigned char block_size)
{
	ST_AWB_Block_Size = block_size;
}

void get_value_Block_Size_ST_AWB(unsigned char *block_size)
{
	*block_size = ST_AWB_Block_Size;
}

void set_value_Ky_RB_ST_AWB(float ky_r, float ky_b)
{
	ST_AWB_Ky_R = FLOTOFIX(unsigned char, 8, ky_r);
	ST_AWB_Ky_B = FLOTOFIX(unsigned char, 8, ky_b);
}

void get_value_Ky_RB_ST_AWB(unsigned char *ky_r, unsigned char *ky_b)
{
	*ky_r = ST_AWB_Ky_R;
	*ky_b = ST_AWB_Ky_B;
}

void set_value_Start_XY_ST_AWB(unsigned short start_x, unsigned short start_y, unsigned short end_x, unsigned short end_y)
{
	ST_AWB_Start_X = start_x;
	ST_AWB_Start_Y = start_y;
	ST_AWB_End_X = end_x;
	ST_AWB_End_Y = end_y;
}

void get_value_Start_XY_ST_AWB(unsigned short *start_x, unsigned short *start_y, unsigned short *end_x, unsigned short *end_y)
{
	*start_x = ST_AWB_Start_X;
	*start_y = ST_AWB_Start_Y;
	*end_x = ST_AWB_End_X;
	*end_y = ST_AWB_End_Y;
}

void enable_ST_AWB(void)
{
	ST_AWB_ENABLE = 1;
}

void disable_ST_AWB(void)
{
	ST_AWB_ENABLE = 0;
}

void get_data_ST_AWB(uint32_t *data, uint32_t count)
{
	int i;

	uint32_t *st_data = (uint32_t *)(ISP_AWEMEM_BASE | (1 << 31));

	for (i = 0; i < count; i++)
	{
		data[i] = st_data[i];
		data[i + 2048] = st_data[i + 2048];
	}
}