/* ========================================================================== */
/*                             ͷ�ļ���                                       */
/* ========================================================================== */
#include "alg_afix.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "LogDefs.h"
/* ========================================================================== */
/*                           ������Ͷ�����                                   */
/* ========================================================================== */
/* ���Ĳ���������Ŀǰ�ɼ�60����*/
#define MAX_SAMPLE_NUM    60
/* У�������߶�����һ��63������ */
#define AFIX_TABLE_CURV_NUM  63

/* У�������������ٽ��������һ��64��*/
#define AFIX_TABLE_POINT_NUM 64

#define AFIX_CH_NUM_4 4
#define AFIX_CH_NUM_3 3
#define OSA_EFAIL     1
#define OSA_SOK       0

/* �������ɫͨ��ID�� */
#define COLOR_CH_R              0           //Rͨ��
#define COLOR_CH_GR             1           //Grͨ��
#define COLOR_CH_GB             2           //Gbͨ��
#define COLOR_CH_B              3           //Bͨ��

#define AFIX_CURVE_MAX_OFFSET     (32767)     /*����У������offset�����ֵ32767*/
#define AFIX_CURVE_MIN_OFFSET     (-32768)    /*����У������offset����Сֵ-32768,2*19*/
#define AFIX_CURVE_MAX_SLOPE      (4095)      /*����У������slope�����ֵ*/
#define AFIX_CURVE_MIN_SLOPE      (256)       /*����У������slope����Сֵ*/

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
/*                            ȫ�ֱ���������                                  */
/* ========================================================================== */
typedef struct
{
	float   offset;     
	float   slope;
	unsigned int     k_b;
}ALG_Out_kb;

//���k,b
typedef struct
{
	ALG_Out_kb           outAfixCurve[AFIX_TABLE_POINT_NUM];// fpga 64��
}ALG_Out_AfixCurve;

//3������ͨ��AD������ֵ
typedef struct
{
	ALG_Out_AfixCurve  outAfixParam[AFIX_CH_NUM_4]; // 4ͨ��
}ALG_Out_AfixParam;

//�������ֵ AFIX_TABLE_POINT_NUM=64
typedef struct
{
	ALG_Out_AfixParam    outAfixRegion[AFIX_CH_NUM_3];   ///3
}ALG_Out_AfixRegion;





/* ========================================================================== */
/*                          ����������                                        */
/* ========================================================================== */

static int ALG_Calc(ALG_Input *Input, ALG_Out_AfixRegion *fixTable);
static int ALG_Calc_k_b(ALG_Input *Input, int region, int channel, ALG_Out_AfixRegion *fixTable);
static int ALG_searchLeftPoint(unsigned int keypoint, ALG_In_AfixRegion *sample, int region, int channel, int*leftIdex);
static int ALG_searchRightPoint(unsigned int keypoint, ALG_In_AfixRegion *sample, int region, int channel, int*rightIdex);

/* ========================================================================== */
/*                          ����������                                        */
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
		printf("����ʶ������");
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
					fprintf(fp, "region=%d,channel=%d��k = %f;b = %f\n", region, channel, k, b);
					
				}
			}
			fprintf(fp,"-------------------> < --------------------------");
		}
	fclose(fp);
	return (ALG_Output *)handle;
}

static int ALG_Calc(ALG_Input *Input, ALG_Out_AfixRegion *fixTable)
{

	int channel;//ͨ��R,GR,GB,B
	int region;//�������ϣ����£�����
	int sample;// ������
	int type = Input->inFormat;

	if (type == 0)
	{
		for (int sample = 0; sample < MAX_SAMPLE_NUM; sample++)   //60��������
		{
			for (int region = 0; region < AFIX_CH_NUM_4; region++) //4���� ͨ����ֵ
			{
				Input->input.inAfixsamp[sample].inAfixregion[region].r = (Input->input.inAfixsamp[sample].inAfixregion[region].r + 
				Input->input.inAfixsamp[sample].inAfixregion[region].gr + Input->input.inAfixsamp[sample].inAfixregion[region].gb + Input->input.inAfixsamp[sample].inAfixregion[region].b)/4;
			}
		}
		for (int region = 0; region < AFIX_CH_NUM_3; region++)  //3���������� 
		{
			ALG_Calc_k_b(Input, region, 0, fixTable);
			for (int i = 0; i < AFIX_TABLE_POINT_NUM; i++)
			{ 
				fixTable->outAfixRegion[region].outAfixParam[1].outAfixCurve[i].offset = fixTable->outAfixRegion[region].outAfixParam[0].outAfixCurve[i].offset;//��һͨ����ֵ���ڶ�ͨ��
				fixTable->outAfixRegion[region].outAfixParam[1].outAfixCurve[i].slope = fixTable->outAfixRegion[region].outAfixParam[0].outAfixCurve[i].slope;
				fixTable->outAfixRegion[region].outAfixParam[1].outAfixCurve[i].k_b = fixTable->outAfixRegion[region].outAfixParam[0].outAfixCurve[i].k_b;
				
				fixTable->outAfixRegion[region].outAfixParam[2].outAfixCurve[i].offset = fixTable->outAfixRegion[region].outAfixParam[0].outAfixCurve[i].offset;//��һͨ����ֵ������ͨ��
				fixTable->outAfixRegion[region].outAfixParam[2].outAfixCurve[i].slope = fixTable->outAfixRegion[region].outAfixParam[0].outAfixCurve[i].slope;
				fixTable->outAfixRegion[region].outAfixParam[2].outAfixCurve[i].k_b = fixTable->outAfixRegion[region].outAfixParam[0].outAfixCurve[i].k_b;
				
				fixTable->outAfixRegion[region].outAfixParam[3].outAfixCurve[i].offset = fixTable->outAfixRegion[region].outAfixParam[0].outAfixCurve[i].offset;//��һͨ����ֵ������ͨ��
				fixTable->outAfixRegion[region].outAfixParam[3].outAfixCurve[i].slope = fixTable->outAfixRegion[region].outAfixParam[0].outAfixCurve[i].slope;
				fixTable->outAfixRegion[region].outAfixParam[3].outAfixCurve[i].k_b = fixTable->outAfixRegion[region].outAfixParam[0].outAfixCurve[i].k_b;
			}
		}
	}

	else if (type == 1)
	{
		for (region = 0; region < AFIX_CH_NUM_3; region++)            // 3���������� 1-3  
		{
			for (channel = 0; channel < AFIX_CH_NUM_4; channel++)     // 4��ͨ��   0-4
			{
				ALG_Calc_k_b(Input, region, channel, fixTable);
			}
		}
	}
	
	return OSA_SOK;
}
	
//����k,b
static int ALG_Calc_k_b(ALG_Input *Input, int region, int channel, ALG_Out_AfixRegion *fixTable)
{
	//UP_Log("region:%d channel:%d\n", region, channel);
	/*��������ʼ��ָ��*/
	float *start_d0 = NULL, *start_d1 = NULL;
	int step = 0;
	/*��������k,bֵ��ֵ��־λ��0��ʾ��δ��ֵ��1��ʾ�Ѿ���ֵ��*/
	unsigned int pointFlag[AFIX_TABLE_CURV_NUM] = { 0 };
	/*�ɲ��������õ���k,bֵ*/
	float b = 0, k = 0;
	int i = 0;
	/*��Ҫͨ���ӳ�����ֵ���߶�λ�ã�0~leftIdex��rightIdex~32��Ҫ�ӳ���ֵ*/
	int leftIdex = -1, rightIdex = -1;
	/*��׼ͨ��������ʹ�У��ͨ��������ֵ����������ֱ�ߵ�k,b*/
	float *x1 = NULL, *y1 = NULL, *x2 = NULL, *y2 = NULL;

	unsigned int curRegion = region + 1;//��ǰ��������

	step = sizeof(ALG_In_AfixRegion) / sizeof(float);
	
	//��ʼָ��
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
		/*��ʼ��*/
		k = 0;
		b = 0;
		x1 = NULL;
		y1 = NULL;
		x2 = NULL;
		y2 = NULL;
		leftIdex = -1;
		rightIdex = -1;

		/*�ҵ�i�����ߵ���ʼ�˵�*/
		unsigned int a0 = afixCurvTable[i];
		unsigned int a1 = afixCurvTable[i + 1];

		/*��a0�������ĵ�*/
		int ret1 = ALG_searchLeftPoint(a0, (&Input->input.inAfixsamp[0]), curRegion, channel, &leftIdex);
		/*��a1�ұ�����ĵ�*/
		int ret2 = ALG_searchRightPoint(a1, (&Input->input.inAfixsamp[0]), curRegion, channel, &rightIdex);


		/*���a0����е���a1�ұ�Ҳ�е������k,bֵ*/
		if (ret1 == OSA_SOK && ret2 == OSA_SOK)
		{

			pointFlag[i] = 1;

			/*�ҳ�y1,y2,x1,x2*/
			y1 = start_d0 + leftIdex*step;
			x1 = start_d1 + leftIdex*step;
			y2 = start_d0 + rightIdex*step;
			x2 = start_d1 + rightIdex*step;

			/*��k,bֵ*/
			if (*x1 != *x2)
			{
				k = (*y1 - *y2) / (*x1 - *x2);
				b = *y1 - (*x1)*k;
			}
			else
			{
				printf("X1==X2,error");
			}

			/*���bֵԽ�磬С��-128������(0,-128)��(*x2, *y2)����*/
			if ((int)FLOAT2INT(256.0 * b) < AFIX_CURVE_MIN_OFFSET)
			{
				float x0 = 0;
				float y0 = -128;
				k = (y0 - *y2) / (x0 - *x2);
				b = y0;
			}
			/*���bֵԽ�磬����127������(0,127)��(*x2, *y2)����*/
			if ((int)FLOAT2INT(256.0 * b) > AFIX_CURVE_MAX_OFFSET)
			{
				float x0 = 0;
				float y0 = 127;
				k = (y0 - *y2) / (x0 - *x2);
				b = y0;
			}
			/*��offset��slope*/
			/*����256��С������ת���ɵ�8λ*/
			short offset = CLIP_VAL((int)FLOAT2INT(256.0 * b), AFIX_CURVE_MIN_OFFSET, AFIX_CURVE_MAX_OFFSET);
			unsigned short slope = CLIP_VAL((int)FLOAT2INT(1024.0 *k), AFIX_CURVE_MIN_SLOPE, AFIX_CURVE_MAX_SLOPE);
			int k_b = ((slope << 16) & 0XFFFF0000) | (offset & 0X0000FFFF);

			//�Ըöθ�ֵ

			fixTable->outAfixRegion[region].outAfixParam[channel].outAfixCurve[i].offset = b;
			fixTable->outAfixRegion[region].outAfixParam[channel].outAfixCurve[i].slope = k;
			fixTable->outAfixRegion[region].outAfixParam[channel].outAfixCurve[i].k_b = k_b;
		}

	}
		/*��lineIdexStart֮ǰ�Ķ���lineIdexStart��ֵ��ֵ*/
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

		/*��lineIdexEnd֮��Ķ���lineIdexEnd-1��ֵ��ֵ,
		* ���ｫlineIdexEnd��ʼ��ΪAFIX_TABLE_CURV_NUM������������£�gr��gb�Ľ�������������ȫ�����������������Ҫ�����ｫû�м�������ĵ�
		* ����һ�θ�ֵ������������£�lineIdexEnd��ʼ��Ϊ0�ᵼ�º��潫���ν���ϵ����ֵ��0���Ӷ�������ĳЩ�����³��ַ��������*/
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

		/*����Ƿ��л�û��ֵk,b���߶�*/
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

	//���ָ��
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
		/*��i��������*/
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


/*��a1�ұ�����ĵ�*/
static int ALG_searchRightPoint(unsigned int keypoint, ALG_In_AfixRegion *sample, int curRegion, int channel, int*rightIdex)
{
	float *start_d0 = NULL;
	float *y = NULL;
	int step = 0;
	int i = 0;
	int ret = OSA_EFAIL;

	step = sizeof(ALG_In_AfixRegion) / sizeof(float);

	//���ָ��
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
		/*��i��������*/
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
