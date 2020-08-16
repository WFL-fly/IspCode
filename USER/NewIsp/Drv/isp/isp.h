#ifndef _ISP_H_
#define _ISP_H_

#include "wb.h"
#include "ccm.h"
#include "awb_statics.h"
#include "ee_driver.h"
#include "gamma.h"
#include "raw2rgb.h"
#include "rgb2yuv.h"
#include "rgb2raw.h"
#include "spc.h"
#include "ffc.h"
//#include "types.h"
#include <sys/_stdint.h>
#include "iif.h"
#include "dgc.h"
#include "filter.h"
#include "boc.h"
#include "sta.h"
#include "alg_aew.h"
#include "wdr.h"

//===================================================
// PIXEL FORMATS
//===================================================
// Indicate if pixel is monochrome or RGB
#define ISP_PIX_MONO 0x01000000
#define ISP_PIX_RGB 0x02000000 // deprecated in version 1.1
#define ISP_PIX_COLOR 0x02000000
#define ISP_PIX_CUSTOM 0x80000000
#define ISP_PIX_COLOR_MASK 0xFF000000
// Indicate effective number of bits occupied by the pixel (including padding).
// This can be used to compute amount of memory required to store an image.
#define ISP_PIX_OCCUPY1BIT 0x00010000
#define ISP_PIX_OCCUPY2BIT 0x00020000
#define ISP_PIX_OCCUPY4BIT 0x00040000
#define ISP_PIX_OCCUPY8BIT 0x00080000
#define ISP_PIX_OCCUPY12BIT 0x000C0000
#define ISP_PIX_OCCUPY16BIT 0x00100000
#define ISP_PIX_OCCUPY24BIT 0x00180000
#define ISP_PIX_OCCUPY32BIT 0x00200000
#define ISP_PIX_OCCUPY36BIT 0x00240000
#define ISP_PIX_OCCUPY48BIT 0x00300000
#define ISP_PIX_EFFECTIVE_PIXEL_SIZE_MASK 0x00FF0000
#define ISP_PIX_EFFECTIVE_PIXEL_SIZE_SHIFT 16
// Pixel ID: lower 16-bit of the pixel formats
#define ISP_PIX_ID_MASK 0x0000FFFF
#define ISP_PIX_COUNT 0x46 // next Pixel ID available

//Mono buffer format defines
#define ISP_PIX_MONO1P (ISP_PIX_MONO | ISP_PIX_OCCUPY1BIT | 0x0037)
#define ISP_PIX_MONO2P (ISP_PIX_MONO | ISP_PIX_OCCUPY2BIT | 0x0038)
#define ISP_PIX_MONO4P (ISP_PIX_MONO | ISP_PIX_OCCUPY4BIT | 0x0039)
#define ISP_PIX_MONO8 (ISP_PIX_MONO | ISP_PIX_OCCUPY8BIT | 0x0001)
#define ISP_PIX_MONO8S (ISP_PIX_MONO | ISP_PIX_OCCUPY8BIT | 0x0002)
#define ISP_PIX_MONO10 (ISP_PIX_MONO | ISP_PIX_OCCUPY16BIT | 0x0003)
#define ISP_PIX_MONO10_PACKED (ISP_PIX_MONO | ISP_PIX_OCCUPY12BIT | 0x0004)
#define ISP_PIX_MONO12 (ISP_PIX_MONO | ISP_PIX_OCCUPY16BIT | 0x0005)
#define ISP_PIX_MONO12_PACKED (ISP_PIX_MONO | ISP_PIX_OCCUPY12BIT | 0x0006)
#define ISP_PIX_MONO14 (ISP_PIX_MONO | ISP_PIX_OCCUPY16BIT | 0x0025)
#define ISP_PIX_MONO16 (ISP_PIX_MONO | ISP_PIX_OCCUPY16BIT | 0x0007)

//Bayer buffer format defines
#define ISP_PIX_BAYGR8 (ISP_PIX_MONO | ISP_PIX_OCCUPY8BIT | 0x0008)
#define ISP_PIX_BAYRG8 (ISP_PIX_MONO | ISP_PIX_OCCUPY8BIT | 0x0009)
#define ISP_PIX_BAYGB8 (ISP_PIX_MONO | ISP_PIX_OCCUPY8BIT | 0x000A)
#define ISP_PIX_BAYBG8 (ISP_PIX_MONO | ISP_PIX_OCCUPY8BIT | 0x000B)
#define ISP_PIX_BAYGR10 (ISP_PIX_MONO | ISP_PIX_OCCUPY16BIT | 0x000C)
#define ISP_PIX_BAYRG10 (ISP_PIX_MONO | ISP_PIX_OCCUPY16BIT | 0x000D)
#define ISP_PIX_BAYGB10 (ISP_PIX_MONO | ISP_PIX_OCCUPY16BIT | 0x000E)
#define ISP_PIX_BAYBG10 (ISP_PIX_MONO | ISP_PIX_OCCUPY16BIT | 0x000F)
#define ISP_PIX_BAYGR12 (ISP_PIX_MONO | ISP_PIX_OCCUPY16BIT | 0x0010)
#define ISP_PIX_BAYRG12 (ISP_PIX_MONO | ISP_PIX_OCCUPY16BIT | 0x0011)
#define ISP_PIX_BAYGB12 (ISP_PIX_MONO | ISP_PIX_OCCUPY16BIT | 0x0012)
#define ISP_PIX_BAYBG12 (ISP_PIX_MONO | ISP_PIX_OCCUPY16BIT | 0x0013)
#define ISP_PIX_BAYGR10_PACKED (ISP_PIX_MONO | ISP_PIX_OCCUPY12BIT | 0x0026)
#define ISP_PIX_BAYRG10_PACKED (ISP_PIX_MONO | ISP_PIX_OCCUPY12BIT | 0x0027)
#define ISP_PIX_BAYGB10_PACKED (ISP_PIX_MONO | ISP_PIX_OCCUPY12BIT | 0x0028)
#define ISP_PIX_BAYBG10_PACKED (ISP_PIX_MONO | ISP_PIX_OCCUPY12BIT | 0x0029)
#define ISP_PIX_BAYGR12_PACKED (ISP_PIX_MONO | ISP_PIX_OCCUPY12BIT | 0x002A)
#define ISP_PIX_BAYRG12_PACKED (ISP_PIX_MONO | ISP_PIX_OCCUPY12BIT | 0x002B)
#define ISP_PIX_BAYGB12_PACKED (ISP_PIX_MONO | ISP_PIX_OCCUPY12BIT | 0x002C)
#define ISP_PIX_BAYBG12_PACKED (ISP_PIX_MONO | ISP_PIX_OCCUPY12BIT | 0x002D)
#define ISP_PIX_BAYGR16 (ISP_PIX_MONO | ISP_PIX_OCCUPY16BIT | 0x002E)
#define ISP_PIX_BAYRG16 (ISP_PIX_MONO | ISP_PIX_OCCUPY16BIT | 0x002F)
#define ISP_PIX_BAYGB16 (ISP_PIX_MONO | ISP_PIX_OCCUPY16BIT | 0x0030)
#define ISP_PIX_BAYBG16 (ISP_PIX_MONO | ISP_PIX_OCCUPY16BIT | 0x0031)

//RGB Packed buffer format defines
#define ISP_PIX_RGB8 (ISP_PIX_COLOR | ISP_PIX_OCCUPY24BIT | 0x0014)
#define ISP_PIX_BGR8 (ISP_PIX_COLOR | ISP_PIX_OCCUPY24BIT | 0x0015)
#define ISP_PIX_RGBA8 (ISP_PIX_COLOR | ISP_PIX_OCCUPY32BIT | 0x0016)
#define ISP_PIX_BGRA8 (ISP_PIX_COLOR | ISP_PIX_OCCUPY32BIT | 0x0017)
#define ISP_PIX_RGB10 (ISP_PIX_COLOR | ISP_PIX_OCCUPY48BIT | 0x0018)
#define ISP_PIX_BGR10 (ISP_PIX_COLOR | ISP_PIX_OCCUPY48BIT | 0x0019)
#define ISP_PIX_RGB12 (ISP_PIX_COLOR | ISP_PIX_OCCUPY48BIT | 0x001A)
#define ISP_PIX_BGR12 (ISP_PIX_COLOR | ISP_PIX_OCCUPY48BIT | 0x001B)
#define ISP_PIX_RGB16 (ISP_PIX_COLOR | ISP_PIX_OCCUPY48BIT | 0x0033)
#define ISP_PIX_RGB10V1_PACKED (ISP_PIX_COLOR | ISP_PIX_OCCUPY32BIT | 0x001C)
#define ISP_PIX_RGB10P32 (ISP_PIX_COLOR | ISP_PIX_OCCUPY32BIT | 0x001D)
#define ISP_PIX_RGB12V1_PACKED (ISP_PIX_COLOR | ISP_PIX_OCCUPY36BIT | 0X0034)
#define ISP_PIX_RGB565P (ISP_PIX_COLOR | ISP_PIX_OCCUPY16BIT | 0x0035)
#define ISP_PIX_BGR565P (ISP_PIX_COLOR | ISP_PIX_OCCUPY16BIT | 0X0036)

//YUV and YCbCr Packed buffer format defines
#define ISP_PIX_YUV411_8_UYYVYY (ISP_PIX_COLOR | ISP_PIX_OCCUPY12BIT | 0x001E)
#define ISP_PIX_YUV422_8_UYVY (ISP_PIX_COLOR | ISP_PIX_OCCUPY16BIT | 0x001F)
#define ISP_PIX_YUV422_8 (ISP_PIX_COLOR | ISP_PIX_OCCUPY16BIT | 0x0032)
#define ISP_PIX_YUV8_UYV (ISP_PIX_COLOR | ISP_PIX_OCCUPY24BIT | 0x0020)
#define ISP_PIX_YCBCR8_CBYCR (ISP_PIX_COLOR | ISP_PIX_OCCUPY24BIT | 0x003A)
#define ISP_PIX_YCBCR422_8 (ISP_PIX_COLOR | ISP_PIX_OCCUPY16BIT | 0x003B)
#define ISP_PIX_YCBCR422_8_CBYCRY (ISP_PIX_COLOR | ISP_PIX_OCCUPY16BIT | 0x0043)
#define ISP_PIX_YCBCR411_8_CBYYCRYY (ISP_PIX_COLOR | ISP_PIX_OCCUPY12BIT | 0x003C)
#define ISP_PIX_YCBCR601_8_CBYCR (ISP_PIX_COLOR | ISP_PIX_OCCUPY24BIT | 0x003D)
#define ISP_PIX_YCBCR601_422_8 (ISP_PIX_COLOR | ISP_PIX_OCCUPY16BIT | 0x003E)
#define ISP_PIX_YCBCR601_422_8_CBYCRY (ISP_PIX_COLOR | ISP_PIX_OCCUPY16BIT | 0x0044)
#define ISP_PIX_YCBCR601_411_8_CBYYCRYY (ISP_PIX_COLOR | ISP_PIX_OCCUPY12BIT | 0x003F)
#define ISP_PIX_YCBCR709_8_CBYCR (ISP_PIX_COLOR | ISP_PIX_OCCUPY24BIT | 0x0040)
#define ISP_PIX_YCBCR709_422_8 (ISP_PIX_COLOR | ISP_PIX_OCCUPY16BIT | 0x0041)
#define ISP_PIX_YCBCR709_422_8_CBYCRY (ISP_PIX_COLOR | ISP_PIX_OCCUPY16BIT | 0x0045)
#define ISP_PIX_YCBCR709_411_8_CBYYCRYY (ISP_PIX_COLOR | ISP_PIX_OCCUPY12BIT | 0x0042)

//RGB Planar buffer format defines
#define ISP_PIX_RGB8_PLANAR (ISP_PIX_COLOR | ISP_PIX_OCCUPY24BIT | 0x0021)
#define ISP_PIX_RGB10_PLANAR (ISP_PIX_COLOR | ISP_PIX_OCCUPY48BIT | 0x0022)
#define ISP_PIX_RGB12_PLANAR (ISP_PIX_COLOR | ISP_PIX_OCCUPY48BIT | 0x0023)
#define ISP_PIX_RGB16_PLANAR (ISP_PIX_COLOR | ISP_PIX_OCCUPY48BIT | 0x0024)

/* 输出模式配置 */
#define MSB_SEL   *(volatile unsigned char *) ((ISP_OMODE_BASE + COV_CHAR(0x3)) | (1 << 31))
#define DATA_SEL  *(volatile unsigned char *) ((ISP_OMODE_BASE + COV_CHAR(0x2)) | (1 << 31))
#define MODE_SEL  *(volatile unsigned char *) ((ISP_OMODE_BASE + COV_CHAR(0x1)) | (1 << 31))
#define WIDTH_SEL *(volatile unsigned char *) ((ISP_OMODE_BASE + COV_CHAR(0x0)) | (1 << 31))
#define OUTPUT_MASK	  *(volatile unsigned int *) ((ISP_OMODE_BASE + 0x04) | (1 << 31))

#define ISP_FPN			(0)
#define ISP_BINNING		(1)
#define ISP_SPC			(2)
#define ISP_DPC			(3)
#define ISP_BOC			(6)
#define ISP_DGC			(9)
#define ISP_BALANCE		(10)
#define ISP_CCM			(20)
#define ISP_LUT2D		(22)
#define ISP_GAMA		(23)
#define ISP_CSC			(24)
#define ISP_EE			(25)
#define ISP_MEAN_FILT	(26)

//<< isp 跳模块地址
#define SKIP_ISP_ADDR	*(volatile unsigned int *)((ISP_VER_BASE + 0x10) | (1 << 31))
#define SKIP_STATIC_CORRECT_ADDR	*(volatile unsigned int *)(ISP_VER_BASE + 0x14)		//<< 地址不对，仅为编译通过

typedef struct tagPixelFormatSetting
{
	uint32_t pixelFormat;
	uint8_t rawMsb;
	uint8_t dataSel;
	uint8_t modeSel;
	uint8_t widthSel;
} pixelFormatSetting;

/* 应用ISP参数 */
void IspApplyParameters(void);
void disableIspModel(uint32_t model);
void enableIspModel(uint32_t model);
void IspSetBinning(int x, int y, unsigned int width);//monoBinning
void IspSetColorBinning(uint8_t enable, uint8_t mode, uint8_t img_rb_flag, uint8_t bin_dir);//colorBinning

/* 图像模式配置 */
// sensor_mode: 0:mono sensor 1:color sensor
//color2mono:彩转黑模块
// out_type :pixelformat
void IspSetOutputMode(uint8_t sensorMode, uint8_t colorTransMono, uint32_t outType);
void IspInitOutputMode(uint8_t mono8Path, uint8_t rawMsb);
void IspSetOutputMask(uint32_t mask);
uint32_t IspGetOutputMask(void);

//void IspSetLut2DConfig(LUT_FPGA* pLutFpga);
//void IspSetLut2DAtFrameEnd(LUT_FPGA* pLutFpga);
//void IspSetEeConfig(SHARPNESS_FPGA* pSharpnessFpga);

void getIspSkipData(uint32_t *value);
void setIspSkip(uint32_t value);

void getStaticCorrectSkipData(uint32_t *value);
void setStaticCorrectSkip(uint32_t value);

unsigned short getIspChannel(void);
#endif
