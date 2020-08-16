/* ========================================================================== */
/*                             头文件区                                       */
/* ========================================================================== */
#include "alg_afix.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "LogDefs.h"
/* ========================================================================== */
/*                           宏和类型定义区                                   */
/* ========================================================================== */
/* 最大的采样点数，目前采集60个点*/
#define MAX_SAMPLE_NUM    60
/* 校正表曲线段数，一共63段曲线 */
#define AFIX_TABLE_CURV_NUM  63

/* 校正表亮度区间临界点数量，一共64个*/
#define AFIX_TABLE_POINT_NUM 64

#define AFIX_CH_NUM_4 4
#define AFIX_CH_NUM_3 3
#define OSA_EFAIL     1
#define OSA_SOK       0

/* 定义各颜色通道ID号 */
#define COLOR_CH_R              0           //R通道
#define COLOR_CH_GR             1           //Gr通道
#define COLOR_CH_GB             2           //Gb通道
#define COLOR_CH_B              3           //B通道

#define AFIX_CURVE_MAX_OFFSET     (32767)     /*定义校正曲线offset的最大值32767*/
#define AFIX_CURVE_MIN_OFFSET     (-32768)    /*定义校正曲线offset的最小值-32768,2*19*/
#define AFIX_CURVE_MAX_SLOPE      (4095)      /*定义校正曲线slope的最大值*/
#define AFIX_CURVE_MIN_SLOPE      (256)       /*定义校正曲线slope的最小值*/

#ifndef FLOAT2INT
#define FLOAT2INT(a) ((int)( (a >= 0) ? (a + 0.5) : (a - 0.5) ))
#endif

#ifndef CLIP_VAL
#define CLIP_VAL(a, low, high) (a) < (low) ? (low) : ( (a) > (high) ? (high) : (a) )
#endif

#define MEM_LE2BE_INT(x) ((((unsigned int)(x) & 0x000000ff) << 24) | (((unsigned int)(x) & 0x0000ff00) << 8 ) | (((unsigned int)(x) & 0x00ff0000) >> 8) | (((unsigned int)(x) & 0xff000000) >> 24))  

static unsigned short afixCurvTable[AFIX_TABLE_POINT_NUM] =
{
	0, 20, 40, 50, 60, 70, 80, 90, 100, 110, 120, 135, 150, 165, 180, 200, 220, 240, 265, 290,
	320, 350, 385, 425, 470, 520, 570, 630, 690, 760, 830, 910, 1000, 1100, 1200, 1300, 1400, 1500, 1600, 1700, 1800,
	1900, 2000, 2100, 2200, 2300, 2400, 2500, 2600, 2700, 2800, 2900, 3000, 3100, 3200, 3300, 3400, 3500, 3600, 3700, 3800,
	3900, 4000, 4095
};
/* ========================================================================== */
/*                            全局变量定义区                                  */
/* ========================================================================== */
typedef struct
{
	float   offset;     
	float   slope;
	unsigned int     k_b;
}ALG_Out_kb;

//输出k,b
typedef struct
{
	ALG_Out_kb           outAfixCurve[AFIX_TABLE_POINT_NUM];// fpga 64段
}ALG_Out_AfixCurve;

//3个矫正通道AD的像素值
typedef struct
{
	ALG_Out_AfixCurve  outAfixParam[AFIX_CH_NUM_4]; // 4通道
}ALG_Out_AfixParam;

//输出采样值 AFIX_TABLE_POINT_NUM=64
typedef struct
{
	ALG_Out_AfixParam    outAfixRegion[AFIX_CH_NUM_3];   ///3
}ALG_Out_AfixRegion;





/* ========================================================================== */
/*                          函数声明区                                        */
/* ========================================================================== */

static int ALG_Calc(ALG_Input *Input, ALG_Out_AfixRegion *fixTable);
static int ALG_Calc_k_b(ALG_Input *Input, int region, int channel, ALG_Out_AfixRegion *fixTable);
static int ALG_searchLeftPoint(unsigned int keypoint, ALG_In_AfixRegion *sample, int region, int channel, int*leftIdex);
static int ALG_searchRightPoint(unsigned int keypoint, ALG_In_AfixRegion *sample, int region, int channel, int*rightIdex);

/* ========================================================================== */
/*                          函数定义区                                        */
/* ========================================================================== */
int ALG_Init(ALG_Input *Input, ALG_HANDLE *handle)
{
	ALG_Output *Output;
	int size = 0;
	if (1 == Input->inFormat || 0 == Input->inFormat)
	{
		size = 64 * 3 * 4 * sizeof(int);
	}
	else
	{
		printf("不能识别类型");
		return OSA_EFAIL;
	}

	Output = (ALG_Output *)malloc(sizeof(ALG_Output));
	if (NULL == Output)
		return OSA_EFAIL;

	Output->Output_Data = (void*)malloc(size);
	Output->Output_Size = size;
	if (Output->Output_Data == NULL)
	{
		free(Output);
		return OSA_EFAIL;
	}
	*handle = (ALG_HANDLE)Output;

	return OSA_SOK;
}

ALG_Output * ALG_Run(ALG_HANDLE handle, ALG_Input *Input)
{
	//UP_Log("handle:0x%.8x input:0x%.8x\n", (unsigned int)handle, (unsigned int)Input);
	ALG_Out_AfixRegion fixTable;
	//ALG_Output Output;
	if (Input == NULL)
	{
		return NULL;
	}

	ALG_Calc(Input, &fixTable);
	
	float b = 0, k = 0;
	unsigned int *ptr = NULL;
	ptr = (unsigned int *)(((ALG_Output *)handle)->Output_Data); //(unsigned int *)(Output.Output_Data);
	FILE *fp = fopen("./1.txt", "w+");
	for (int region = 0; region < AFIX_CH_NUM_3; region++)
		{
			for (int channel = 0; channel < AFIX_CH_NUM_4; channel++)
			{
				for (int sample = 0; sample < AFIX_TABLE_POINT_NUM; sample++)
				{
					//*ptr = MEM_LE2BE_INT(fixTable.outAfixRegion[region].outAfixParam[channel].outAfixCurve[sample].k_b);
					*ptr = fixTable.outAfixRegion[region].outAfixParam[channel].outAfixCurve[sample].k_b;
					ptr++;
					k=fixTable.outAfixRegion[region].outAfixParam[channel].outAfixCurve[sample].slope;
					b=fixTable.outAfixRegion[region].outAfixParam[channel].outAfixCurve[sample].offset;
					fprintf(fp, "region=%d,channel=%d：k = %f;b = %f\n", region, channel, k, b);
					
				}
			}
			fprintf(fp,"-------------------> < --------------------------");
		}
	fclose(fp);
	return (ALG_Output *)handle;
}

static int ALG_Calc(ALG_Input *Input, ALG_Out_AfixRegion *fixTable)
{

	int channel;//通道R,GR,GB,B
	int region;//区域右上，左下，右下
	int sample;// 采样点
	int type = Input->inFormat;

	if (type == 0)
	{
		for (int sample = 0; sample < MAX_SAMPLE_NUM; sample++)   //60个采样点
		{
			for (int region = 0; region < AFIX_CH_NUM_4; region++) //4区域 通道均值
			{
				Input->input.inAfixsamp[sample].inAfixregion[region].r = (Input->input.inAfixsamp[sample].inAfixregion[region].r + 
				Input->input.inAfixsamp[sample].inAfixregion[region].gr + Input->input.inAfixsamp[sample].inAfixregion[region].gb + Input->input.inAfixsamp[sample].inAfixregion[region].b)/4;
			}
		}
		for (int region = 0; region < AFIX_CH_NUM_3; region++)  //3个矫正区域 
		{
			ALG_Calc_k_b(Input, region, 0, fixTable);
			for (int i = 0; i < AFIX_TABLE_POINT_NUM; i++)
			{ 
				fixTable->outAfixRegion[region].outAfixParam[1].outAfixCurve[i].offset = fixTable->outAfixRegion[region].outAfixParam[0].outAfixCurve[i].offset;//第一通道赋值给第二通道
				fixTable->outAfixRegion[region].outAfixParam[1].outAfixCurve[i].slope = fixTable->outAfixRegion[region].outAfixParam[0].outAfixCurve[i].slope;
				fixTable->outAfixRegion[region].outAfixParam[1].outAfixCurve[i].k_b = fixTable->outAfixRegion[region].outAfixParam[0].outAfixCurve[i].k_b;
				
				fixTable->outAfixRegion[region].outAfixParam[2].outAfixCurve[i].offset = fixTable->outAfixRegion[region].outAfixParam[0].outAfixCurve[i].offset;//第一通道赋值给第三通道
				fixTable->outAfixRegion[region].outAfixParam[2].outAfixCurve[i].slope = fixTable->outAfixRegion[region].outAfixParam[0].outAfixCurve[i].slope;
				fixTable->outAfixRegion[region].outAfixParam[2].outAfixCurve[i].k_b = fixTable->outAfixRegion[region].outAfixParam[0].outAfixCurve[i].k_b;
				
				fixTable->outAfixRegion[region].outAfixParam[3].outAfixCurve[i].offset = fixTable->outAfixRegion[region].outAfixParam[0].outAfixCurve[i].offset;//第一通道赋值给第四通道
				fixTable->outAfixRegion[region].outAfixParam[3].outAfixCurve[i].slope = fixTable->outAfixRegion[region].outAfixParam[0].outAfixCurve[i].slope;
				fixTable->outAfixRegion[region].outAfixParam[3].outAfixCurve[i].k_b = fixTable->outAfixRegion[region].outAfixParam[0].outAfixCurve[i].k_b;
			}
		}
	}

	else if (type == 1)
	{
		for (region = 0; region < AFIX_CH_NUM_3; region++)            // 3个矫正区域 1-3  
		{
			for (channel = 0; channel < AFIX_CH_NUM_4; channel++)     // 4个通道   0-4
			{
				ALG_Calc_k_b(Input, region, channel, fixTable);
			}
		}
	}
	
	return OSA_SOK;
}
	
//计算k,b
static int ALG_Calc_k_b(ALG_Input *Input, int region, int channel, ALG_Out_AfixRegion *fixTable)
{
	//UP_Log("region:%d channel:%d\n", region, channel);
	/*采样点起始点指针*/
	float *start_d0 = NULL, *start_d1 = NULL;
	int step = 0;
	/*亮度区域k,b值赋值标志位，0表示还未赋值，1表示已经赋值过*/
	unsigned int pointFlag[AFIX_TABLE_CURV_NUM] = { 0 };
	/*由采样点计算得到的k,b值*/
	float b = 0, k = 0;
	int i = 0;
	/*需要通过延长来赋值的线段位置，0~leftIdex和rightIdex~32需要延长赋值*/
	int leftIdex = -1, rightIdex = -1;
	/*基准通道采样点和待校正通道采样点值，用来计算直线的k,b*/
	float *x1 = NULL, *y1 = NULL, *x2 = NULL, *y2 = NULL;

	unsigned int curRegion = region + 1;//当前矫正区域

	step = sizeof(ALG_In_AfixRegion) / sizeof(float);
	
	//起始指针
	switch (channel)
	{
	case COLOR_CH_R:
		start_d0 = &(Input->input.inAfixsamp[0].inAfixregion[0].r);
		start_d1 = &(Input->input.inAfixsamp[0].inAfixregion[curRegion].r);
		break;
	case COLOR_CH_GR:
		start_d0 = &(Input->input.inAfixsamp[0].inAfixregion[0].gr);
		start_d1 = &(Input->input.inAfixsamp[0].inAfixregion[curRegion].gr);
		break;
	case COLOR_CH_GB:
		start_d0 = &(Input->input.inAfixsamp[0].inAfixregion[0].gb);
		start_d1 = &(Input->input.inAfixsamp[0].inAfixregion[curRegion].gb);
		break;
	case COLOR_CH_B:
		start_d0 = &(Input->input.inAfixsamp[0].inAfixregion[0].b);
		start_d1 = &(Input->input.inAfixsamp[0].inAfixregion[curRegion].b);
		break;

	default:
		return OSA_EFAIL;

	}

	for (i = 0; i < AFIX_TABLE_CURV_NUM; i++)
	{
		/*初始化*/
		k = 0;
		b = 0;
		x1 = NULL;
		y1 = NULL;
		x2 = NULL;
		y2 = NULL;
		leftIdex = -1;
		rightIdex = -1;

		/*找第i段曲线的起始端点*/
		unsigned int a0 = afixCurvTable[i];
		unsigned int a1 = afixCurvTable[i + 1];

		/*找a0左边最近的点*/
		int ret1 = ALG_searchLeftPoint(a0, (&Input->input.inAfixsamp[0]), curRegion, channel, &leftIdex);
		/*找a1右边最近的点*/
		int ret2 = ALG_searchRightPoint(a1, (&Input->input.inAfixsamp[0]), curRegion, channel, &rightIdex);


		/*如果a0左边有点且a1右边也有点则求解k,b值*/
		if (ret1 == OSA_SOK && ret2 == OSA_SOK)
		{

			pointFlag[i] = 1;

			/*找出y1,y2,x1,x2*/
			y1 = start_d0 + leftIdex*step;
			x1 = start_d1 + leftIdex*step;
			y2 = start_d0 + rightIdex*step;
			x2 = start_d1 + rightIdex*step;

			/*求k,b值*/
			if (*x1 != *x2)
			{
				k = (*y1 - *y2) / (*x1 - *x2);
				b = *y1 - (*x1)*k;
			}
			else
			{
				printf("X1==X2,error");
			}

			/*如果b值越界，小于-128，则用(0,-128)和(*x2, *y2)连线*/
			if ((int)FLOAT2INT(256.0 * b) < AFIX_CURVE_MIN_OFFSET)
			{
				float x0 = 0;
				float y0 = -128;
				k = (y0 - *y2) / (x0 - *x2);
				b = y0;
			}
			/*如果b值越界，大于127，则用(0,127)和(*x2, *y2)连线*/
			if ((int)FLOAT2INT(256.0 * b) > AFIX_CURVE_MAX_OFFSET)
			{
				float x0 = 0;
				float y0 = 127;
				k = (y0 - *y2) / (x0 - *x2);
				b = y0;
			}
			/*求offset和slope*/
			/*乘以256，小数部分转换成低8位*/
			short offset = CLIP_VAL((int)FLOAT2INT(256.0 * b), AFIX_CURVE_MIN_OFFSET, AFIX_CURVE_MAX_OFFSET);
			unsigned short slope = CLIP_VAL((int)FLOAT2INT(1024.0 *k), AFIX_CURVE_MIN_SLOPE, AFIX_CURVE_MAX_SLOPE);
			int k_b = ((slope << 16) & 0XFFFF0000) | (offset & 0X0000FFFF);

			//对该段赋值

			fixTable->outAfixRegion[region].outAfixParam[channel].outAfixCurve[i].offset = b;
			fixTable->outAfixRegion[region].outAfixParam[channel].outAfixCurve[i].slope = k;
			fixTable->outAfixRegion[region].outAfixParam[channel].outAfixCurve[i].k_b = k_b;
		}

	}
		/*将lineIdexStart之前的段用lineIdexStart段值赋值*/
		unsigned int lineIdexStart = 0;
		for (i = 0; i < AFIX_TABLE_CURV_NUM; i++)
		{

			if (pointFlag[i] != 0)
			{
				lineIdexStart = i;
				break;
			}
		}

		for (i = 0; i < lineIdexStart; i++)
		{
			pointFlag[i] = 1;
		
			fixTable->outAfixRegion[region].outAfixParam[channel].outAfixCurve[i].offset = \
				fixTable->outAfixRegion[region].outAfixParam[channel].outAfixCurve[lineIdexStart].offset;
			fixTable->outAfixRegion[region].outAfixParam[channel].outAfixCurve[i].slope = \
				fixTable->outAfixRegion[region].outAfixParam[channel].outAfixCurve[lineIdexStart].slope;
			fixTable->outAfixRegion[region].outAfixParam[channel].outAfixCurve[i].k_b = \
				fixTable->outAfixRegion[region].outAfixParam[channel].outAfixCurve[lineIdexStart].k_b;
	
		
		}

		/*将lineIdexEnd之后的段用lineIdexEnd-1段值赋值,
		* 这里将lineIdexEnd初始化为AFIX_TABLE_CURV_NUM，在少数情况下，gr和gb的矫正折线在上面全部被计算出来，不需要在这里将没有计算出来的点
		* 用上一段赋值，在这种情况下，lineIdexEnd初始化为0会导致后面将整段矫正系数赋值成0，从而导致在某些增益下出现粉屏的情况*/
		unsigned int lineIdexEnd = AFIX_TABLE_CURV_NUM;
		for (i = 0; i < AFIX_TABLE_CURV_NUM; i++)
		{
			if (pointFlag[i] == 0)
			{
				lineIdexEnd = i;
				break;
			}
		}
		lineIdexEnd = CLIP_VAL(lineIdexEnd, 1, AFIX_TABLE_CURV_NUM);
		for (i = lineIdexEnd; i < AFIX_TABLE_CURV_NUM; i++)
		{
			pointFlag[i] = 1;

			fixTable->outAfixRegion[region].outAfixParam[channel].outAfixCurve[i].offset = \
				fixTable->outAfixRegion[region].outAfixParam[channel].outAfixCurve[lineIdexEnd - 1].offset;
			fixTable->outAfixRegion[region].outAfixParam[channel].outAfixCurve[i].slope = \
				fixTable->outAfixRegion[region].outAfixParam[channel].outAfixCurve[lineIdexEnd - 1].slope;
			fixTable->outAfixRegion[region].outAfixParam[channel].outAfixCurve[i].k_b = \
				fixTable->outAfixRegion[region].outAfixParam[channel].outAfixCurve[lineIdexEnd - 1].k_b;
			
		}

		/*检查是否有还没赋值k,b的线段*/
		for (i = 0; i < AFIX_TABLE_CURV_NUM; i++)
		{
			if (pointFlag[i] == 0)
			{
				printf("curve %d = 0\n", i);
			}
		}

		return OSA_SOK;

}
	

static int ALG_searchLeftPoint(unsigned int keypoint, ALG_In_AfixRegion *sample, int curRegion, int channel, int*leftIdex)
{
	float *start_d0 = NULL;
	float *y = NULL;
	int step = 0;
	int i = 0;
	int ret = OSA_EFAIL;

	step = sizeof(ALG_In_AfixRegion) / sizeof(float);

	//起点指针
	switch (channel)
	{
	case COLOR_CH_R:
		start_d0 = &(sample->inAfixregion[curRegion].r);
		break;
	case COLOR_CH_GR:
		start_d0 = &(sample->inAfixregion[curRegion].gr);
		break;
	case COLOR_CH_GB:
		start_d0 = &(sample->inAfixregion[curRegion].gb);
		break;
	case COLOR_CH_B:
		start_d0 = &(sample->inAfixregion[curRegion].b);
		break;

	default:
		return OSA_EFAIL;
	}


	for (i = MAX_SAMPLE_NUM-1; i >= 0; i--)
	{
		/*第i个点坐标*/
		y = start_d0 + i*step;
		if (*y < (float)(keypoint))
		{
			*leftIdex = i;
			//OSA_printf("*y=%4.2f, i=%d, *leftIdex=%d\n",*y, i, *leftIdex);
			ret = OSA_SOK;
			break;
		}
	}

	return ret;
}


/*找a1右边最近的点*/
static int ALG_searchRightPoint(unsigned int keypoint, ALG_In_AfixRegion *sample, int curRegion, int channel, int*rightIdex)
{
	float *start_d0 = NULL;
	float *y = NULL;
	int step = 0;
	int i = 0;
	int ret = OSA_EFAIL;

	step = sizeof(ALG_In_AfixRegion) / sizeof(float);

	//起点指针
	switch (channel)
	{
	case COLOR_CH_R:
		start_d0 = &(sample->inAfixregion[curRegion].r);
		break;
	case COLOR_CH_GR:
		start_d0 = &(sample->inAfixregion[curRegion].gr);
		break;
	case COLOR_CH_GB:
		start_d0 = &(sample->inAfixregion[curRegion].gb);
		break;
	case COLOR_CH_B:
		start_d0 = &(sample->inAfixregion[curRegion].b);
		break;

	default:
		return OSA_EFAIL;
	}

	for (i = 0; i <= MAX_SAMPLE_NUM - 1; i++)
	{
		/*第i个点坐标*/
		y = start_d0 + i*step;
		if (*y > (float)(keypoint))
		{
			*rightIdex = i;
			//OSA_printf("*y=%4.2f, i=%d, *rightIdex=%d\n",*y, i, *rightIdex);
			ret = OSA_SOK;
			break;
		}
	}

	return ret;

}

void ALG_Delete(ALG_HANDLE handle)
{
	free ((ALG_Output *)handle);
}
