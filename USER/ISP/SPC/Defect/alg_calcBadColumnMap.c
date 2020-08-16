#include "alg_calcBadColumnMap.h"

void judgebadPointsIsbadColumn(unsigned char *raw, int imgHeight, int imgWidth, int rawType)
{
	int i = 0, j = 0,k = 0;
	int continueBadPointsNum = 0;
	unsigned char *praw = raw;

	//连续11个坏点即认为是坏列
	int continueNumThrd = 11;

	if (SPC_RAW_TYPE_BW == rawType)	//黑白
	{
		//CCD的坏列要区分是图像的上半部分还是下半部分
		for (i = 0; i < imgHeight/2 - continueNumThrd; i++)
		{
			for (j = 0; j < imgWidth; j++)
			{
				if (1 == praw[j+i*imgWidth])
				{
					//判断是否存在连续的坏点满足坏列的标准
					for (k = 0; k < continueNumThrd; k++)
					{
						if(1 == praw[j + i*imgWidth + k*imgWidth])
						{
							continueBadPointsNum++;

						}
						else if (0 == praw[j + i*imgWidth + k*imgWidth])
						{
							break;
						}
					}

					//把坏列标记为2
					if (continueBadPointsNum == continueNumThrd)
					{
						for (k = 0;k < imgHeight/2;k++)
						{
							praw[j + k*imgWidth] = 2;					
						}
					}

					continueBadPointsNum = 0;
				}
			}
		}

		//CCD的坏列要区分是图像的上半部分还是下半部分
		for (i = imgHeight/2; i < imgHeight - continueNumThrd; i++)
		{
			for (j = 0; j < imgWidth; j++)
			{
				if (1 == praw[j+i*imgWidth])
				{
					//判断是否存在连续的坏点满足成为坏列的条件 
					for (k = 0; k < continueNumThrd; k++)
					{
						if(1 == praw[j + i*imgWidth + k*imgWidth])
						{
							continueBadPointsNum++;
						}
						else if (0 == praw[j + i*imgWidth + k*imgWidth])
						{
							break;
						}
					}

					//把坏列标记为2
					if (continueBadPointsNum == continueNumThrd)
					{
						for (k = imgHeight/2;k < imgHeight;k++)
						{
							praw[j + k*imgWidth] = 2;
						}
					}

					continueBadPointsNum = 0;
				}
			}
		}
	}
	else//彩色
	{
		return;
	}

}

void generateBadColumnMap_Raw(unsigned short *res, int imgHeight, int imgWidth, int threshold, int rawType, unsigned char *raw)
{

	int i = 0, j = 0;	
	int *colAvgUpper;
	int *colAvgLower;
	unsigned short tempUpperBadColumnFlag = 0, tempLowerBadColumnFlag = 0;

	colAvgUpper = (int *)malloc(imgWidth * sizeof (int));
	memset(colAvgUpper,0,imgWidth * sizeof(int));

	colAvgLower = (int *)malloc(imgWidth * sizeof (int));
	memset(colAvgLower,0,imgWidth * sizeof(int));

	/*备注*/
	/*列均值检测算法不完整，可能存在连续两个的坏列检测不出来，边缘上的好列可能误检测为坏列，待完善*/

	if (SPC_RAW_TYPE_BW == rawType)	// 黑白raw
	{
		for (j = 0; j < imgWidth; j++)
		{
			for (i = 0; i < imgHeight/2; i++)
			{
				colAvgUpper[j] = colAvgUpper[j] + res[i*imgWidth + j];
				colAvgLower[j] = colAvgLower[j] + res[(i+imgHeight/2)*imgWidth + j];
			}
			
			colAvgUpper[j] = colAvgUpper[j] / (imgHeight/2);
			colAvgLower[j] = colAvgLower[j] / (imgHeight/2);			
		}

		//判断是否为坏列
		for(j = 0; j < imgWidth; j++)
		{
			//最左侧一列
			if(j == 0)
			{
				if (ABS(colAvgUpper[j] - colAvgUpper[j+1]) > threshold)
				{
					tempUpperBadColumnFlag = 1;
				}

				if (ABS(colAvgLower[j] - colAvgLower[j+1]) > threshold)
				{
					tempLowerBadColumnFlag = 1;
				}

			}
			//最右侧一列
			else if(j == imgWidth -1)
			{
				if (ABS(colAvgUpper[j] - colAvgUpper[j-1]) > threshold)
				{
					tempUpperBadColumnFlag = 1;
				}

				if (ABS(colAvgLower[j] - colAvgLower[j-1]) > threshold)
				{
					tempLowerBadColumnFlag = 1;
				}
			}
			//中间列
			else
			{
				if ((ABS(colAvgUpper[j] - colAvgUpper[j-1]) > threshold) && (ABS(colAvgUpper[j] - colAvgUpper[j+1]) > threshold))
				{
					tempUpperBadColumnFlag = 1;
				}
				else
				{
					tempUpperBadColumnFlag = 0;
				}

				if ((ABS(colAvgLower[j] - colAvgLower[j-1]) > threshold) && (ABS(colAvgLower[j] - colAvgLower[j+1]) > threshold))
				{
					tempLowerBadColumnFlag = 1;
				}
				else
				{
					tempLowerBadColumnFlag = 0;
				}
			}

			//坏列标记为2
			if (tempUpperBadColumnFlag == 1)
			{
				for (i = 0; i < imgHeight/2; i++)
				{
					raw[i*imgWidth + j] = 2;
				}

			}

			if (tempLowerBadColumnFlag == 1)
			{
				for (i = imgHeight/2; i < imgHeight; i++)
				{
					raw[i*imgWidth + j] = 2;
				}

			}				
		}
	}
	else//彩色sensor
	{
		return;
	}

	free(colAvgUpper);
	free(colAvgLower);

}