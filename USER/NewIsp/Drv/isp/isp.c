#include <stdio.h>
#include <sys/_stdint.h>
//#include "logmodule.h"
#include "isp_utils.h"
#include "sys.h"
#include "isp.h"


void IspApplyParameters(void)
{
	IOWR_PIO_SET_BITS(PIO_BASE, PIO_SENSOR_V_SYNC);
	IOWR_PIO_CLEAR_BITS(PIO_BASE, PIO_SENSOR_V_SYNC);
}

#define ISP_CHANNEL_NUM	*(volatile unsigned int *)((ISP_VER_BASE + 0x0C) | (1 << 31))
#define ISP_BYPASS *(volatile uint32_t *)((ISP_VER_BASE + 0x10) | (1 << 31))

unsigned short getIspChannel(void)
{
	return (ISP_CHANNEL_NUM & 0xFFFF);
}

void disableIspModel(uint32_t model)
{
	uint32_t bypassReg;

	bypassReg = ISP_BYPASS;
	bypassReg |= 1ul << model;
	ISP_BYPASS = bypassReg;
}

void enableIspModel(uint32_t model)
{
	uint32_t bypassReg;

	bypassReg = ISP_BYPASS;
	bypassReg &= ~(1ul << model);
	ISP_BYPASS = bypassReg;
}

/*
 * 图像模式配置
 * sensor_mode : 0:mono sensor, 1:color sensor
 * out_type :pixelformat,
 */
/*
	+ ----------- + -------------- + ------------------- + ------------------------------ +
	|  data_sel   |   00 : RAW     |   01 : RGB          |  10 : YUV                      |
	+ ----------- + -------------- + ------------------- + ------------------------------ +
	|  mode_sel   |   01 : const   |   00 : rgb-->rgb;   |  00 : yuv444-->CbYCr / UYV     |
	|             |                |   01 : rgb-->bgr;   |  01 : yuv422-->UYVY            |
	|             |                |                     |  10 : yuv422-->YUYV    ,Y高位  |
	|             |                |                     |  11 : yuv411-->CbYYCrYY        |
	|             |                |                     |       U1,Y1[3:0]; Y2,Y1[7:4];  |
	|             |                |                     |       V1,Y3[3:0]; Y4,Y3[7:4];  |
	+ ----------- + -------------- + ------------------- + ------------------------------ +
	|  width_sel  |   00 : 8 bit;  |   00 : 8 bit;       |  00 : 8 bit;                   |
	|             |   01 : 10bit;  |   01 : 10bit;       |                                |
	|             |   10 : 12bit;  |                     |                                |
	+ ----------- + -------------- + ------------------- + ------------------------------ +
	 ISP_OMODE_BASE :VISP+0x0400
	 MSB_SEL    ISP_OMODE_BASE + COV_CHAR(0x3)) 
     DATA_SEL   ISP_OMODE_BASE + COV_CHAR(0x2)) 
     MODE_SEL   ISP_OMODE_BASE + COV_CHAR(0x1))
     WIDTH_SEL  ISP_OMODE_BASE + COV_CHAR(0x0))
     OUTPUT_MASK	  ISP_OMODE_BASE + 0x04) 
 */

static pixelFormatSetting colorSettings[] = 
{
	/* Pixel Format				msb		data	mode	width */
	{ ISP_PIX_MONO8,			1,		2,		1,		0 },
	{ ISP_PIX_BAYRG8,			1,		0,		1,		0 },
	{ ISP_PIX_BAYRG12,			1,		0,		1,		2 },
	{ ISP_PIX_BAYRG12_PACKED,	1,		0,		1,		2 },
	{ ISP_PIX_BAYRG10,			1,		0,		1,		1 },
	{ ISP_PIX_BAYRG10_PACKED,	1,		0,		1,		1 },
	{ ISP_PIX_RGB8,				1,		1,		1,		0 },
	{ ISP_PIX_YUV422_8_UYVY,	1,		2,		2,		0 },
	{ ISP_PIX_YUV422_8,			1,		2,		1,		0 },
	{ ISP_PIX_BAYGB8,			1,		0,		1,		0 },
	{ ISP_PIX_BAYGB12,			1,		0,		1,		2 },
	{ ISP_PIX_BAYGB12_PACKED,	1,		0,		1,		2 },
	{ ISP_PIX_BAYGB10,			1,		0,		1,		1 },
	{ ISP_PIX_BAYGB10_PACKED,	1,		0,		1,		1 },
	{ ISP_PIX_BAYGR8,			1,		0,		1,		0 },
	{ ISP_PIX_BAYGR12,			1,		0,		1,		2 },
	{ ISP_PIX_BAYGR12_PACKED,	1,		0,		1,		2 },
	{ ISP_PIX_BAYGR10,			1,		0,		1,		1 },
	{ ISP_PIX_BAYGR10_PACKED,	1,		0,		1,		1 },
	{ ISP_PIX_BAYBG8,			1,		0,		1,		0 },
	{ ISP_PIX_BAYBG12,			1,		0,		1,		2 },
	{ ISP_PIX_BAYBG12_PACKED,	1,		0,		1,		2 },
	{ ISP_PIX_BAYBG10,			1,		0,		1,		1 },
	{ ISP_PIX_BAYBG10_PACKED,	1,		0,		1,		1 }
};

static pixelFormatSetting monoSettings[] = 
{
	/* Pixel Format				msb		data	mode	width */
	{ ISP_PIX_MONO4P,			1,		0,		2,		3 },
	{ ISP_PIX_MONO8,			1,		0,		1,		0 },
	{ ISP_PIX_MONO12,			1,		0,		0,		2 },
	{ ISP_PIX_MONO12_PACKED,	1,		0,		0,		2 },
	{ ISP_PIX_MONO10,			1,		0,		1,		1 },
	{ ISP_PIX_MONO10_PACKED,	1,		0,		1,		1 },
	{ ISP_PIX_YUV422_8_UYVY,	1,		2,		2,		0 },
	{ ISP_PIX_YUV422_8,			1,		2,		1,		0 }
};

/*彩转黑，输出mono8格式*/
static pixelFormatSetting colorTransmonoSettings[] = 
{
	{ ISP_PIX_MONO8,			1,		0,		0,		0 }
};

void IspSetOutputMode(uint8_t sensorMode, uint8_t colorTransMono, uint32_t outType)
{
	uint8_t i;
	pixelFormatSetting setting;
	
	setting.rawMsb = 0;
	setting.dataSel = 2;
	setting.modeSel = 2;
	setting.widthSel = 0;

	if (sensorMode)	//color
	{
		if (outType == ISP_PIX_MONO8)
		{
			set_value_BW_Ena_Switch_CSC_CDC(1);
		}
		else
		{
			set_value_BW_Ena_Switch_CSC_CDC(0);
		}

		if (colorTransMono)
		{
			for (i = 0; i < COUNTOF(colorTransmonoSettings); i++)
			{
				if (colorSettings[i].pixelFormat == outType)
				{
					setting = colorTransmonoSettings[i];
					break;
				}
			}
		}
		else
		{
			for (i = 0; i < COUNTOF(colorSettings); i++)
			{
				if (colorSettings[i].pixelFormat == outType)
				{
					setting = colorSettings[i];
					break;
				}
			}
		}
		
	}
	else	//mono
	{
		set_value_BW_Ena_Switch_CSC_CDC(1);

		for (i = 0; i < COUNTOF(monoSettings); i++)
		{
			if (monoSettings[i].pixelFormat == outType)
			{
				setting = monoSettings[i];
				break;
			}
		}
	}

	if (colorTransMono)
	{
		MSB_SEL = setting.rawMsb;
	}
	DATA_SEL = setting.dataSel;
	MODE_SEL = setting.modeSel;
	WIDTH_SEL = setting.widthSel;

	IspApplyParameters();
}

void IspInitOutputMode(uint8_t mono8Path, uint8_t rawMsb)
{
	uint8_t i;

	for (i = 0; i < COUNTOF(colorSettings); i++)
	{
		if (colorSettings[i].pixelFormat == ISP_PIX_MONO8)
		{
			colorSettings[i].rawMsb = rawMsb;

			if (mono8Path == 0)
			{
				colorSettings[i].dataSel = 0;
				colorSettings[i].modeSel = 1;
				colorSettings[i].widthSel = 0;
			}
			else
			{
				colorSettings[i].dataSel = 2;
				colorSettings[i].modeSel = 1;
				colorSettings[i].widthSel = 0;
			}
			break;
		}
	}

	for (i = 0; i < COUNTOF(monoSettings); i++)
	{
		if (monoSettings[i].pixelFormat == ISP_PIX_MONO8)
		{
			monoSettings[i].rawMsb = rawMsb;

			if (mono8Path == 0)
			{
				monoSettings[i].dataSel = 0;
				monoSettings[i].modeSel = 1;
				monoSettings[i].widthSel = 0;
			}
			else
			{
				monoSettings[i].dataSel = 2;
				monoSettings[i].modeSel = 1;
				monoSettings[i].widthSel = 0;
			}
			break;
		}
	}
}

#define BINNING_REG *(volatile uint32_t *)((ISP_BINNING_BASE) | (1 << 31))
#define BINNING_WIDTH_REG *(volatile uint32_t *)((ISP_BINNING_BASE + 4) | (1 << 31))
#define BINNING_COLOR_REG *(volatile uint32_t *)((ISP_BINNING_BASE) | (1 << 31))

void IspSetBinning(int x, int y, unsigned int width)
{
	uint32_t regValue = 0;

	if (x)
	{
		regValue |= (1ul << 0);
	}
	else
	{
		regValue &= ~(1ul << 0);
	}

	if (y)
	{
		regValue |= (1ul << 1);
	}
	else
	{
		regValue &= ~(1ul << 1);
	}

	//binning 使用求和模式
	//regValue |= (1ul << 8);

	BINNING_WIDTH_REG = width;
	BINNING_REG = regValue;	
}

/************************************************************************************
*函数名: IspSetColorBinning
*描     述:enable         :  0:关;1:开
*			mode          :  2:2*2类型; 3:3*3类型
*			img_rg_flag :  1:当前图像起始行为R行; 0:当前图像起始行为B行		     
*			bin_dir	     :  0:只Y方向Binning; 1:只X方向Binning; 2: XY方向都Binning
************************************************************************************/

void IspSetColorBinning(uint8_t enable, uint8_t mode, uint8_t img_rb_flag, uint8_t bin_dir)
{
	uint32_t regValue = 0;
	regValue |= (enable & 0x1);
	regValue |= ((mode & 0x3)<< 8);
	regValue |= ((img_rb_flag & 0x1)<< 16);
	regValue |= ((bin_dir & 0x3)<< 24);

	BINNING_COLOR_REG = regValue;
}

void IspSetOutputMask(uint32_t mask)
{
	OUTPUT_MASK = mask;
}

uint32_t IspGetOutputMask(void)
{
	return OUTPUT_MASK;
}

void getIspSkipData(uint32_t *value)
{
	*value = SKIP_ISP_ADDR;
}

void setIspSkip(uint32_t value)
{
	SKIP_ISP_ADDR = value;
}

void getStaticCorrectSkipData(uint32_t *value)
{
	*value = SKIP_STATIC_CORRECT_ADDR;
}

void setStaticCorrectSkip(uint32_t value)
{
	SKIP_STATIC_CORRECT_ADDR = value;
}

