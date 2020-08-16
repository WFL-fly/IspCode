#include "DrvIsp_Dgc.h"
#include "isp_utils.h"

/*******************************************************************************
* 函数名  : Dg_Init
* 描  述  : 初始化mono数字增益
* 输  入  : 无
* 输  出  : 无
* 返回值  : 无
*******************************************************************************/
void DrvIspDg_Init(void)
{
	DG_Gr = 0x0100;
	DG_R  = 0x0100;
	DG_B  = 0x0100;
	DG_Gb = 0x0100;
}
/*******************************************************************************
* 函数名  : Gg_setVal
* 描  述  : 设置mono数字增益
* 输  入  : 无
* 输  出  : 增益设置值
* 返回值  : 无
*******************************************************************************/
void DrvIspGg_setVal(float coff)
{
	DG_Gr = FLOTOFIX(unsigned short, 8, coff);
	DG_R  = FLOTOFIX(unsigned short, 8, coff);
	DG_B  = FLOTOFIX(unsigned short, 8, coff);
	DG_Gb = FLOTOFIX(unsigned short, 8, coff);
}
/*******************************************************************************
* 函数名  : Dg_getVal
* 描  述  : 获取mono数字增益
* 输  入  : 无
* 输  出  : 增益设置值
* 返回值  : 无
*******************************************************************************/
void DrvIspDg_getVal(unsigned short *coff)
{
    *coff = FIXTOFLOAT(float, 8, DG_Gr);
}

/*******************************************************************************
* 函数名  : Dgc_Init
* 描  述  : 彩色数字增益初始化
            默认设置1倍增益
* 输  入  : 无
* 输  出  : 无
* 返回值  : 无
*******************************************************************************/
void DrvIspDgc_Init(void)
{
	DG_Gr = 0x0100;
	DG_R = 0x0100;
	DG_B = 0x0100;
	DG_Gb = 0x0100;
}

/*******************************************************************************
* 函数名  : Dgc_Init
* 描  述  : 设置彩色数字增益
* 输  入  : 各通道增益设置值
* 输  出  : 无
* 返回值  : 无
*******************************************************************************/
void DrvIspDgc_setVal(float gr, float r, float b, float gb)
{
	DG_Gr = FLOTOFIX(unsigned short, 8, gr);
	DG_R  = FLOTOFIX(unsigned short, 8, r);
	DG_B  = FLOTOFIX(unsigned short, 8, b);
	DG_Gb = FLOTOFIX(unsigned short, 8, gb);
}
/*******************************************************************************
* 函数名  : Dgc_getVal
* 描  述  : 获取彩色数字增益
* 输  入  : 无
* 输  出  : 各通道增益设置值
* 返回值  : 无
*******************************************************************************/
void DrvIspDgc_getVal(float *gr, float *r, float *b, float *gb)
{
	*gr = FIXTOFLOAT(float, 8, DG_Gr);
	*r  = FIXTOFLOAT(float, 8, DG_R);
	*b  = FIXTOFLOAT(float, 8, DG_B);
	*gb = FIXTOFLOAT(float, 8, DG_Gb);
}
