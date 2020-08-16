#ifndef _ALG_SPCTOOL_LVDS_H_
#define _ALG_SPCTOOL_LVDS_H_

#ifdef __cplusplus
extern "C" {
#endif
/* ========================================================================== */
/*                             头文件区                                       */
/* ========================================================================== */
#include <stdio.h>
#include <Windows.h>

/* ========================================================================== */
/*                           宏和类型定义区                                   */
/* ========================================================================== */

//版本号
typedef enum
{
	LVDS_VERSION_101 = 1,
	LVDS_VERSION_102,
	LVDS_VERSION_NUM
}LVDS_VERSION;

//raw类型，黑白或彩色
typedef enum
{
	LVDS_RAW_TYPE_BW    = 0,
	LVDS_RAW_TYPE_COLOR,
	LVDS_RAW_TYPE_NUM
}LVDS_RAW_TYPE;

//raw类型，黑白或彩色
typedef enum
{
	LVDS_RERVESEX_TYPE_NO    = 1,
	LVDS_RERVESEX_TYPE_YES,
	LVDS_RERVESEX_TYPE_NUM
}LVDS_RERVESEX_TYPE;

/*单个坏点信息*/
struct LVDS_BADPOINTINFO
{
	int  x;         //坏点坐标x
	int  y;         //坏点坐标y
	int  type;      //坏点修补类型
	char reserve[4];
};

/* 算法输入参数 */
struct LVDS_SPCParam
{
	unsigned int   			width;                  // in,     	坏点图大小
	unsigned int   			height;                 // in,     	坏点图大小
	int 					rawType;                // in, 		是否彩色图片, LVDS_RAW_TYPE  0为mono，1为color
	int  					version;                // in, 		算法版本号, LVDS_VERSION
	LVDS_BADPOINTINFO*		spcRawData;				// in, 		输入坏点信息
	int  					defectCount;			// in, 		输入坏点总个数
	int  					reverseFlag;			// in, 		输入坏点起始点位置,LVDS_RERVESEX_TYPE 0不翻转 1翻转
};

/* 算法输出参数表数据*/
struct LVDS_SPCTable
{
	LVDS_BADPOINTINFO*		canRepairPoint_no;
	int 					canRepairSum_no;
	LVDS_BADPOINTINFO*		canRepairPoint_x;
	int 					canRepairSum_x;
	LVDS_BADPOINTINFO*		canRepairPoint_y;
	int 					canRepairSum_y;
	LVDS_BADPOINTINFO*		canRepairPoint_xy;
	int 					canRepairSum_xy;
	LVDS_BADPOINTINFO*		canNotRepairPoint_no;
	int 					canNotRepairSum_no;
	LVDS_BADPOINTINFO*		canNotRepairPoint_x;
	int 					canNotRepairSum_x;
};



/* ========================================================================== */
/*                          函数声明区                                        */
/* ========================================================================== */

/*******************************************************************************
* 函数名  : detectBadPointInfo_lvds
* 描  述  : 计算SPC参数表
* 输  入  : - ALG_SPCParam
* 输  出  ：- ALG_SPCTable
* 输  出  : 无
* 返回值  : OSA_SOK: 成功。
*           OSA_EXX: 失败。
*******************************************************************************/
int detectBadPointInfo_lvds(LVDS_SPCParam *SpcParam, LVDS_SPCTable *SpcTable);

/*******************************************************************************
* 函数名  : deleteBadPointInfo
* 描  述  : 释放BadPointInfo结构体内指针指向内存空间
* 输  入  : 无

* 输  出  : 无
* 返回值  : OSA_SOK: 创建成功。
*           OSA_EXX: 创建失败。
*******************************************************************************/

int deleteBadPointInfo_lvds(LVDS_SPCTable *SpcTable);
#ifdef __cplusplus
}
#endif

#endif