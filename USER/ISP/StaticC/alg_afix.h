/*******************************************************************************
* alg_afix.h
*
* sharp CCD 2900 静态矫正模块
*
* Author : Huang Bijuan
* Version: V1.0.0  2017-7-24 Create
*
*******************************************************************************/

#ifndef _ALG_AFIX_
#define _ALG_AFIX_

/* ========================================================================== */
/*                             头文件区                                       */
/* ========================================================================== */
#ifdef __cplusplus
extern "C" {
#endif

      
	/* 最大的采样点数，目前采集60个点*/
#define MAX_SAMPLE_NUM    60
	/* 校正表曲线段数，一共63段曲线 */
#define AFIX_TABLE_CURV_NUM  63

	/* 校正表亮度区间临界点数量，一共64个*/
#define AFIX_TABLE_POINT_NUM 64

#define AFIX_CH_NUM_4 4
#define AFIX_CH_NUM_3 3

	//输入
	//校正像素点,改成浮点数提高一下采样精度
	//当做输入时，ALG_AfixPixel.gr_kb取gr像素值，作为输出k,b时，作为k，b值
	typedef struct
	{
		float  gr;
		float   r;
		float   b;
		float  gb;
	}ALG_In_AfixPixel;

	//各通道AD的像素值 AFIX_CH_NUM_4=4
	typedef struct
	{
		ALG_In_AfixPixel    inAfixregion[AFIX_CH_NUM_4];
	}ALG_In_AfixRegion;

	//采样值MAX_SAMPLE_NUM=60
	typedef struct
	{
		ALG_In_AfixRegion  	inAfixsamp[MAX_SAMPLE_NUM];
	}ALG_In_AfixSample;

	
	typedef struct
	{
		ALG_In_AfixSample  	input;
		int 				inFormat;		//mono为0，color为1
		int					inBits;
	}ALG_Input;

	typedef struct
	{
		void*  				Output_Data;
		int 				Output_Size;	//有效字节数
	}ALG_Output;

	
	/* ========================================================================== */
	/*                          函数声明区                                        */
	/* ========================================================================== */
	
#define ALG_HANDLE  void * 

	/*******************************************************************************
	* 函数名  : ALG_Init
	* 描  述  : 初始化模块
	* 输  入  : 无

	* 输  出  : 无
	* 返回值  : OSA_SOK: 创建成功。
	*           OSA_EXX: 创建失败。
	*******************************************************************************/
	int ALG_Init(ALG_Input *Input, ALG_HANDLE *handle);
	/*******************************************************************************
	* 函数名  : ALG_Run
	* 描  述  : 矫正算法模块
	* 输  入  : 无

	* 输  出  : 无
	* 返回值  : OSA_SOK: 创建成功。
	*           OSA_EXX: 创建失败。
	*******************************************************************************/
	ALG_Output * ALG_Run(ALG_HANDLE handle, ALG_Input *Input);
	/*******************************************************************************
	* 函数名  : ALG_Delete
	* 描  述  : 内存释放
	* 输  入  : 无

	* 输  出  : 无
	* 返回值  : OSA_SOK: 创建成功。
	*           OSA_EXX: 创建失败。
	*******************************************************************************/
	void ALG_Delete(ALG_HANDLE handle);
#ifdef __cplusplus
}
#endif

#endif