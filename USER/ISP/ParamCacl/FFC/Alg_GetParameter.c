/* ========================================================================== */
/*                             头文件区                                       */
/* ========================================================================== */

#include "Alg_GetParameter.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef FLOAT2INT
#define FLOAT2INT(a) ((int)( (a >= 0) ? (a + 0.5) : (a - 0.5) ))
#endif

#ifndef CLIP_VAL
#define CLIP_VAL(a, low, high) ((a) < (low) ? (low) : ( (a) > (high) ? (high) : (a) ))
#endif

#define SAFE_FREE(p) {if (p!=NULL) free(p); p=NULL;}

/* ========================================================================== */
/*                          函数声明区                                        */
/* ========================================================================== */

static void Region_getParamKB(unsigned int* pKK, unsigned int* pBB, unsigned short* pKB, int height_scale,int width_scale, int nHeight, int nWidth);

static void Region_getParamBB(double * pB, unsigned int* pBB, int height_scale,int width_scale, int nHeight, int nWidth, int nBits);

static void Region_getParamKK(double * pK, unsigned int* pKK, int height_scale,int width_scale, int nHeight, int nWidth);

static void Region_getParamB(int pDst, double * pBlack, double * pK, double * pB, int height_scale,int width_scale, int nHeight, int nWidth);

static void Region_getParamK(int diff, double * pGrey, double * pBlack, double * pK, int height_scale,int width_scale, int nHeight, int nWidth);

static void Region_getParamK_29k(int diff, double * pGrey, double * pBlack, double * pK, unsigned int* pKK, int height_scale,int width_scale, int nHeight, int nWidth);

static void Region_getParamB_29k(int pDst, double * pBlack, double * pK, double * pB, unsigned int* pBB, int height_scale,int width_scale, int nHeight, int nWidth, int nBits);

static void Region_getParamKB_29k(unsigned int* pKK, unsigned int* pBB, unsigned int* pKB, unsigned char *pFFCTable, int height_scale,int width_scale, int nHeight, int nWidth);

static void Region_getParamKB_4byte(unsigned int* pKK, unsigned int* pBB, unsigned int* pKB, unsigned char * pFFCTable, int height_scale,int width_scale, int nHeight, int nWidth);

static void Region_getParamKB_dcc(unsigned int* pKK, double * pBlack, unsigned int* pKB, unsigned char * pFFCTable, int height_scale,int width_scale, int nHeight, int nWidth, int nBits);

static void Region_getRegionData(double* src, double* dst, int height_scale,int width_scale, int nHeight, int nWidth);

static void Region_Process(ALG_FFCParam *pFFCParam, ALG_FFCTable *pFFCTable);

int ALG_GetParameterRun(ALG_FFCParam *pFFCParam, ALG_FFCTable *pFFCTable);
/* ========================================================================== */
/*                          函数定义区                                         */
/* ========================================================================== */

static void Region_getParamKB_out(unsigned short* pKB, unsigned char* pKB1, int height_scale,int width_scale, int nHeight, int nWidth)
{
	int i;
	int h_region_num = 0, w_region_num = 0;
	h_region_num = nHeight / height_scale;
	w_region_num = nWidth / width_scale;
	for (i = 0; i < h_region_num*w_region_num; i = i + 2)
	{
		pKB1[2*i+0] = (unsigned char)(pKB[i+1]>>8);
		pKB1[2*i+1]	= (unsigned char)pKB[i+1];
		pKB1[2*i+2]	= (unsigned char)(pKB[i]>>8);
		pKB1[2*i+3]	= (unsigned char)pKB[i];
	}
}

static void Region_getParamKB(unsigned int* pKK, unsigned int* pBB, unsigned short* pKB, int height_scale,int width_scale, int nHeight, int nWidth)
{
	int i,j;
	unsigned int a,b;
	int h_region_num = 0, w_region_num = 0;
	h_region_num = nHeight / height_scale;
	w_region_num = nWidth / width_scale;
	for (i = 0; i < h_region_num; i++)
	{
		for (j = 0; j < w_region_num; j++)
		{
			a = pKK[i*w_region_num + j];
			b = pBB[i*w_region_num + j];
			pKB[i*w_region_num + j] = (unsigned short)((a & 0x3ff) << 6) | (b & 0x3f);
		}
	}
}

static void Region_getParamBB(double * pB, unsigned int* pBB, int height_scale,int width_scale, int nHeight, int nWidth, int nBits)
{
	int i,j;
	int tmp = 0;
	int h_region_num = 0, w_region_num = 0;
	h_region_num = nHeight / height_scale;
	w_region_num = nWidth / width_scale;
	for (i = 0; i < h_region_num; i++)
	{
		for (j = 0; j < w_region_num; j++)
		{
			if(8 == nBits)
			{
				pB[i*w_region_num + j] = pB[i*w_region_num + j] * 4;
			}
			if(12 == nBits)
			{
				pB[i*w_region_num + j] = pB[i*w_region_num + j] / 4;
			}
			tmp = CLIP_VAL(FLOAT2INT(pB[i*w_region_num + j]), -31, 31);
			if(tmp>=0)
			{
				pBB[i*w_region_num + j] = tmp;
			}
			else
			{
				pBB[i*w_region_num + j] = 64 + tmp;
			}
		}
	}
}

static void Region_getParamKK(double * pK, unsigned int* pKK, int height_scale,int width_scale, int nHeight, int nWidth)
{
	int i,j;
	int h_region_num = 0, w_region_num = 0;
	h_region_num = nHeight / height_scale;
	w_region_num = nWidth / width_scale;
	for (i = 0; i < h_region_num; i++)
	{
		for (j = 0; j < w_region_num; j++)
		{
			pKK[i*w_region_num + j] = CLIP_VAL(FLOAT2INT(pK[i*w_region_num + j] * 512), 0, 1023);
		}
	}
}

static void Region_getParamB(int pDst, double * pBlack, double * pK, double * pB, int height_scale,int width_scale, int nHeight, int nWidth)
{
	int i,j;
	int h_region_num = 0, w_region_num = 0;
	h_region_num = nHeight / height_scale;
	w_region_num = nWidth / width_scale;
	for (i = 0; i < h_region_num; i++)
	{
		for (j = 0; j < w_region_num; j++)
		{
			pB[i*w_region_num + j] = pDst - pBlack[i*w_region_num + j] * pK[i*w_region_num + j];
		}
	}
}

static void Region_getParamK(int diff, double * pGrey, double * pBlack, double * pK, int height_scale,int width_scale, int nHeight, int nWidth)
{
	int i,j;
	int h_region_num = 0, w_region_num = 0;
	h_region_num = nHeight / height_scale;
	w_region_num = nWidth / width_scale;
	for (i = 0; i < h_region_num; i++)
	{
		for (j = 0; j < w_region_num; j++)
		{
			pK[i*w_region_num + j] = CLIP_VAL(diff / (pGrey[i*w_region_num + j] - pBlack[i*w_region_num + j]), 0, 1.998);
		}
	}
}

static void Region_getRegionData(double* src, double* dst, int height_scale,int width_scale, int nHeight, int nWidth)
{
	int i,j,m,n;
	
	double tmp = .0f;
	int h_region_num = 0, w_region_num = 0;
	h_region_num = nHeight / height_scale;
	w_region_num = nWidth / width_scale;
	for (i = 0; i <h_region_num; i++)
	{
		for (j = 0; j < w_region_num; j++)
		{
			tmp = .0f;
			for (m = 0; m < height_scale; m++)
			{
				for (n = 0; n < width_scale; n++)
				{
					tmp += src[(i*height_scale+m)*nWidth + j*width_scale+n];
				}
			}
			dst[i*w_region_num + j] = tmp / (height_scale*width_scale);
		}	
	}
}

static void Region_getParamK_29k(int diff, double * pGrey, double * pBlack, double * pK, unsigned int* pKK, int height_scale,int width_scale, int nHeight, int nWidth)
{
	int i, j;
	int h_region_num = 0, w_region_num = 0;
	h_region_num = nHeight / height_scale;
	w_region_num = nWidth / width_scale;
	for (i = 0; i < h_region_num; i++)
	{
		for (j = 0; j < w_region_num; j++)
		{
			if (i == 2554 && j == 636)
			{
				printf("ttt");
			}
			pK[i*w_region_num + j] = CLIP_VAL(diff / (pGrey[i*w_region_num + j] - pBlack[i*w_region_num + j]), 0, 1.9997);
			pKK[i*w_region_num + j] = CLIP_VAL(FLOAT2INT(pK[i*w_region_num + j] * 4096), 0, 8191);
		}
	}
}

static void Region_getParamB_29k(int pDst, double * pBlack, double * pK, double * pB, unsigned int* pBB, int height_scale,int width_scale, int nHeight, int nWidth, int nBits)
{
	int i, j;
	int tmp = 0;
	int h_region_num = 0, w_region_num = 0;
	h_region_num = nHeight / height_scale;
	w_region_num = nWidth / width_scale;
	for (i = 0; i < h_region_num; i++)
	{
		for (j = 0; j < w_region_num; j++)
		{
			pB[i*w_region_num + j] = pDst - pBlack[i*w_region_num + j] * pK[i*w_region_num + j];

			if (8 == nBits)
			{
				pB[i*w_region_num + j] = pB[i*w_region_num + j] * 16;
			}
			if (10 == nBits)
			{
				pB[i*w_region_num + j] = pB[i*w_region_num + j] * 4;
			}
			/********
				ISP底层FFC实现对B的处理上，在s10的基础上乘2，
				故此，在算法层面对B除以2，以便和底层实现匹配
				wang_fulai(2019_10_21)
			********/
			pB[i*w_region_num + j] = pB[i*w_region_num + j] / 2;
			tmp = CLIP_VAL(FLOAT2INT(pB[i*w_region_num + j]), -1024, 1023);
			if (tmp >= 0)
			{
				pBB[i*w_region_num + j] = tmp;
			}
			else
			{
				pBB[i*w_region_num + j] = 2048 + tmp;
			}
		}
	}
}

static void Region_getParamKB_29k(unsigned int* pKK, unsigned int* pBB, unsigned int* pKB, unsigned char * pFFCTable, int height_scale,int width_scale, int nHeight, int nWidth)
{
	int i, j;
	int n;
	unsigned int a, b;
	int h_region_num = 0, w_region_num = 0;
	h_region_num = nHeight / height_scale;
	w_region_num = nWidth / width_scale;
	for (i = 0; i < h_region_num; i++)
	{
		for (j = 0; j < w_region_num; j++)
		{
			a = pKK[i*w_region_num + j];
			b = pBB[i*w_region_num + j];
			pKB[i*w_region_num + j] = (unsigned int)((a & 0x1fff) << 11) | (b & 0x7ff);
		}
	}
	for (n = 0; n < h_region_num*w_region_num; n++)
	{
		pFFCTable[3 * n + 0] = (unsigned char)(pKB[n] >> 16);
		pFFCTable[3 * n + 1] = (unsigned char)(pKB[n] >> 8);
		pFFCTable[3 * n + 2] = (unsigned char)(pKB[n]);

	}
}
static void Region_getPickedParamKB_29k(unsigned int* pKK, unsigned int* pBB, unsigned int* pKB, unsigned char * pFFCTable, int height_scale,int width_scale, int nHeight, int nWidth)
{
	int i, j;
	int n;
	unsigned int a, b;
	int h_region_num = 0, w_region_num = 0;
    unsigned int cnt = 0;
	h_region_num = nHeight / height_scale;
	w_region_num = nWidth / width_scale;
	for (i = 0; i < h_region_num; i++)
	{
		for (j = 0; j < w_region_num; j++)
		{
			a = pKK[i*w_region_num + j];
			b = pBB[i*w_region_num + j];
			pKB[i*w_region_num + j] = (unsigned int)((a & 0x1fff) << 11) | (b & 0x7ff);
		}
	}
    for(i = 0;i<h_region_num;i++)
    {
        for(j = 0;j<w_region_num;j+=2)
        {
            pFFCTable[3 * cnt + 0] = (unsigned char)(pKB[ i*w_region_num +j] >> 16);
		    pFFCTable[3 * cnt + 1] = (unsigned char)(pKB[ i*w_region_num +j] >> 8);
		    pFFCTable[3 * cnt + 2] = (unsigned char)(pKB[ i*w_region_num +j]);
            cnt ++;
        }
    }
	return ;
}
static void Region_getParamKB_4byte(unsigned int* pKK, unsigned int* pBB, unsigned int* pKB, unsigned char * pFFCTable, int height_scale,int width_scale, int nHeight, int nWidth)
{
	int i, j;
	int n;
	unsigned int a, b;
	int h_region_num = 0, w_region_num = 0;
	h_region_num = nHeight / height_scale;
	w_region_num = nWidth / width_scale;
	for (i = 0; i < h_region_num; i++)
	{
		for (j = 0; j < w_region_num; j++)
		{
			a = pKK[i*w_region_num + j];
			b = pBB[i*w_region_num + j];
			pKB[i*w_region_num + j] = (unsigned int)((a & 0x1fff) << 11) | (b & 0x7ff);
		}
	}
	for (n = 0; n < h_region_num*w_region_num; n++)
	{
		pFFCTable[4 * n + 0] = (unsigned char)(pKB[n] >> 24);
		pFFCTable[4 * n + 1] = (unsigned char)(pKB[n] >> 16);
		pFFCTable[4 * n + 2] = (unsigned char)(pKB[n] >> 8);
		pFFCTable[4 * n + 2] = (unsigned char)(pKB[n]);
	}
}

static void Region_getParamKB_dcc(unsigned int* pKK, double * pBlack, unsigned int* pKB, unsigned char * pFFCTable, int height_scale,int width_scale, int nHeight, int nWidth, int nBits)
{
	int i, j;
	int n;
	unsigned int a, b;
	int h_region_num = 0, w_region_num = 0;
	h_region_num = nHeight / height_scale;
	w_region_num = nWidth / width_scale;
	for (i = 0; i < h_region_num; i++)
	{
		for (j = 0; j < w_region_num; j++)
		{
			
			if (8 == nBits)
			{
				b = (unsigned int)pBlack[i*w_region_num + j] * 4;
			}
			if (10 == nBits)
			{
				b = (unsigned int)pBlack[i*w_region_num + j];
			}
			if (12 == nBits)
			{
				b = (unsigned int)pBlack[i*w_region_num + j] / 4;
			}
			
			a = pKK[i*w_region_num + j] >> 4;

			if (i == 2554 && j == 636)
			{
				/*FILE *fp = fopen("D:\\KB.txt", "a+");
				char tempBuff[64] = { 0 };
				sprintf("K : %d ,B: %d\n", a, b);
				fwrite(tempBuff, 1, strlen(tempBuff), fp);
				fflush(fp);
				fclose(fp);*/

			}

			pKB[i*w_region_num + j] = (unsigned int)(((a & 0x1ff) << 23) | ((b & 0x3ff) << 12));
		}
	}
	for (n = 0; n < h_region_num*w_region_num; n++)
	{
		pFFCTable[4 * n + 0] = (unsigned char)(pKB[n] >> 0);
		pFFCTable[4 * n + 1] = (unsigned char)(pKB[n] >> 8);
		pFFCTable[4 * n + 2] = (unsigned char)(pKB[n] >> 16);
		pFFCTable[4 * n + 3] = (unsigned char)(pKB[n] >> 24);
	}
}

static void Region_Process(ALG_FFCParam *pFFCParam, ALG_FFCTable *pFFCTable)
{
	//{
	//	int nBits = (8 == pFFCParam->nBits) ? 1 : 2;
	//	FILE *fp = NULL;
	//	fp = fopen("c:\\black.bin", "wb");
	//	fwrite(pFFCParam->blackData, 1, nBits * pFFCParam->nWidth * pFFCParam->nHeight * sizeof(unsigned char), fp);
	//	fflush(fp);
	//	fclose(fp);

	//	fp = fopen("c:\\grey.bin", "wb");
	//	fwrite(pFFCParam->greyData, 1, nBits * pFFCParam->nWidth * pFFCParam->nHeight * sizeof(unsigned char), fp);
	//	fflush(fp);
	//	fclose(fp);
	//}


	double sum = 0;
	int size_region;
	double* pGreyRegion;
	double* pBlackRegion;
	double* pK=NULL;
	double* pB = NULL;
	unsigned char* pGrey;
	unsigned char* pBlack;
	int i,j;

	unsigned int* pKK;
	unsigned int* pBB;
	unsigned short* pKB;
	unsigned char* pKB_out;

	unsigned int* pKB_29k;

	//输入数据
	int size_raw = (pFFCParam->nHeight)*(pFFCParam->nWidth);
	double* pGreyRAW = (double*)malloc(size_raw*sizeof(double));
	double* pBlackRAW = (double*)malloc(size_raw*sizeof(double));
	memset(pGreyRAW, 0, size_raw*sizeof(double));
	memset(pBlackRAW, 0, size_raw*sizeof(double));
	pGrey = (unsigned char*)pFFCParam->greyData;
	pBlack = (unsigned char*)pFFCParam->blackData;
	
	for (i = 0; i < pFFCParam->nHeight; i++)
	{
		for (j = 0; j < pFFCParam->nWidth; j++)
		{
				if (8 == pFFCParam->nBits)
				{
					pGreyRAW[i*pFFCParam->nWidth + j] = (double)(pGrey[i*pFFCParam->nWidth + j]);
					pBlackRAW[i*pFFCParam->nWidth + j] = (double)(pBlack[i*pFFCParam->nWidth + j]);
				}
				else
				{
					pGreyRAW[i*pFFCParam->nWidth + j] = (double)(pGrey[2 * (i*pFFCParam->nWidth + j)]|(pGrey[2 * (i*pFFCParam->nWidth + j)+1]<<8));
					pBlackRAW[i*pFFCParam->nWidth + j] = (double)(pBlack[2 * (i*pFFCParam->nWidth + j)] | (pBlack[2 * (i*pFFCParam->nWidth + j) + 1] << 8));
				}
		}
	}

	//区域均值数据
	size_region = (pFFCParam->nHeight/pFFCParam->region_height_scale)*(pFFCParam->nWidth/pFFCParam->region_width_scale);
	pGreyRegion = (double*)malloc(size_region*sizeof(double));
	pBlackRegion = (double*)malloc(size_region*sizeof(double));
	memset(pGreyRegion, 0, size_region*sizeof(double));
	memset(pBlackRegion, 0, size_region*sizeof(double));
	Region_getRegionData(pGreyRAW, pGreyRegion, pFFCParam->region_height_scale,pFFCParam->region_width_scale, pFFCParam->nHeight, pFFCParam->nWidth);
	Region_getRegionData(pBlackRAW, pBlackRegion, pFFCParam->region_height_scale,pFFCParam->region_width_scale, pFFCParam->nHeight, pFFCParam->nWidth);
	if (pFFCParam->greyDst == 0)
	{
		/**
		使用区域最大值作为目标值
		**/
		int maxGreyRegion = 0;
		for (i = 0; i < size_region; i++)
		{
			if (pGreyRegion[i] > maxGreyRegion)
			{
				maxGreyRegion =(int)pGreyRegion[i];
			}
		}
		pFFCParam->greyDst = maxGreyRegion;
	}
	else
	{
		/**
		使用全图均值作为目标值,由外部传入
		**/
	}
	//老版本韩国定制小面阵系列，K、B系数占两个字节
	if (2 == pFFCParam->kb_byte)
	{
		//K,B系数
		pK = (double*)malloc(size_region*sizeof(double));
		pB = (double*)malloc(size_region*sizeof(double));
		memset(pK, 0, size_region*sizeof(double));
		memset(pB, 0, size_region*sizeof(double));
		Region_getParamK(pFFCParam->greyDst - pFFCParam->blackDst, pGreyRegion, pBlackRegion, pK, pFFCParam->region_height_scale,pFFCParam->region_width_scale, pFFCParam->nHeight, pFFCParam->nWidth);
		Region_getParamB(pFFCParam->blackDst, pBlackRegion, pK, pB, pFFCParam->region_height_scale,pFFCParam->region_width_scale,pFFCParam->nHeight, pFFCParam->nWidth);

		//K,B系数
		pKK = (unsigned int*)malloc(size_region*sizeof(unsigned int));
		pBB = (unsigned int*)malloc(size_region*sizeof(unsigned int));
		memset(pKK, 0, size_region);
		memset(pBB, 0, size_region);
		Region_getParamKK(pK, pKK, pFFCParam->region_height_scale,pFFCParam->region_width_scale, pFFCParam->nHeight, pFFCParam->nWidth);
		Region_getParamBB(pB, pBB, pFFCParam->region_height_scale,pFFCParam->region_width_scale, pFFCParam->nHeight, pFFCParam->nWidth, pFFCParam->nBits);

		pKB = (unsigned short*)malloc(size_region*sizeof(unsigned short));
		memset(pKB, 0, size_region);
		Region_getParamKB(pKK, pBB, pKB, pFFCParam->region_height_scale,pFFCParam->region_width_scale, pFFCParam->nHeight, pFFCParam->nWidth);

		
		pKB_out = (unsigned char*)pFFCTable->pFFCTable;
		memset(pKB_out, 0, size_region * 2);
		Region_getParamKB_out(pKB, pKB_out, pFFCParam->region_height_scale,pFFCParam->region_width_scale, pFFCParam->nHeight, pFFCParam->nWidth);
		SAFE_FREE(pGreyRAW);
		SAFE_FREE(pBlackRAW);
		SAFE_FREE(pGreyRegion);
		SAFE_FREE(pBlackRegion);
		SAFE_FREE(pK);
		SAFE_FREE(pB);
		SAFE_FREE(pKK);
		SAFE_FREE(pBB);
	}
	//新版本29K面阵，K、B系数占三个字节
	else if (3 == pFFCParam->kb_byte)
	{
		//K,B系数

		pK = (double*)malloc(size_region*sizeof(double));
		pB = (double*)malloc(size_region*sizeof(double));
		memset(pK, 0, size_region*sizeof(double));
		memset(pB, 0, size_region*sizeof(double));

		pKK = (unsigned int*)malloc(size_region*sizeof(unsigned int));
		pBB = (unsigned int*)malloc(size_region*sizeof(unsigned int));
		memset(pKK, 0, size_region*sizeof(unsigned int));
		memset(pBB, 0, size_region*sizeof(unsigned int));

		Region_getParamK_29k(pFFCParam->greyDst - pFFCParam->blackDst, pGreyRegion, pBlackRegion, pK, pKK, pFFCParam->region_height_scale,pFFCParam->region_width_scale, pFFCParam->nHeight, pFFCParam->nWidth);
		Region_getParamB_29k(pFFCParam->blackDst, pBlackRegion, pK, pB, pBB, pFFCParam->region_height_scale,pFFCParam->region_width_scale,pFFCParam->nHeight, pFFCParam->nWidth, pFFCParam->nBits);

		pKB_29k = (unsigned int*)malloc(size_region*sizeof(unsigned int));
		memset(pKB_29k, 0, size_region*sizeof(unsigned int));
        if(!pFFCParam->paramIsPick)
        {
            Region_getParamKB_29k(pKK, pBB, pKB_29k, pFFCTable->pFFCTable, pFFCParam->region_height_scale,pFFCParam->region_width_scale, pFFCParam->nHeight, pFFCParam->nWidth);
        }
        else
        {
            Region_getPickedParamKB_29k(pKK, pBB, pKB_29k, pFFCTable->pFFCTable, pFFCParam->region_height_scale,pFFCParam->region_width_scale, pFFCParam->nHeight, pFFCParam->nWidth);
        }
		SAFE_FREE(pGreyRAW);
		SAFE_FREE(pBlackRAW);
		SAFE_FREE(pGreyRegion);
		SAFE_FREE(pBlackRegion);
		SAFE_FREE(pK);
		SAFE_FREE(pB);
		SAFE_FREE(pKK);
		SAFE_FREE(pBB);
		SAFE_FREE(pKB_29k);
	}
	else if (4 == pFFCParam->kb_byte)
	{
		//K,B系数

		pK = (double*)malloc(size_region*sizeof(double));
		pB = (double*)malloc(size_region*sizeof(double));
		memset(pK, 0, size_region*sizeof(double));
		memset(pB, 0, size_region*sizeof(double));

		pKK = (unsigned int*)malloc(size_region*sizeof(unsigned int));
		pBB = (unsigned int*)malloc(size_region*sizeof(unsigned int));
		memset(pKK, 0, size_region*sizeof(unsigned int));
		memset(pBB, 0, size_region*sizeof(unsigned int));

		Region_getParamK_29k(pFFCParam->greyDst - pFFCParam->blackDst, pGreyRegion, pBlackRegion, pK, pKK, pFFCParam->region_height_scale,pFFCParam->region_width_scale, pFFCParam->nHeight, pFFCParam->nWidth);
		Region_getParamB_29k(pFFCParam->blackDst, pBlackRegion, pK, pB, pBB, pFFCParam->region_height_scale,pFFCParam->region_width_scale,pFFCParam->nHeight, pFFCParam->nWidth, pFFCParam->nBits);

		pKB_29k = (unsigned int*)malloc(size_region*sizeof(unsigned int));
		memset(pKB_29k, 0, size_region*sizeof(unsigned int));
	
		Region_getParamKB_dcc(pKK, pBlackRegion, pKB_29k, pFFCTable->pFFCTable, pFFCParam->region_height_scale, pFFCParam->region_width_scale, pFFCParam->nHeight, pFFCParam->nWidth, pFFCParam->nBits);
		

		SAFE_FREE(pGreyRAW);
		SAFE_FREE(pBlackRAW);
		SAFE_FREE(pGreyRegion);
		SAFE_FREE(pBlackRegion);
		SAFE_FREE(pK);
		SAFE_FREE(pB);
		SAFE_FREE(pKK);
		SAFE_FREE(pBB);
		SAFE_FREE(pKB_29k);
	}

}
int ALG_GetParameterMemoryLen(ALG_FFCParam *pFFCParam)
{
	int size = -1;
	int num_x, num_y;
	if (ALG_TYPE_FFC_REGION == pFFCParam->nType)
	{
		num_x = pFFCParam->nWidth / pFFCParam->region_width_scale;
		num_y = pFFCParam->nHeight / pFFCParam->region_height_scale;
        if(pFFCParam->paramIsPick)
        {
            num_x = num_x/2 + num_x%2;
        }
		if(2 == pFFCParam->kb_byte)
		{
			size = num_x*num_y*2;
		}
		else if(3 == pFFCParam->kb_byte)
		{
			size = num_x*num_y*3;			
		}
		else if(4 == pFFCParam->kb_byte)
		{
			size = num_x*num_y*4;			
		}
	}
	else if (ALG_TYPE_FFC_ROW == pFFCParam->nType)
	{
		num_y = pFFCParam->nHeight / pFFCParam->region_height_scale;
		size = 2 * num_y*sizeof(int);
	}

	return size;
}

int ALG_GetParameterRun(ALG_FFCParam *pFFCParam, ALG_FFCTable *pFFCTable)
{
	if (ALG_TYPE_FFC_REGION == pFFCParam->nType)
	{
		Region_Process(pFFCParam, pFFCTable);
	}
	return 0;
}
