#include "alg_calcBadColumnMap.h"

void judgebadPointsIsbadColumn(unsigned char *raw, int imgHeight, int imgWidth, int rawType)
{
	int i = 0, j = 0,k = 0;
	int continueBadPointsNum = 0;
	unsigned char *praw = raw;

	//����11�����㼴��Ϊ�ǻ���
	int continueNumThrd = 11;

	if (SPC_RAW_TYPE_BW == rawType)	//�ڰ�
	{
		//CCD�Ļ���Ҫ������ͼ����ϰ벿�ֻ����°벿��
		for (i = 0; i < imgHeight/2 - continueNumThrd; i++)
		{
			for (j = 0; j < imgWidth; j++)
			{
				if (1 == praw[j+i*imgWidth])
				{
					//�ж��Ƿ���������Ļ������㻵�еı�׼
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

					//�ѻ��б��Ϊ2
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

		//CCD�Ļ���Ҫ������ͼ����ϰ벿�ֻ����°벿��
		for (i = imgHeight/2; i < imgHeight - continueNumThrd; i++)
		{
			for (j = 0; j < imgWidth; j++)
			{
				if (1 == praw[j+i*imgWidth])
				{
					//�ж��Ƿ���������Ļ��������Ϊ���е����� 
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

					//�ѻ��б��Ϊ2
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
	else//��ɫ
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

	/*��ע*/
	/*�о�ֵ����㷨�����������ܴ������������Ļ��м�ⲻ��������Ե�ϵĺ��п�������Ϊ���У�������*/

	if (SPC_RAW_TYPE_BW == rawType)	// �ڰ�raw
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

		//�ж��Ƿ�Ϊ����
		for(j = 0; j < imgWidth; j++)
		{
			//�����һ��
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
			//���Ҳ�һ��
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
			//�м���
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

			//���б��Ϊ2
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
	else//��ɫsensor
	{
		return;
	}

	free(colAvgUpper);
	free(colAvgLower);

}