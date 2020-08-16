#include <string.h>
#include "sys.h"
#include "isp.h"
#include "sta.h"

void set_STA_en(uint8_t enable)
{
	Adjust_en = enable;
}

void set_STA_Param(unsigned short strX, unsigned short strY, unsigned short endX, unsigned short endY)
{
    unsigned int readValue = 0;

    readValue = Start_X;
    Start_X = (readValue & 0xFFFFE000) | strX;

    readValue = Start_Y;
    Start_Y = (readValue & 0xFFFFE000) | strY;

    readValue = End_X;
    End_X = (readValue & 0xFFFFE000) | endX;

    readValue = End_Y;
    End_Y = (readValue & 0xFFFFE000) | endY;
}

uint16_t get_STA_hist_aver(void)
{
	unsigned int pixels, sta_total;

//	if (SENSOR_TYPE == SENSOR_COLOR)
//	{
//		return STA_TOTAL;
//	}
	
	pixels = PIXEL_SUM;
	sta_total = STA_TOTAL;

	if (PIXEL_SUM == 0)
	{
		return 0;
	}

	return sta_total / pixels;
}

int get_STA_hist_pixelsum(void)
{

	return PIXEL_SUM;
}


int Y_adj_lut_conf(int *adj_ram_256x9, int count)
{
	int i;
	unsigned char shiftBits;
	volatile unsigned long *sta_data = DATA_BASE_STA; //0x000

	if (g_driverConfig.sensorType == SENSOR_COLOR)
	{
		shiftBits = 20;
	}
	else
	{
		shiftBits = 16;
	}

	for (i = 1; i < count - 1; i = i + 2)
	{
		*sta_data = ((*(adj_ram_256x9 + i + 1)) << shiftBits) + (*(adj_ram_256x9 + i));
		sta_data++;
	}
	*sta_data = ((*(adj_ram_256x9 + i)) << shiftBits) + (*(adj_ram_256x9 + i));

	return 0;
}

void get_hist(int *hist, int count)
{
	int i;

	unsigned int offset;

	if (g_driverConfig.sensorType == SENSOR_COLOR)
	{
		offset = 0x400;
	}
	else
	{
		offset = 0x1000;
	}

	unsigned long *hist_data = (unsigned long *)((ISP_STAMEM_BASE + offset) | (1ul << 31));

	for (i = 0; i < count; i++)
	{
		hist[i] = hist_data[i];
	}
	//memcpy(hist, hist_data, count * 4);
}

void set_Ctr(float ctr)
{
	STA_CTR = FLOTOFIX(unsigned char, 4, ctr);
}
