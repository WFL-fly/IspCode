#ifndef _ALG_GET_PARAMETER_H_
#define _ALG_GET_PARAMETER_H_
/* ========================================================================== */
/*                             头文件区                                       */
/* ========================================================================== */
#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <Windows.h>

/* ========================================================================== */
/*                           宏和类型定义区                                   */
/* ========================================================================== */

#define OSA_SOK	 0	 		//返回成功
#define OSA_EXX -1			//返回失败

//算法类型
typedef enum{
	ALG_TYPE_FFC_REGION = 0,
	ALG_TYPE_FFC_ROW,
    ALG_TYPE_FFC_REGION_PICK,
	ALG_TYPE_FFC_NUM
} ALG_TYPE_FFC;

//图像格式类型
typedef enum{
	ALG_IMG_FORMAT_MONO = 0,
	ALG_IMG_FORMAT_RG,
	ALG_IMG_FORMAT_GB,
	ALG_IMG_FORMAT_GR,
	ALG_IMG_FORMAT_BG,
	ALG_IMG_FORMAT_NUM
} ALG_IMG_FORMAT;

/* 算法输入参数 */
typedef struct
{
	int 			nWidth;  		//输入图像宽度
	int 			nHeight;		//输入图像高度
	int 			nBits;			//输入图像数据位深
	void 			*greyData;		//输入亮图数据
	void			*blackData;		//输入黑图数据
	int				greyDst;		//亮图矫正目标值
	int				blackDst;		//黑图矫正目标值
	ALG_IMG_FORMAT 	nFormat;		//输入图像数据格式
	ALG_TYPE_FFC	nType;			//所选算法类别
	int 			region_height_scale;	//FFC_Region算法压缩scale,--USB:16;GIGE:16
	int 			region_width_scale;	//FFC_Region算法压缩scale,--USB:32;GIGE:16
	unsigned char	kb_byte;		//FFC_Region算法中KB占字节数目
    unsigned char	paramIsPick;	//KB参数是否进行挑选 0：不挑选，所有KB参数存储到相机；
                                    //1：参数挑选，部分参数存储到相机，缺失的参数，相机通过差值获取
	int 			reserved[8];
}ALG_FFCParam;

/* 算法输出参数表数据*/
typedef struct
{	
	float			nDiff;			//输出亮度不均匀程度
	
	int				nSize;			//输出FFC数据大小，字节数
	unsigned char	*pFFCTable;		//输出参数数据
	int				nCRC32;			//输出参数数据的crc32校验码
	
	int 			reserved[8];
}ALG_FFCTable;

/* ========================================================================== */
/*                          函数声明区                                        */
/* ========================================================================== */

/*******************************************************************************
* 函数名  : ALG_Nonuniformity_calc
* 描  述  : 获取亮图的不均匀性nDiff
* 输  入  : - ALG_FFCParam
            - ALG_FFCTable
* 输  出  : 无
* 返回值  : OSA_SOK: 成功。
*           OSA_EXX: 失败。
*******************************************************************************/
//int ALG_Nonuniformity_calc(ALG_FFCParam *pFFCParam, ALG_FFCTable *pFFCTable);

/*******************************************************************************
* 函数名  : ALG_GetParameterInit
* 描  述  : 获取FFC参数表内存空间大小
* 输  入  : - ALG_FFCParam
- ALG_FFCTable
* 输  出  : 无
* 返回值  : >0 : 成功。
*           OSA_EXX: 失败。
*******************************************************************************/
int ALG_GetParameterMemoryLen(ALG_FFCParam *pFFCParam);

/*******************************************************************************
* 函数名  : ALG_GetParameterRun
* 描  述  : 计算FFC参数表
* 输  入  : - ALG_FFCParam
            - ALG_FFCTable
* 输  出  : 无
* 返回值  : OSA_SOK: 成功。
*           OSA_EXX: 失败。
*******************************************************************************/
int ALG_GetParameterRun(ALG_FFCParam *pFFCParam, ALG_FFCTable *pFFCTable);

#ifdef __cplusplus
}
#endif


#endif