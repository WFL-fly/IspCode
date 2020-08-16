#include "alg_spcTool.h"
#include "alg_calcMap.h"
#include "alg_calcCoor.h"
#include "alg_calcCoor_cl.h"
#include "alg_calcBadColumnCoor.h"
#include "alg_spcLog.h"
static boolean CHECK_ERROR_SPC_BADPOINT_RESOUCE(struct SPC_BADPOINT_RESOUCE *pImageBuffer);
static boolean CHECK_ERROR_SPC_BADPOINTINFOS(struct SPC_BADPOINTINFOS *badPonitInfo);
static boolean CHECK_ERROR_SPC_BADCOLUMNINFOS(struct SPC_BADCOLUMNINFOS *badColumnInfos);
static void QuickSortMax(int* values, const int lo, const int hi);


static void QuickSortMax(int* values, const int lo, const int hi)
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
	if (lo<j) QuickSortMax(values, lo, j);
	if (i<hi) QuickSortMax(values, i, hi);
}
void detectBadPointInit()
{
    //创建坏点检测日志文件
    alg_spcLogFileCreate("spcLog.txt");
}
void detectBadPointDestroy()
{
    
    alg_spcLogFileClose();
}
int detectMaxBadPointInfo(struct SPC_Max_BADPOINT_RESOUCE *pImageBufferMax, struct SPC_Max_BADPOINTINFOS *badPonitInfoMax)
{
	int s, i, j, z, Thr_on,xIdx, yIdx, dataIdx, m, n, Vx, type;//s是计算坏点个数的变量
	int nCount=0;
	int medianArr[49] ={0};
	int imgHeight = badPonitInfoMax->Max_height;
	int imgWidth = badPonitInfoMax->Max_width;
	unsigned short *res=NULL; 
	unsigned char  *badRaw =NULL;
    badPonitInfoMax->highBlack_Badraw = (unsigned char *)malloc(imgHeight * imgWidth * sizeof(unsigned char));
    badRaw = badPonitInfoMax->highBlack_Badraw;
	Thr_on = pImageBufferMax->ori_Threshold << 4;
	res = pImageBufferMax->pBuffer_highBlack;
	for (z = 1; z < (imgHeight*imgWidth); z=z+1)
	{
		s=0;
		memset(badRaw,0,imgHeight * imgWidth * sizeof(unsigned char));
		memset(medianArr,0,49 * sizeof(int));
		xIdx = 0;
		yIdx = 0;
		dataIdx = 0;
		m = 0;
		n = 0;
		Vx = 0;
		type = 0;

//-------------------------------------------------------------------	
		for (i = 0;i < imgHeight; i = i + 1)
		{
			for (j = 0;j < imgWidth; j = j + 1)
			{
				 dataIdx = 0;
				 if ((i < 3) || (i >= imgHeight - 3) || (j < 3) || (j >= imgWidth - 3))	
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
									
					QuickSortMax(medianArr, 0, 8);
						
					Vx = (int)res[i * imgWidth + j];
					Vx -= medianArr[4];

					if (ABS(Vx) >= Thr_on)
					{
						badRaw[i * imgWidth + j] = 1;
						s=s+1;
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
						
					QuickSortMax(medianArr, 0, 48);
					Vx = (int)res[i * imgWidth + j];
					Vx -= medianArr[24];
					if (ABS(Vx) >= Thr_on)
					{
						badRaw[i * imgWidth + j] = 1;
						s=s+1;
					}
				}
			}
		}

		if (s > pImageBufferMax->maxBadpointNumber)
		{
			Thr_on=Thr_on+5;
		}
		else 
			break;
	}

	badPonitInfoMax->MaxbadPointSum = s;
	badPonitInfoMax->res_Threshold = Thr_on;

	badPonitInfoMax->max_badPointInfo=(struct SPC_BADPOINTINFO*)malloc(s * sizeof(struct SPC_BADPOINTINFO));
	//printf("坏点总数=%d 迭代阈值=%d \n",s,Thr_on);
	
	for (i = 0;i < imgHeight; i = i + 1)
	{
		for (j = 0;j < imgWidth; j = j + 1)
		{
			if(badPonitInfoMax->highBlack_Badraw[i*imgWidth+j]==1)
			{
				//----------------------判断坏点类型-----------------------------
				//---------判断边界-------
				badPonitInfoMax->max_badPointInfo[nCount].x=j;//max_badPointInfo[i * imgWidth + j].x;
				badPonitInfoMax->max_badPointInfo[nCount].y=i;//max_badPointInfo[i * imgWidth + j].y;
				if(i==0)
				{
					type = 15;
					badPonitInfoMax->max_badPointInfo[nCount].type=type;
				}
				else if (j==0)
				{
					type = 13;
					badPonitInfoMax->max_badPointInfo[nCount].type=type;
				}
				else if (j == imgWidth-1)
				{
					type = 14;
					badPonitInfoMax->max_badPointInfo[nCount].type=type;
				}
				else if (i==imgHeight-1)
				{
					type = 12;
					badPonitInfoMax->max_badPointInfo[nCount].type=type;
				}
				else
				{
					if(badPonitInfoMax->highBlack_Badraw[i*imgWidth+j-imgWidth]==0&&badPonitInfoMax->highBlack_Badraw[i*imgWidth+j+imgWidth]==0&&badPonitInfoMax->highBlack_Badraw[i*imgWidth+j-1]==0&&badPonitInfoMax->highBlack_Badraw[i*imgWidth+j+1]==0)
					{	
						type = 9;
						
						badPonitInfoMax->max_badPointInfo[nCount].type=type;
					}
					else if (badPonitInfoMax->highBlack_Badraw[i*imgWidth+j-1]==0&&badPonitInfoMax->highBlack_Badraw[i*imgWidth+j+1]==0)
					{
						type = 10;
						
						badPonitInfoMax->max_badPointInfo[nCount].type=type;
					}
					else if (badPonitInfoMax->highBlack_Badraw[i*imgWidth+j-imgWidth]==0&&badPonitInfoMax->highBlack_Badraw[i*imgWidth+j+imgWidth]==0)
					{
						type = 11;
						
						badPonitInfoMax->max_badPointInfo[nCount].type=type;
					}
					else if (badPonitInfoMax->highBlack_Badraw[i*imgWidth+j-imgWidth]==0)
					{
						type = 12;
						
						badPonitInfoMax->max_badPointInfo[nCount].type=type;
					}
					else if (badPonitInfoMax->highBlack_Badraw[i*imgWidth+j+1]==0)
					{
						type = 13;
						
						badPonitInfoMax->max_badPointInfo[nCount].type=type;
					}
					else if (badPonitInfoMax->highBlack_Badraw[i*imgWidth+j-1]==0)
					{
						type = 14;
						badPonitInfoMax->max_badPointInfo[nCount].type=type;
						
					}
					else if (badPonitInfoMax->highBlack_Badraw[i*imgWidth+j+imgWidth]==0)
					{
						type = 15;
						
						badPonitInfoMax->max_badPointInfo[nCount].type=type;
					}
				}//判断非边界else
				//------------------------

				//---------------------------------------------------
				nCount++;
				if (nCount>s)
				{
					return 0;
				}
			}
		}
	}
	//system("pause");
	return 0;
}

int deleteMaxBadPointInfo(struct SPC_Max_BADPOINT_RESOUCE *pImageBufferMax, struct SPC_Max_BADPOINTINFOS *badPonitInfoMax)
{
	if (NULL != pImageBufferMax->pBuffer_highBlack)
	{
		free(pImageBufferMax->pBuffer_highBlack);
		pImageBufferMax->pBuffer_highBlack = NULL;
	}
	return 0;

}
int detectBadPointInfo(struct SPC_BADPOINT_RESOUCE *pImageBuffer, struct SPC_BADPOINTINFOS *badPonitInfo)
{
	if (!CHECK_ERROR_SPC_BADPOINT_RESOUCE(pImageBuffer))
	{
		return -1;
	}
	if (!CHECK_ERROR_SPC_BADPOINTINFOS(badPonitInfo))
	{
		return -1;
	}	
	generateMap(pImageBuffer, badPonitInfo);
	getBadPointCoordinate(badPonitInfo);

	if (badPonitInfo->needBadColumnCorrect)
	{
		getBadColumnCoordinate(badPonitInfo);
	}

	return 0;
}


int detectBadPointInfo_CL(struct SPC_BADPOINTINFOS *badPonitInfo)
{
	if (!CHECK_ERROR_SPC_BADPOINTINFOS(badPonitInfo))
	{
		return -1;
	}

	getBadPointCoordinate(badPonitInfo);

	getBadPointInfo_cl(badPonitInfo);

	return 0;
}

int deleteBadPointInfo(struct SPC_BADPOINTINFOS *badPonitInfo)
{
	int i = 0;
	for (i = 0; i <= 16 && i < badPonitInfo->imageNumber; i++)
	{
		if (NULL != badPonitInfo->raw[i])
		{
			free(badPonitInfo->raw[i]);
			badPonitInfo->raw[i] = NULL;
		}
		if (NULL != badPonitInfo->badRaw[i])
		{
			free(badPonitInfo->badRaw[i]);
			badPonitInfo->badRaw[i] = NULL;
		}
		
	}
	if (NULL != badPonitInfo->canNotRepairCoordinate)
	{
		free(badPonitInfo->canNotRepairCoordinate);
		badPonitInfo->canNotRepairCoordinate = NULL;
	}
	if (NULL != badPonitInfo->canRepairCoordinate)
	{
		free(badPonitInfo->canRepairCoordinate);
		badPonitInfo->canRepairCoordinate = NULL;
	}

	if (NULL != badPonitInfo->canNotRepairBadColumnCoordinate)
	{
		free(badPonitInfo->canNotRepairBadColumnCoordinate);
		
		badPonitInfo->canNotRepairBadColumnCoordinate = NULL;
	}
	if (NULL != badPonitInfo->canRepairBadColumnCoordinate)
	{
		free(badPonitInfo->canRepairBadColumnCoordinate);
		badPonitInfo->canRepairBadColumnCoordinate = NULL;
	}
	if (NULL != badPonitInfo->canRepairPointCooratBadCol)
	{
		free(badPonitInfo->canRepairPointCooratBadCol);
		badPonitInfo->canRepairPointCooratBadCol = NULL;
	}
	
	return 0;
}

int deleteBadPointInfo_CL(struct SPC_BADPOINTINFOS *badPonitInfo)
{
	if (NULL != badPonitInfo->canNotRepairCoordinate)
	{
		free(badPonitInfo->canNotRepairCoordinate);
		badPonitInfo->canNotRepairCoordinate = NULL;
	}
	if (NULL != badPonitInfo->canRepairCoordinate)
	{
		free(badPonitInfo->canRepairCoordinate);
		badPonitInfo->canRepairCoordinate = NULL;
	}

	if (NULL != badPonitInfo->canRepairInfo_CL[0])
	{
		free(badPonitInfo->canRepairInfo_CL[0]);
		badPonitInfo->canRepairInfo_CL[0] = NULL;
	}

	if (NULL != badPonitInfo->canRepairInfo_CL[1])
	{
		free(badPonitInfo->canRepairInfo_CL[1]);
		badPonitInfo->canRepairInfo_CL[1] = NULL;
	}

	if (NULL != badPonitInfo->canRepairInfo_CL[2])
	{
		free(badPonitInfo->canRepairInfo_CL[2]);
		badPonitInfo->canRepairInfo_CL[2] = NULL;
	}

	if (NULL != badPonitInfo->canRepairInfo_CL[3])
	{
		free(badPonitInfo->canRepairInfo_CL[3]);
		badPonitInfo->canRepairInfo_CL[3] = NULL;
	}
	return 0;
}

static boolean CHECK_ERROR_SPC_BADPOINT_RESOUCE(struct SPC_BADPOINT_RESOUCE *pImageBuffer)
{
	//�ָ��
	int i = 0;
	if (NULL == pImageBuffer)
	{
		return FALSE;
	}

	if (0 == pImageBuffer->imageNumber)
	{
		return FALSE;
	}

	/*
	for (i = 0; i < pImageBuffer->imageNumber; i++)
	{
		if (NULL == pImageBuffer->pBuffer[i])
		{
			return FALSE;
		}
		if (0 == pImageBuffer->Thr[i])
		{
			return FALSE;
		}

	}
    */
	
	return TRUE;
}

static boolean CHECK_ERROR_SPC_BADPOINTINFOS(struct SPC_BADPOINTINFOS *badPonitInfo)
{
	if (NULL == badPonitInfo)
	{
		return FALSE;
	}

	if (0 == badPonitInfo->width)
	{
		return FALSE;
	}

	if (0 == badPonitInfo->height)
	{
		return FALSE;
	}

	if (0 == badPonitInfo->rawType)
	{
		return FALSE;
	}

	if (0 == badPonitInfo->version)
	{
		return FALSE;
	}

	if (NULL != badPonitInfo->canRepairInfo_CL[0])
	{
		return FALSE;
	}

	if (NULL != badPonitInfo->canRepairCoordinate)
	{
		return FALSE;
	}

	if (1 == badPonitInfo->needBadColumnCorrect)
	{
		if (NULL != badPonitInfo->canRepairBadColumnCoordinate)
		{
			return FALSE;
		}
		if (NULL != badPonitInfo->canRepairPointCooratBadCol)
		{
			return FALSE;
		}
	}

	return TRUE;
}