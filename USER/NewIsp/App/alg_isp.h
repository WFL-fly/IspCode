/******************************************************************************** alg_isp.h** Copyright (C) 2019-2021 ZheJiang Dahua Technology CO.,LTD.** Author : Yan Hongsheng  <yan_hongsheng@dahuatech.com>* Version: V1.0.0  2019-9-1 Create** Desc: ISP配置所需要的参数数据结构以及函数定义** Modification:*    Date    :*    Revision:*    Author  :*    Contents:*******************************************************************************/#ifndef _ALG_ISP_H_#define _ALG_ISP_H_/* ========================================================================== *//*                             头文件区                                       *//* ========================================================================== */#include "alg_cap.h"#include "aew_typeDef.h"/* ========================================================================== *//*                          数据结构定义区                                    *//* ========================================================================== */typedef enum{    ALG_AUTO_MODE_OFF = 0,              		//手动模式，界面显示选项为Off    ALG_AUTO_MODE_ONCE,                 		//once模式，界面显示选项为Once    ALG_AUTO_MODE_CONTINOUS,            		//continous模式，界面显示选项为Continous    ALG_AUTO_MODE_NUM} ALG_AutoMode;                        			//调节模式typedef enum{	ALG_LUT2D_MODE_GAMMA = 0,					//gamma模式，默认模式	ALG_LUT2D_MODE_LUT,							//lut模式	ALG_LUT2D_MODE_NUM} ALG_Lut2dMode;								//lut2d模式，gamma/lut两者互斥typedef enum{	ALG_RUN_MODE_AUTO = 0,						//自动模式，适用于每帧自动调用场景	ALG_RUN_MODE_MANUAL,						//手动模式，适用于手动切换参数场景	ALG_RUN_MODE_SEQUENCE,						//sequence模式，适用于sequence功能开启场景	ALG_RUN_MODE_NUM} ALG_RunMode;/********ALG_SensorCfgParams:sensor 配置参数，所有参数均为固定值，只需一次配置即可，程序运行中不会发生修改********/typedef struct {       Uint16	senMaxWidth;             //sensor最大宽度	Uint16	senMaxHeight;            //sensor最大高度    Uint8 	senFlipXFlag;            //sensor是否做X轴翻转    Uint8 	senFlipYFlag;            //sensor是否做Y轴翻转    Uint8 	senRoiXFlag;             //sensor是否做X轴ROI    Uint8 	senRoiYFlag;             //sensor是否做Y轴ROI    Uint8 	senOffsetXFlag;          //sensor是否做X轴偏移    Uint8 	senOffsetYFlag;          //sensor是否做Y轴偏移	Uint8 	aGainNum;            	 //模拟增益档位数    float   aGainTable[16];          //模拟增益档位值     float	maxSensorGain;           //sensor提供的增益最大值	} ALG_SensorCfgParams;/********ALG_IspCfgParams:isp 配置参数，所有参数均为固定值，只需一次配置即可，程序运行中不会发生修改********/typedef struct {   	Uint16  ispChannelNum;				//底层ISP处理通道数	float   	   	dgcOffset; 					//相机默认偏置增益		Uint16 	tColorMin;           		//AWB算法参数    Uint16 	tColorMax;           		//AWB算法参数    float        	grGainMin;           		//AWB算法参数    float          	grGainMax;           		//AWB算法参数    float         	gbGainMin;           		//AWB算法参数    float         	gbGainMax;           		//AWB算法参数    float         	minGain;           		    //增益最小值    float         	maxGain;           		    //增益最大值} ALG_IspCfgParams;typedef struct {   	ALG_SensorCfgParams sensorCfgParam;    ALG_IspCfgParams    ispCfgParam;} ALG_ConfigParams;typedef struct {    	ALG_RunMode		ispRunMode;					//ALG_IspRun接口被调用时所处场景    Uint32 	        pixelFormat;				//界面参数图像像素格式	Uint32          ispChannelCnt;				//底层ISP处理水平方向通道数，因tap格式改变} ALG_CommonParams;typedef struct{	Uint16  *blackStats;				//黑图列均值数据	Uint16  *grayStats;					//灰图列均值数据	Int32   blackOffset;				//黑电平偏置参数，对应于python sensor R129[9:1]	Uint32  columnNum;					//图像列数	Uint8   typeFlag;					//档位标识，0/1/...表示第1/2/...档模拟增益下的数据}ALG_FpnFlashParam;						//竖条纹矫正模块flash参数typedef struct{ 	Uint8   	        fpnFlashUpdate;			//竖条纹矫正模块Flash参数更新标识：1表示有更新    Uint8   	        fpnFlashCnt;			//当前Flash中竖条纹矫正参数档位数目    ALG_FpnFlashParam   fpnFlashParam[8];		//竖条纹矫正模块Flash参数} ALG_FpnParams;								//竖条纹矫正模块参数typedef struct{       Uint32      *badPixelData;				//Flash中坏点坐标信息	Uint32      badPixelNum;				//坏点数量	    Uint16 	    *badColumnData;				//Flash中坏列坐标信息    Uint32	    badColumnNum;				//坏列数量} ALG_SpcParams;								//坏点坏列矫正模块参数typedef struct{	Uint32        **seamFlashData;		//Falsh中分屏矫正参数    Uint32        seamFlashCnt;			//当前Falsh中分屏矫正参数档位数目    Uint32        seamDataSize;			//单档分屏矫正参数大小，单位为sizeof(unsigned int)} ALG_SeamParams;								//分屏矫正参数(KAI29MP/43MP使用)typedef struct{    Uint16  roiWidth;        			//ROI图像宽度    Uint16  roiHeight;        			//ROI图像高度    Uint16  roiOffsetX;    				//ROI图像X方向偏移    Uint16  roiOffsetY;    				//ROI图像Y方向偏移} ALG_RoiParams;								//ROI参数typedef struct{    Uint8  	reverseX;        			//图像X方向翻转情况：0表示不翻转，1表示翻转    Uint8  	reverseY;        			//图像Y方向翻转情况：0表示不翻转，1表示翻转} ALG_ReverseParams;							//图像翻转参数typedef struct{    Uint8  	binningX;        			//图像X方向binning情况：0表示不binning，1表示binning(2=>1)    Uint8  	binningY;        			//图像Y方向binning情况：0表示不binning，1表示binning(2=>1)} ALG_BinningParams;							//图像binning参数typedef struct{    	ALG_AutoMode 	blcMode;					//自动黑电平矫正状态标识    Uint16	        blcVal; 					//界面参数黑电平矫正值	Uint8 	        blcUpdate;					//黑电平矫正值被调整标识，once/continous模式下生效} ALG_BlcParams;								//黑电平矫正相关参数typedef struct{	ALG_AutoMode 	expMode;					//自动曝光状态标识	float			expVal;						//界面参数曝光时间值	Uint8           expUpdate;					//曝光值或自动曝光状态被调整标识，once/continous模式下生效} ALG_ExpParams;								//曝光相关参数typedef struct{   	Uint8	        digitalShift;				//界面参数digitalShift值	Uint8           brightness;   				//界面参数brightness值	ALG_AutoMode 	gainMode;					//自动增益状态标识    float			gainVal;					//界面参数gainRaw值	Uint8           gainUpdate;					//增益gainRaw值或自动增益状态被调整标识，once/continous模式下生效} ALG_GainParams;								//增益相关参数typedef struct{   	Uint32	targetBrightness;			//界面参数自动曝光/增益下目标亮度	float	aeUpperLimit;				//自动曝光调节上限	float	aeLowerLimit;				//自动曝光调节下限	float	agUpperLimit;				//自动增益调节上限	float	agLowerLimit;				//自动增益调节上限	Uint8	staRoiEnable;				//自动曝光/增益统计区域使能标识：0表示使用输出的全部图像，1表示使用设置的ROI区域图像    Uint16	staRoiOffsetX;				//自动曝光/增益统计区域起点X坐标    Uint16	staRoiOffsetY;				//自动曝光/增益统计区域起点Y坐标    Uint16	staRoiWidth;				//自动曝光/增益统计区域宽度    Uint16	staRoiHeight;				//自动曝光/增益统计区域高度} ALG_AutoFunctionParams;						//AutoFunctionControl下相关参数typedef struct{    ALG_AutoMode 	wbMode;						//自动白平衡状态标识    float           redVal;						//界面参数白平衡Red值    float           greenVal;					//界面参数白平衡Green值    float           blueVal;					//界面参数白平衡Blue值    Uint8	        wbUpdate;					//白平衡值或自动白平衡状态被调整标识，once/continous模式下生效} ALG_WhiteBalanceParams;						//白平衡相关参数typedef struct{	ALG_Lut2dMode 	lutMode;					//lut2d模式选择表示				float   		gammaVal;					//界面参数gamma值	Int32 			*lutTable;					//界面参数lut表内容	Uint8        	lutUpdate;					//lut表内容被调整标识，gamma模式下gamma值切换时生效} ALG_Lut2dParams;								//查找表功能相关参数typedef struct{	Uint8	contrast;					//界面参数对比度值	Uint32 	threshold;					//界面参数对比度阈值}ALG_ContrastParams;							//对比度功能相关参数typedef struct{    Uint8	    stitchEnable;          		//stitch矫正功能使能开关	Uint8 	    stitchDarkUpdate;      		//黑图统计信息更新标识	Uint8 	    stitchGrayUpdate;      		//灰图统计信息更新标识	    Uint8       stitchFlashUpdate;     		//stitch矫正系数更新标识，指示app层将矫正系数更新至flash	Uint32      stitchFlashData[4];    		//stitch矫正系数}ALG_StitchParams;								//stitch矫正功能相关参数(KAI29MP专用)typedef struct{    ALG_RunMode             ispRunMode;	ALG_ConfigParams		configParams;    ALG_CommonParams		commonParams;	ALG_FpnParams			fpnParams;	ALG_SpcParams			spcParams;	ALG_SeamParams			seamParams;	ALG_RoiParams			roiParams;	ALG_ReverseParams		reverseParams;	ALG_BinningParams		binningParams;	ALG_BlcParams			blcParams;	ALG_ExpParams			expParams;	ALG_GainParams			gainParams;	ALG_AutoFunctionParams	afParams;	ALG_WhiteBalanceParams	wbParams;	ALG_Lut2dParams			lut2dParams;	ALG_ContrastParams		contrastParams;	ALG_StitchParams		stitchParams;}ALG_IspParams;	/* ========================================================================== *//*                          函数定义区                                        *//* ========================================================================== *//******************************************************************************** 函数名  : ALG_ispCreate* 描  述  : 创建相关参数,并初始化值* 输  入  : - pIspParams:       isp模块参数* 输  出  : 无。* 返回值  : OSA_SOK: 创建成功。*           OSA_EXX: 创建失败。*******************************************************************************/Int32 ALG_ispCreate(ALG_IspParams* pIspParams);/******************************************************************************** 函数名  : ALG_ispInit* 描  述  : 初始化ISP模块* 输  入  : - pIspParams:       isp模块参数* 输  出  : 无。* 返回值  : OSA_SOK: 配置成功。*           OSA_EXX: 配置失败。*******************************************************************************/Int32 ALG_ispInit(void);/******************************************************************************** 函数名  : ALG_ispRun* 描  述  : ISP模块运行函数* 输  入  : - pIspParams:       isp模块参数* 输  出  : 无。* 返回值  : OSA_SOK: 配置成功。*           OSA_EXX: 配置失败。*******************************************************************************/Int32 ALG_ispRun(void);/******************************************************************************** 函数名  : ALG_ispDelete* 描  述  : 删除ISP模块，释放参数所占内存* 输  入  : - pIspParams:       isp模块参数* 输  出  : 无。* 返回值  : OSA_SOK: 删除成功。*           OSA_EXX: 删除失败。*******************************************************************************/Int32 ALG_ispDelete(void);#endif