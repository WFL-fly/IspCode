#ifndef _ALG_SPCTOOL_H_
#define _ALG_SPCTOOL_H_

#ifdef __cplusplus
extern "C" {
#endif 
	/* ========================================================================== */
	/*                             头文件区                                       */
	/* ========================================================================== */

#include <stdio.h>
#include <Windows.h>
	//#include <WinDef.h>

	/* ========================================================================== */
	/*                           宏和类型定义区                                   */
	/* ========================================================================== */

	//版本号
	typedef enum
	{
		SPC_VERSION_101 = 1,
		SPC_VERSION_102 = 2,
		SPC_VERSION_103 = 3,
		SPC_VERSION_NUM
	}SPC_VERSION;

	//坏列算法版本号
	typedef enum
	{
		BADCOLUMN_VERSION_101 = 1,
		BADCOLUMN_VERSION_NUM
	}BADCOLUMN_VERSION;

	//raw类型，黑白或彩色
	typedef enum
	{
		SPC_RAW_TYPE_BW = 1,
		SPC_RAW_TYPE_COLOR,
		SPC_RAW_TYPE_NUM
	}SPC_RAW_TYPE;

	//单个坏点信息
	struct SPC_BADPOINTINFO
	{
		int  	x;         //坏点坐标x
		int  	y;         //坏点坐标y
		int  	type;      //坏点修补类型
		char 	reserve[4];
		/*
		bool operator==(const SPC_BADPOINTINFO& point)const
		{
			return (x==point.x&&y==point.y);
		}*/
	};
	
	//坏列在图像的上半部分还是下半部分,还是整列的标识
	typedef enum
	{
		BAD_COLUMN_IN_UPPER_IMAGE = 1,
		BAD_COLUMN_IN_LOWER_IMAGE = 2,
		BAD_COLUMN_IN_ALL_IMAGE = 3
	}BAD_COLUMN_POSITION_FLAG;

	//单个坏列信息
	struct SPC_BADCOLUMNINFO
	{
		int				x;					//坏列坐标x
		int				y;					//坏列上不可修补的坏点的纵坐标
		int				type;				//坏列修补类型
		unsigned short	positionInImageFlag;//坏列在图像的上半部分还是下半部分，1：上半部分，3：下半部分
		char			reserve[4];
	};


	//坏点检测输入图像数据源集合
	struct SPC_BADPOINT_RESOUCE
	{
		unsigned short 	*pBuffer[16];    				// in, 图片数据源, 时域滤波图像，归一化至12bit
		int 			imageNumber;             		// in, 图片数量
		int  			Thr[16];                        // in, 坏点允许偏差,归一化至8bit
		int				badColumnThr[16];				// in, 坏列允许偏差，归一化至8bit
		int				badLineThr[16];                 // in, 坏行列允许偏差，归一化至8bit
		char			reserve[4];
	};

	//坏点检测信息集合
	struct SPC_BADPOINTINFOS
	{
		int 					imageNumber;				// in		图片数量	
		unsigned char 			*raw[17];  					// in/out, 	生成的坏点图  坏点为1，好点为0
		unsigned int   			width;						// in,     	坏点图大小
		unsigned int   			height;						// in,     	坏点图大小
		int 					rawType;					// in, 		是否彩色图片, SPC_RAW_TYPE
		int  					version;					// in, 		算法版本号, SPC_VERSION
		unsigned int 			badPointSum;        		// out, 	检测到的坏点总数
		struct SPC_BADPOINTINFO *canRepairCoordinate; 		// out, 	坏点坐标信息
		unsigned int 			canRepairSum;				// out, 	可修复的坏点总数
		struct SPC_BADPOINTINFO *canNotRepairCoordinate;	// out, 	坏点坐标信息
		unsigned int 			canNotRepairSum;			// out, 	不可修复的坏点总数

		unsigned int			*canRepairInfo_CL[4];		// out,		可修复的坏点,only for cameraLink

		int						 needBadColumnCorrect;				// in,	是否需要坏列矫正，0：不需要，1：需要
		int						 flag_CXP;							// in,	是否cxp接口,0: 不是，1：是
		unsigned char			 *badRaw[17];						//in,	生成的坏点、坏列图，0:好点，1:坏点，2:坏列 3:坏行	
		int						 badColumnVersion;					// in,	坏列算法版本
		unsigned int 			 badColumnSum;        				// out, 	检测到的坏列总数
		struct SPC_BADCOLUMNINFO *canRepairBadColumnCoordinate; 	// out, 	坏列坐标信息
		unsigned int 			 canRepairBadColumnSum;				// out, 	可修复的坏列总数
		struct SPC_BADCOLUMNINFO *canNotRepairBadColumnCoordinate;	// out, 	坏列坐标信息
		unsigned int 			 canNotRepairBadColumnSum;			// out, 	不可修复的坏列上的坏点总数

		struct SPC_BADCOLUMNINFO *canRepairPointCooratBadCol; 		// out, 	坏列上可修复的点的信息，用于工具的检验部分
		unsigned int			 canRepairPointsSumatBadCol;		//out,	坏列上可修复点的个数，用于工具的检验部分

		char	reserve[4];
	};

	//--------------------------LF新增结构体-------------------------------//
	//坏点检测输入图像数据源集合
	struct SPC_Max_BADPOINT_RESOUCE
	{
		int			    needhighBlack;				           // in,  是否需要检测高曝光黑图坏点，0：不需要，1：需要
		int             maxBadpointNumber;                     // in,  图像最大单个坏点数，LF新增
		int             ori_Threshold;                         // in,  单张图像判断坏点的初始阈值，8bit,LF新增
	    unsigned short 	*pBuffer_highBlack;    				   // in,  图片数据源, 时域滤波图像，归一化至12bit
        char			reserve[2];
	};

	//坏点检测信息集合
	struct SPC_Max_BADPOINTINFOS
	{
		unsigned char 			*highBlack_Badraw;  			// in/out, 	生成的坏点图  坏点为1，好点为0
		unsigned int   			Max_width;						// in,     	坏点图大小
		unsigned int   			Max_height;						// in,     	坏点图大小
		struct SPC_BADPOINTINFO *max_badPointInfo; 		    // out, 	坏点坐标信息
		int 			        MaxbadPointSum;        		    // out, 	检测到的坏点总数
		int 			        res_Threshold;        		    // out, 	迭代之后的阈值,(12bit)LF新增
		char	reserve[4];
	};

	//单个坏点信息
	/*
	struct SPC_Max_BADPOINTINFO
	{
		int  	Max_x;         //坏点坐标x
		int  	Max_y;         //坏点坐标y
		int  	Max_type;      //坏点修补类型
		char 	reserve[4];
	};
	*/

	//----------------------------------------------------------------------------//


	/* ========================================================================== */
	/*                          函数声明区                                        */
	/* ========================================================================== */
    /*******************************************************************************
	* 函数名  : detectBadPointInit
	* 描  述  : 坏点检测初始化，主要用来创建日志文件
	* 输  入  : 无

	* 输  出  : 无
	* 返回值  : 无。
	*******************************************************************************/
    void detectBadPointInit();
    /*******************************************************************************
	* 函数名  : detectBadPointDestroy
	* 描  述  : 坏点检测释放，主要用来关闭日志文件
	* 输  入  : 无

	* 输  出  : 无
	* 返回值  : 无。
	*******************************************************************************/
    void detectBadPointDestroy();

	/*******************************************************************************
	* 函数名  : detectBadPointInfo
	* 描  述  : 图片、阈值 => 坏点图、坏点坐标、坏点类型信息
	* 输  入  : 无

	* 输  出  : 无
	* 返回值  : OSA_SOK: 创建成功。
	*           OSA_EXX: 创建失败。
	*******************************************************************************/
	int detectBadPointInfo(struct SPC_BADPOINT_RESOUCE *pImageBuffer, struct SPC_BADPOINTINFOS *badPonitInfo);

	/*******************************************************************************
	* 函数名  : detectBadPointInfo_CL
	* 描  述  : 坏点图 => 坏点坐标、坏点类型信息
	* 输  入  : 无

	* 输  出  : 无
	* 返回值  : OSA_SOK: 创建成功。
	*           OSA_EXX: 创建失败。
	*******************************************************************************/
	int detectBadPointInfo_CL(struct SPC_BADPOINTINFOS *badPonitInfo);

	/*******************************************************************************
	* 函数名  : deleteBadPointInfo
	* 描  述  : 释放BadPointInfo结构体内指针指向内存空间
	* 输  入  : 无

	* 输  出  : 无
	* 返回值  : OSA_SOK: 创建成功。
	*           OSA_EXX: 创建失败。
	*******************************************************************************/
	int deleteBadPointInfo(struct SPC_BADPOINTINFOS *badPonitInfo);
	/*******************************************************************************
	* 函数名  : deleteBadPointInfo_CL
	* 描  述  : 释放BadPointInfo结构体内指针指向内存空间,不包括*raw
	* 输  入  : 无

	* 输  出  : 无
	* 返回值  : OSA_SOK: 创建成功。
	*           OSA_EXX: 创建失败。
	*******************************************************************************/
	int deleteBadPointInfo_CL(struct SPC_BADPOINTINFOS *badPonitInfo);

	/***************************************************
	*函数名 ： detectMaxBadPointInfo
	*描  述 :  LF新增，检测高曝光黑图单个最大坏点
	***************************************************/
	int detectMaxBadPointInfo(struct SPC_Max_BADPOINT_RESOUCE *pImageBufferMax, struct SPC_Max_BADPOINTINFOS *badPonitInfoMax);

	/***************************************************
	*函数名 ： deleteMaxBadPointInfo
	*描  述 :  LF新增，检测高曝光黑图单个最大坏点
	***************************************************/
	int deleteMaxBadPointInfo(struct SPC_Max_BADPOINT_RESOUCE *pImageBufferMax, struct SPC_Max_BADPOINTINFOS *badPonitInfoMax);

#ifdef __cplusplus
}
#endif

#endif


#if 0


//版本号
	typedef enum
	{
		SPC_VERSION_101 = 1,
		SPC_VERSION_102,
		SPC_VERSION_NUM
	}SPC_VERSION;

	//坏列算法版本号
	typedef enum
	{
		BADCOLUMN_VERSION_101 = 1,
		BADCOLUMN_VERSION_NUM
	}BADCOLUMN_VERSION;

	//raw类型，黑白或彩色
	typedef enum
	{
		SPC_RAW_TYPE_BW = 1,
		SPC_RAW_TYPE_COLOR,
		SPC_RAW_TYPE_NUM
	}SPC_RAW_TYPE;

	//单个坏点信息
	struct SPC_BADPOINTINFO
	{
		int  	x;         //坏点坐标x
		int  	y;         //坏点坐标y
		int  	type;      //坏点修补类型
		char 	reserve[4];
	};

	//坏列在图像的上半部分还是下半部分的标识
	typedef enum
	{
		BAD_COLUMN_IN_UPPER_IMAGE = 1,
		BAD_COLUMN_IN_LOWER_IMAGE = 3
	}BAD_COLUMN_POSITION_FLAG;


	//单个坏列信息
	struct SPC_BADCOLUMNINFO
	{
		int				x;					//坏列坐标x
		int				y;					//坏列上不可修补的坏点的纵坐标
		int				type;				//坏列修补类型
		unsigned short	positionInImageFlag;//坏列在图像的上半部分还是下半部分，1：上半部分，3：下半部分
		char			reserve[4];
	};

	//坏点检测输入图像数据源集合
	struct SPC_BADPOINT_RESOUCE
	{
		unsigned short 	*pBuffer[16];    				// in, 图片数据源, 时域滤波图像，归一化至12bit
		int 			imageNumber;             		// in, 图片数量	
		int  			Thr[16];                        // in, 坏点允许偏差,归一化至8bit
		int				badColumnThr[16];				// in, 坏列允许偏差，归一化至8bit
		char			reserve[4];
	};

	//坏点检测信息集合
	struct SPC_BADPOINTINFOS
	{
		unsigned char 			*raw;						// in/out, 	生成的坏点图  坏点为1，好点为0
		unsigned int   			width;						// in,     	坏点图大小
		unsigned int   			height;						// in,     	坏点图大小
		int 					rawType;					// in, 		是否彩色图片, SPC_RAW_TYPE
		int  					version;					// in, 		算法版本号, SPC_VERSION
		unsigned int 			badPointSum;        		// out, 	检测到的坏点总数
		struct SPC_BADPOINTINFO *canRepairCoordinate; 		// out, 	坏点坐标信息
		unsigned int 			canRepairSum;				// out, 	可修复的坏点总数
		struct SPC_BADPOINTINFO *canNotRepairCoordinate;	// out, 	坏点坐标信息
		unsigned int 			canNotRepairSum;			// out, 	不可修复的坏点总数

		unsigned int			*canRepairInfo_CL[4];		// out,		可修复的坏点,only for cameraLink
		char	reserve[4];
	};

	//坏列检测信息集合
	struct SPC_BADCOLUMNINFOS
	{
		unsigned char 			 *raw;						// in/out, 	生成的坏点和坏列图  坏点为1，好点为0，坏列为2
		unsigned int   			 width;						// in,     	坏列图大小
		unsigned int   			 height;					// in,     	坏列图大小
		int 					 rawType;					// in, 		是否彩色图片, SPC_RAW_TYPE
		int						 version;					// in,		坏列算法版本号
		unsigned int 			 badColumnSum;        		// out, 	检测到的坏列总数
		struct SPC_BADCOLUMNINFO *canRepairCoordinate; 		// out, 	坏列坐标信息
		unsigned int 			 canRepairSum;				// out, 	可修复的坏列总数
		struct SPC_BADCOLUMNINFO *canNotRepairCoordinate;	// out, 	坏列坐标信息
		unsigned int 			 canNotRepairSum;			// out, 	不可修复的坏列总数
		char	reserve[4];
	};

	int detectBadPointBadColumnInfo(struct SPC_BADPOINT_RESOUCE *pImageBuffer, struct SPC_BADPOINTINFOS *badPonitInfo, struct SPC_BADCOLUMNINFOS *badColumnInfos);
	int deleteBadPointBadColumnInfo(struct SPC_BADPOINTINFOS *badPonitInfo, struct SPC_BADCOLUMNINFOS *badColumnInfos);
#endif