#include "alg_calcMap.h"
#include "alg_calcBadColumnMap.h"
#include "file.h"
#include "alg_spcLog.h"
#if 0
#define CLIP(_val, _min, _max) ((_val)<(_min) ? (_min) : ((_val)>(_max)?(_max):(_val)))
#define ABS(_val) ((_val)>0?(_val):(-(_val)))
#define DIV(a,b) (((b) == 0) ? 0 : (a) / (b))
#endif

#define MAX(a,b) (a>b? a:b)

static void QuickSort(int* values, const int lo, const int hi);
static int AvgFilter(int* values, const int N);
static void generateMap_Raw(unsigned short *res, int imgHeight, int imgWidth, int threshold, int rawType, unsigned char *raw);
static void generateMap_Raw_cxp(unsigned short *res, int imgHeight, int imgWidth, int threshold, int rawType, unsigned char *raw);
//检测入口
char path[24];
int generateMap(struct SPC_BADPOINT_RESOUCE *pImageBuffer, struct SPC_BADPOINTINFOS *badPonitInfo)
{
    uint64_t rdSize=0;
	int imgHeight = badPonitInfo->height;
	int imgWidth = badPonitInfo->width;
	int threshold = 0;
	int rawType = badPonitInfo->rawType;
	int badColumnThr = 0;
	int badLineThr = 0;
	int flag_cxp = badPonitInfo->flag_CXP;
	
	unsigned short *res = NULL;
	int i = 0;
	int j = 0;

	badPonitInfo->imageNumber = 1;
    //一张坏点图
    badPonitInfo->raw[0] = (unsigned char *)malloc(imgHeight * imgWidth * sizeof(unsigned char));
    if (NULL == badPonitInfo->raw[0])
	{
        alg_spcLogf(Log_Error,"%s-%d-memory apply fail\n",__FUNCTION__,__LINE__);
		return -1;
	}
    memset(badPonitInfo->raw[0], 0, imgHeight * imgWidth * sizeof(unsigned char));
    res = (unsigned short *)malloc(imgHeight * imgWidth * sizeof(unsigned short));
    if (NULL == res)
	{
        alg_spcLogf(Log_Error,"%s-%d-memory apply fail\n",__FUNCTION__,__LINE__);
		return -1;
	}
    if (badPonitInfo->needBadColumnCorrect)
	{	
            //列矫正待修改
         badPonitInfo->badRaw[0] = (unsigned char *)malloc(imgHeight * imgWidth * sizeof(unsigned char));
         memset(badPonitInfo->badRaw[0], 0, imgHeight * imgWidth * sizeof(unsigned char));
    }
	for (i = 0; i < pImageBuffer->imageNumber; i++)
	{
		threshold = pImageBuffer->Thr[i] << 4;
		badColumnThr = pImageBuffer->badColumnThr[i] << 4;
		badLineThr = pImageBuffer->badLineThr[i] << 4;
        //*读取图像
        sprintf(path,"spcImData//imSrc_%d.raw",i);
        memset(res,0,imgHeight * imgWidth * sizeof(unsigned short));
		rdSize = readBinaryFileData((char *)path,(unsigned char *)res,imgHeight * imgWidth * sizeof(unsigned short));
	    if(rdSize != imgHeight * imgWidth * sizeof(unsigned short))
        {
            alg_spcLogf(Log_Error,"%s-%d-read image data fail\n",__FUNCTION__,__LINE__);
            free(res);
		    return -1;
        }
        alg_spcLogf(Log_Neet,"%s-%d-load image <%s> sucess\n",__FUNCTION__,__LINE__,path);
		generateMap_Raw(res, imgHeight, imgWidth, threshold, rawType, badPonitInfo->raw[0]);
        if (badPonitInfo->needBadColumnCorrect)
		{	
			badPonitInfo->badRaw[i + 1] = (unsigned char *)malloc(imgHeight * imgWidth * sizeof(unsigned char));
			if (NULL == badPonitInfo->raw[i + 1])
			{
				return -1;
			}
			memcpy(badPonitInfo->badRaw[i + 1],badPonitInfo->raw[i + 1],imgHeight * imgWidth * sizeof(unsigned char));
			judgebadPointsIsbadColumn(badPonitInfo->badRaw[i + 1], imgHeight, imgWidth,rawType);

			generateBadColumnMap_Raw(res, imgHeight, imgWidth,badColumnThr, rawType, badPonitInfo->badRaw[i + 1]);
		}
	}
    free(res);
	//坏点、坏列融合，给相机用
	if (badPonitInfo->needBadColumnCorrect)
	{
        //待处理
		badPonitInfo->badRaw[0] = (unsigned char *)malloc(imgHeight * imgWidth * sizeof(unsigned char));
		if (NULL == badPonitInfo->badRaw[0])
		{
			return -1;
		}
		memset(badPonitInfo->badRaw[0], 0, imgHeight * imgWidth * sizeof(unsigned char));

		for (i = 0; i < imgHeight * imgWidth; i++)
		{
			for (j = 0; j < badPonitInfo->imageNumber; j++)
			{
				badPonitInfo->badRaw[0][i] = MAX(badPonitInfo->badRaw[0][i],badPonitInfo->badRaw[j + 1][i]);

			}

		}
	}
	

	badPonitInfo->badColumnSum = 0;
	badPonitInfo->badPointSum = 0;
	
	for (i = 0; i < imgHeight * imgWidth; i++)
	{
		if (1 == badPonitInfo->raw[0][i])
		{
			badPonitInfo->badPointSum++;
		}
		else if (badPonitInfo->needBadColumnCorrect)
		{
			if (2 == badPonitInfo->badRaw[0][i])
			{
				badPonitInfo->badColumnSum++;
			}
		
		}
	}
	
	if (badPonitInfo->needBadColumnCorrect)
	{
		badPonitInfo->badColumnSum = badPonitInfo->badColumnSum / (imgHeight/2);
	}
	return 0;
}

#if 0
int generateBadPointBadColumnMap(struct SPC_BADPOINT_RESOUCE *pImageBuffer,  struct SPC_BADPOINTINFOS *badPonitInfo, struct SPC_BADCOLUMNINFOS *badColumnInfos)
{
	int imgHeight = badPonitInfo->height;
	int imgWidth = badPonitInfo->width;
	int threshold = 0;
	int rawType = badPonitInfo->rawType;
	int badColumnThr = 0;

	unsigned char *raw = (unsigned char *)malloc(imgHeight * imgWidth * sizeof(unsigned char));
	if (NULL == raw)
	{
		return -1;
	}
	memset(raw, 0, imgHeight * imgWidth * sizeof(unsigned char));
	unsigned short *res = NULL;
	
	for (int i = 0; i < pImageBuffer->imageNumber; i++)
	{
		threshold = pImageBuffer->Thr[i] << 4;
		badColumnThr = pImageBuffer->badColumnThr[i] << 4;
		res = pImageBuffer->pBuffer[i];

		generateMap_Raw(res, imgHeight, imgWidth, threshold, rawType, raw);

		judgebadPointsIsbadColumn(raw, imgHeight, imgWidth,rawType);

		generateBadColumnMap_Raw(res, imgHeight, imgWidth,badColumnThr, rawType, raw);
	}
			
	badPonitInfo->raw[0] = raw;
	badColumnInfos->raw = raw;
	return 0;
} 
#endif

static void generateMap_Raw(unsigned short *res, int imgHeight, int imgWidth, int threshold, int rawType, unsigned char *raw)
{
	int i = 0, j = 0, m =0, n = 0;
	int xIdx = 0, yIdx = 0, dataIdx = 0;
	int Vx = 0;
	int medianArr[49] = {0}; //7x7中值滤波数据
	if (SPC_RAW_TYPE_BW == rawType)	// 黑白raw
	{
		for (i = 0; i < imgHeight; i++)
		{
			for (j = 0; j < imgWidth; j++)
			{
				dataIdx = 0;
				if ((i < 3) || (i >= imgHeight - 3) || (j < 3) || (j >= imgWidth - 3))	//最外围三行/三列用 3x3中值滤波
				{
					for (m = -1; m <= 1; m++)
					{
						for (n = -1; n <= 1; n++)
						{
							yIdx = i + m;
							xIdx = j + n;
							if (yIdx < 0)
							{
								yIdx += 2;
							}
							if (yIdx >(imgHeight - 1))
							{
								yIdx -= 2;
							}
							if (xIdx < 0)
							{
								xIdx += 2;
							}
							if (xIdx >(imgWidth - 1))
							{
								xIdx -= 2;
							}
							medianArr[dataIdx++] = (int)res[yIdx * imgWidth + xIdx];
						}
					}
					
					QuickSort(medianArr, 0, 8);

					Vx = (int)res[i * imgWidth + j];
					Vx -= medianArr[4];
					if (ABS(Vx) >= threshold)
					{
                        if( !(*raw) )
                        {
                            *raw = 1;
                        }
					}
				}
				else  //中间的用7x7中值滤波
				{
					for (m = -3; m <= 3; m++)
					{
						for (n = -3; n <= 3; n++)
						{
							yIdx = CLIP(i + m, 0, imgHeight - 1);
							xIdx = CLIP(j + n, 0, imgWidth - 1);
							medianArr[dataIdx++] = (int)res[yIdx * imgWidth + xIdx];
						}
					}

					QuickSort(medianArr, 0, 48);
					Vx = (int)res[i * imgWidth + j];
					Vx -= medianArr[24];
					if (ABS(Vx) >= threshold)
					{
						if( !(*raw) )
                        {
                            *raw = 1;
                        }
					}
				}
				++raw;
			}
		}
	}
	else //彩色sensor
	{
		for (i = 0; i < imgHeight; i += 2)
		{
			unsigned short *pData0 = res + i * imgWidth;
			unsigned short *pData1 = pData0 + 1;
			unsigned short *pData2 = res + (i + 1) * imgWidth;
			unsigned short *pData3 = pData2 + 1;

			unsigned char *raw0 = raw + i * imgWidth;
			unsigned char *raw1 = raw0 + 1;
			unsigned char *raw2 = raw + (i + 1) * imgWidth;
			unsigned char *raw3 = raw2 + 1;

			for (j = 0; j < imgWidth; j += 2)
			{
				if ((i < 4) || (i >= imgHeight - 4) || (j < 4) || (j >= imgWidth - 4))	//最外围三行/三列用 3x3中值滤波
				{
					//第一个点
					dataIdx = 0;
					for (m = -2; m <= 2; m+=2)
					{
						for (n = -2; n <= 2; n+=2)
						{
							yIdx = i + m;
							xIdx = j + n;
							if (yIdx < 0)
							{
								yIdx += 4;
							}
							if (yIdx >(imgHeight - 1))
							{
								yIdx -= 4;
							}
							if (xIdx < 0)
							{
								xIdx += 4;
							}
							if (xIdx >(imgWidth - 1))
							{
								xIdx -= 4;
							}
							medianArr[dataIdx++] = (int)res[yIdx * imgWidth + xIdx];
						}
					}
					QuickSort(medianArr, 0, 8);
					Vx = *pData0;
					Vx -= medianArr[4];
					if (ABS(Vx) >= threshold)
					{
                        if( !(*raw0) )
                        {
                            *raw0 = 1;
                        }
					}

					//第二个点
					dataIdx = 0;
					for (m = -2; m <= 2; m += 2)
					{
						for (n = -2; n <= 2; n += 2)
						{
							yIdx = i + m;
							xIdx = j + n + 1;
							if (yIdx < 0)
							{
								yIdx += 4;
							}
							if (yIdx > (imgHeight - 1))
							{
								yIdx -= 4;
							}
							if (xIdx < 0)
							{
								xIdx += 4;
							}
							if (xIdx > (imgWidth - 1))
							{
								xIdx -= 4;
							}
							medianArr[dataIdx++] = (int)res[yIdx * imgWidth + xIdx];
						}
					}
					QuickSort(medianArr, 0, 8);
					Vx = *pData1;
					Vx -= medianArr[4];
					if (ABS(Vx) >= threshold)
					{
                        if( !(*raw1) )
                        {
                            *raw1 = 1;
                        }
					}

					//第三个点
					dataIdx = 0;
					for (m = -2; m <= 2; m += 2)
					{
						for (n = -2; n <= 2; n += 2)
						{
							yIdx = i + m + 1;
							xIdx = j + n;
							if (yIdx < 0)
							{
								yIdx += 4;
							}
							if (yIdx >(imgHeight - 1))
							{
								yIdx -= 4;
							}
							if (xIdx < 0)
							{
								xIdx += 4;
							}
							if (xIdx >(imgWidth - 1))
							{
								xIdx -= 4;
							}
							medianArr[dataIdx++] = (int)res[yIdx * imgWidth + xIdx];							
						}
					}
					QuickSort(medianArr, 0, 8);
					Vx = *pData2;
					Vx -= medianArr[4];
					if (ABS(Vx) >= threshold)
					{
                        if( !(*raw2) )
                        {
                            *raw2 = 1;
                        }
					}

					//第四个点
					dataIdx = 0;
					for (m = -2; m <= 2; m += 2)
					{
						for (n = -2; n <= 2; n += 2)
						{
							yIdx = i + m + 1;
							xIdx = j + n + 1;
							if (yIdx < 0)
							{
								yIdx += 4;
							}
							if (yIdx >(imgHeight - 1))
							{
								yIdx -= 4;
							}
							if (xIdx < 0)
							{
								xIdx += 4;
							}
							if (xIdx >(imgWidth - 1))
							{
								xIdx -= 4;
							}
							medianArr[dataIdx++] = (int)res[yIdx * imgWidth + xIdx];
						}
					}
					QuickSort(medianArr, 0, 8);
					Vx = *pData3;
					Vx -= medianArr[4];
					if (ABS(Vx) >= threshold)
					{
						
                        if( !(*raw3) )
                        {
                            *raw3 = 1;
                        }
					}
				}
				else //中间用5x5的窗口做中值滤波
				{
					//第一个点
					dataIdx = 0;
					for (m = -4; m <= 4; m += 2)
					{
						for (n = -4; n <= 4; n += 2)
						{
							yIdx = CLIP(i + m, 0, imgHeight - 2);
							xIdx = CLIP(j + n, 0, imgWidth - 2);
							medianArr[dataIdx++] = (int)res[yIdx * imgWidth + xIdx];
						}
					}
					QuickSort(medianArr, 0, 24);
					Vx = *pData0;
					Vx -= medianArr[12];
					if (ABS(Vx) >= threshold)
					{
                        if( !(*raw0) )
                        {
                            *raw0 = 1;
                        }
					}

					//第二个点
					dataIdx = 0;
					for (m = -4; m <= 4; m += 2)
					{
						for (n = -4; n <= 4; n += 2)
						{
							yIdx = CLIP(i + m, 0, imgHeight - 2);
							xIdx = CLIP(j + n + 1, 1, imgWidth - 1);
							medianArr[dataIdx++] = (int)res[yIdx * imgWidth + xIdx];
						}
					}
					QuickSort(medianArr, 0, 24);
					Vx = *pData1;
					Vx -= medianArr[12];
					if (ABS(Vx) >= threshold)
					{
						if( !(*raw1) )
                        {
                            *raw1 = 1;
                        }
					}

					//第三个点
					dataIdx = 0;
					for (m = -4; m <= 4; m += 2)
					{
						for (n = -4; n <= 4; n += 2)
						{
							yIdx = CLIP(i + m + 1, 1, imgHeight - 1);
							xIdx = CLIP(j + n, 0, imgWidth - 2);
							medianArr[dataIdx++] = (int)res[yIdx * imgWidth + xIdx];
						}
					}
					QuickSort(medianArr, 0, 24);
					Vx = *pData2;
					Vx -= medianArr[12];
					if (ABS(Vx) >= threshold)
					{
                        if( !(*raw2) )
                        {
                            *raw2 = 1;
                        }
					}

					//第四个点
					dataIdx = 0;
					for (m = -4; m <= 4; m += 2)
					{
						for (n = -4; n <= 4; n += 2)
						{
							yIdx = CLIP(i + m + 1, 1, imgHeight - 1);
							xIdx = CLIP(j + n + 1, 1, imgWidth - 1);
							medianArr[dataIdx++] = (int)res[yIdx * imgWidth + xIdx];
						}
					}
					QuickSort(medianArr, 0, 24);
					Vx = *pData3;
					Vx -= medianArr[12];
					if (ABS(Vx) >= threshold)
					{
                        if( !(*raw3) )
                        {
                            *raw3 = 1;
                        }
					}
				}

				pData0 += 2;
				pData1 += 2;
				pData2 += 2;
				pData3 += 2;

				raw0 += 2;
				raw1 += 2;
				raw2 += 2;
				raw3 += 2;
			}
		}
	}

	return;
}

static void QuickSort(int* values, const int lo, const int hi)
{
	int i = lo, j = hi;
	int v;
	int x = values[(lo + hi) / 2];
	do
	{
		while (values[i]<x) i++;
		while (values[j]>x) j--;
		if (i <= j)
		{
			v = values[i]; values[i] = values[j]; values[j] = v;
			i++; j--;
		}
	} while (i <= j);
	if (lo<j) QuickSort(values, lo, j);
	if (i<hi) QuickSort(values, i, hi);
}

static void generateMap_Raw_cxp(unsigned short *res, int imgHeight, int imgWidth, int threshold, int rawType, unsigned char *raw)
{
	int i = 0, j = 0, m = 0, n = 0;
	int xIdx = 0, yIdx = 0, dataIdx = 0;
	int Vx = 0;
	int avgArr[49] = { 0 }; //7x7均值值滤波数据
	int avgValue = 0;
	if (SPC_RAW_TYPE_BW == rawType)	// 黑白raw
	{
		for (i = 0; i < imgHeight; i++)
		{
			for (j = 0; j < imgWidth; j++)
			{
				dataIdx = 0;
				if ((i < 3) || (i >= imgHeight - 3) || (j < 3) || (j >= imgWidth - 3))	//最外围三行/三列用 3x3均值滤波
				{
					for (m = -1; m <= 1; m++)
					{
						for (n = -1; n <= 1; n++)
						{
							yIdx = i + m;
							xIdx = j + n;
							if (yIdx < 0)
							{
								yIdx += 2;
							}
							if (yIdx >(imgHeight - 1))
							{
								yIdx -= 2;
							}
							if (xIdx < 0)
							{
								xIdx += 2;
							}
							if (xIdx >(imgWidth - 1))
							{
								xIdx -= 2;
							}
							avgArr[dataIdx++] = (int)res[yIdx * imgWidth + xIdx];
						}
					}

					avgValue = AvgFilter(avgArr, 9);

					Vx = (int)res[i * imgWidth + j];
					Vx -= avgValue;
					if (ABS(Vx) >= threshold)
					{
						*raw = 1;
					}
				}
				else  //中间的用7x7均值滤波
				{
					for (m = -3; m <= 3; m++)
					{
						for (n = -3; n <= 3; n++)
						{
							yIdx = CLIP(i + m, 0, imgHeight - 1);
							xIdx = CLIP(j + n, 0, imgWidth - 1);
							avgArr[dataIdx++] = (int)res[yIdx * imgWidth + xIdx];
						}
					}

					avgValue = AvgFilter(avgArr, 49);
					Vx = (int)res[i * imgWidth + j];
					Vx -= avgValue;
					if (ABS(Vx) >= threshold)
					{
						*raw = 1;
					}
				}
				++raw;
			}
		}
	}
	else //彩色sensor
	{
		for (i = 0; i < imgHeight; i += 2)
		{
			unsigned short *pData0 = res + i * imgWidth;
			unsigned short *pData1 = pData0 + 1;
			unsigned short *pData2 = res + (i + 1) * imgWidth;
			unsigned short *pData3 = pData2 + 1;

			unsigned char *raw0 = raw + i * imgWidth;
			unsigned char *raw1 = raw0 + 1;
			unsigned char *raw2 = raw + (i + 1) * imgWidth;
			unsigned char *raw3 = raw2 + 1;

			for (j = 0; j < imgWidth; j += 2)
			{
				if ((i < 4) || (i >= imgHeight - 4) || (j < 4) || (j >= imgWidth - 4))	//最外围三行/三列用 3x3均值滤波
				{
					//第一个点
					dataIdx = 0;
					for (m = -2; m <= 2; m += 2)
					{
						for (n = -2; n <= 2; n += 2)
						{
							yIdx = i + m;
							xIdx = j + n;
							if (yIdx < 0)
							{
								yIdx += 4;
							}
							if (yIdx >(imgHeight - 1))
							{
								yIdx -= 4;
							}
							if (xIdx < 0)
							{
								xIdx += 4;
							}
							if (xIdx >(imgWidth - 1))
							{
								xIdx -= 4;
							}
							avgArr[dataIdx++] = (int)res[yIdx * imgWidth + xIdx];
						}
					}
					avgValue = AvgFilter(avgArr, 9);
					Vx = *pData0;
					Vx -= avgValue;
					if (ABS(Vx) >= threshold)
					{
						*raw0 = 1;
					}

					//第二个点
					dataIdx = 0;
					for (m = -2; m <= 2; m += 2)
					{
						for (n = -2; n <= 2; n += 2)
						{
							yIdx = i + m;
							xIdx = j + n + 1;
							if (yIdx < 0)
							{
								yIdx += 4;
							}
							if (yIdx >(imgHeight - 1))
							{
								yIdx -= 4;
							}
							if (xIdx < 0)
							{
								xIdx += 4;
							}
							if (xIdx >(imgWidth - 1))
							{
								xIdx -= 4;
							}
							avgArr[dataIdx++] = (int)res[yIdx * imgWidth + xIdx];
						}
					}
					avgValue = AvgFilter(avgArr, 9);
					Vx = *pData1;
					Vx -= avgValue;
					if (ABS(Vx) >= threshold)
					{
						*raw1 = 1;
					}

					//第三个点
					dataIdx = 0;
					for (m = -2; m <= 2; m += 2)
					{
						for (n = -2; n <= 2; n += 2)
						{
							yIdx = i + m + 1;
							xIdx = j + n;
							if (yIdx < 0)
							{
								yIdx += 4;
							}
							if (yIdx >(imgHeight - 1))
							{
								yIdx -= 4;
							}
							if (xIdx < 0)
							{
								xIdx += 4;
							}
							if (xIdx >(imgWidth - 1))
							{
								xIdx -= 4;
							}
							avgArr[dataIdx++] = (int)res[yIdx * imgWidth + xIdx];
						}
					}
					avgValue = AvgFilter(avgArr, 9);
					Vx = *pData2;
					Vx -= avgValue;
					if (ABS(Vx) >= threshold)
					{
						*raw2 = 1;
					}

					//第四个点
					dataIdx = 0;
					for (m = -2; m <= 2; m += 2)
					{
						for (n = -2; n <= 2; n += 2)
						{
							yIdx = i + m + 1;
							xIdx = j + n + 1;
							if (yIdx < 0)
							{
								yIdx += 4;
							}
							if (yIdx >(imgHeight - 1))
							{
								yIdx -= 4;
							}
							if (xIdx < 0)
							{
								xIdx += 4;
							}
							if (xIdx >(imgWidth - 1))
							{
								xIdx -= 4;
							}
							avgArr[dataIdx++] = (int)res[yIdx * imgWidth + xIdx];
						}
					}
					avgValue = AvgFilter(avgArr, 9);
					Vx = *pData3;
					Vx -= avgValue;
					if (ABS(Vx) >= threshold)
					{
						*raw3 = 1;
					}
				}
				else //中间用5x5的窗口做均值滤波
				{
					//第一个点
					dataIdx = 0;
					for (m = -4; m <= 4; m += 2)
					{
						for (n = -4; n <= 4; n += 2)
						{
							yIdx = CLIP(i + m, 0, imgHeight - 2);
							xIdx = CLIP(j + n, 0, imgWidth - 2);
							avgArr[dataIdx++] = (int)res[yIdx * imgWidth + xIdx];
						}
					}
					avgValue = AvgFilter(avgArr, 25);
					Vx = *pData0;
					Vx -= avgValue;
					if (ABS(Vx) >= threshold)
					{
						*raw0 = 1;
					}

					//第二个点
					dataIdx = 0;
					for (m = -4; m <= 4; m += 2)
					{
						for (n = -4; n <= 4; n += 2)
						{
							yIdx = CLIP(i + m, 0, imgHeight - 2);
							xIdx = CLIP(j + n + 1, 1, imgWidth - 1);
							avgArr[dataIdx++] = (int)res[yIdx * imgWidth + xIdx];
						}
					}
					avgValue = AvgFilter(avgArr, 25);
					Vx = *pData1;
					Vx -= avgValue;
					if (ABS(Vx) >= threshold)
					{
						*raw1 = 1;
					}

					//第三个点
					dataIdx = 0;
					for (m = -4; m <= 4; m += 2)
					{
						for (n = -4; n <= 4; n += 2)
						{
							yIdx = CLIP(i + m + 1, 1, imgHeight - 1);
							xIdx = CLIP(j + n, 0, imgWidth - 2);
							avgArr[dataIdx++] = (int)res[yIdx * imgWidth + xIdx];
						}
					}
					avgValue = AvgFilter(avgArr, 25);
					Vx = *pData2;
					Vx -= avgValue;
					if (ABS(Vx) >= threshold)
					{
						*raw2 = 1;
					}

					//第四个点
					dataIdx = 0;
					for (m = -4; m <= 4; m += 2)
					{
						for (n = -4; n <= 4; n += 2)
						{
							yIdx = CLIP(i + m + 1, 1, imgHeight - 1);
							xIdx = CLIP(j + n + 1, 1, imgWidth - 1);
							avgArr[dataIdx++] = (int)res[yIdx * imgWidth + xIdx];
						}
					}
					avgValue = AvgFilter(avgArr, 25);
					Vx = *pData3;
					Vx -= avgValue;
					if (ABS(Vx) >= threshold)
					{
						*raw3 = 1;
					}
				}

				pData0 += 2;
				pData1 += 2;
				pData2 += 2;
				pData3 += 2;

				raw0 += 2;
				raw1 += 2;
				raw2 += 2;
				raw3 += 2;
			}
		}
	}

	return;
}
static int AvgFilter(int* values, const int N)
{
	int i = 0;
	int sum = 0;
	for (i = 0; i < N; i++)
	{
		sum += values[i];
	}
	return (int)(sum / N);
}















