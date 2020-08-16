#include "lvds_alg_spcTool.h"
#include "lvds_getCoor.h"

static int JudgeType_BW(boolean D9, boolean D10, boolean D11, boolean D12);
static int generateBadPoint_BW(struct LVDS_SPCParam *SpcParam, unsigned char *raw, struct LVDS_BADPOINTINFO *tmp, struct LVDS_BADPOINTINFO *tmpNoRepair);
static int JudgeType_COLOR(boolean D2, boolean D7, boolean D4, boolean D5);
static int generateBadPoint_COLOR(struct LVDS_SPCParam *SpcParam, unsigned char *raw, struct LVDS_BADPOINTINFO *tmp, struct LVDS_BADPOINTINFO *tmpNoRepair);

int getCoor(struct LVDS_SPCParam *SpcParam,unsigned char *map, struct LVDS_BADPOINTINFO *tmp, struct LVDS_BADPOINTINFO *tmpNoRepair)
{
	int SumNotRepair;
	//���뻵����Ϣͼ�����������Ϣ�Լ������޸�����Ϣ
	if (LVDS_RAW_TYPE_BW == SpcParam->rawType)
	{
		SumNotRepair=generateBadPoint_BW(SpcParam, map, tmp, tmpNoRepair);
	}
	else if (LVDS_RAW_TYPE_COLOR == SpcParam->rawType)
	{
		SumNotRepair=generateBadPoint_COLOR(SpcParam, map, tmp, tmpNoRepair);
	}
	else
	{
		return -1;
	}

	return SumNotRepair;

}

static int JudgeType_BW(boolean D9, boolean D10, boolean D11, boolean D12)
{
	int  type = 0;

	if (D9&&D10&&D11&&D12)
		type = 9;
	else if (D10&&D11)
		type = 10;
	else if (D9&&D12)
		type = 11;
	else if (D12)
		type = 12;
	else if (D11)
		type = 13;
	else if (D10)
		type = 14;
	else if (D9)
		type = 15;

	return type;
}
static int generateBadPoint_BW(struct LVDS_SPCParam *SpcParam, unsigned char *raw, struct LVDS_BADPOINTINFO *tmp, struct LVDS_BADPOINTINFO *tmpNoRepair)
{
	int height = SpcParam->height;
	int width = SpcParam->width;
	boolean D9, D10, D11, D12;
	int SumRepair = 0;
	int SumNotRepair = 0;
	int y, x;
	for (y = 0; y<height; ++y)
	{
		unsigned char *praw = raw;
		for (x = 0; x<width; ++x)
		{
			if (1 == *praw)//����
			{
				D9 = FALSE; //Ĭ�ϻ���
				D10 = FALSE; //Ĭ�ϻ���
				D11 = FALSE; //Ĭ�ϻ���
				D12 = FALSE; //Ĭ�ϻ���
				if (y < 1)
				{
					if (x < 1)
					{	//���Ͻ�1x1
						if (0 == *(praw + 1))
							D11 = TRUE;
						if (0 == *(praw + width))
							D12 = TRUE;
					}
					else if (width - 1 <= x)
					{	//���Ͻ�1x1
						if (0 == *(praw - 1))
							D10 = TRUE;
						if (0 == *(praw + width))
							D12 = TRUE;
					}
					else
					{	//������1��
						if (0 == *(praw - 1))
							D10 = TRUE;
						if (0 == *(praw + 1))
							D11 = TRUE;
						if (0 == *(praw + width))
							D12 = TRUE;
					}
				}
				else if (height - 1 <= y)
				{
					if (x < 1)
					{	//���½�1x1
						if (0 == *(praw - width))
							D9 = TRUE;
						if (0 == *(praw + 1))
							D11 = TRUE;
					}
					else if (width - 1 <= x)
					{
						//���½�1x1
						if (0 == *(praw - width))
							D9 = TRUE;
						if (0 == *(praw - 1))
							D10 = TRUE;
					}
					else
					{	//������1��
						if (0 == *(praw - width))
							D9 = TRUE;
						if (0 == *(praw - 1))
							D10 = TRUE;
						if (0 == *(praw + 1))
							D11 = TRUE;
					}
				}
				else
				{
					if (x < 1)
					{	//�����1��
						if (0 == *(praw - width))
							D9 = TRUE;
						if (0 == *(praw + 1))
							D11 = TRUE;
						if (0 == *(praw + width))
							D12 = TRUE;
					}
					else if (width - 1 <= x)
					{	//���ұ�1��
						if (0 == *(praw - width))
							D9 = TRUE;
						if (0 == *(praw - 1))
							D10 = TRUE;
						if (0 == *(praw + width))
							D12 = TRUE;
					}
					else
					{
						if (0 == *(praw - width))
							D9 = TRUE;
						if (0 == *(praw - 1))
							D10 = TRUE;
						if (0 == *(praw + 1))
							D11 = TRUE;
						if (0 == *(praw + width))
							D12 = TRUE;
					}
				}

				int  type = JudgeType_BW(D9, D10, D11, D12);
				if (0 == type)
				{
					tmpNoRepair[SumNotRepair].x = x;
					tmpNoRepair[SumNotRepair].y = y;
					tmpNoRepair[SumNotRepair ].type = type;
					SumNotRepair += 1;  //   ,out, ��⵽���޷����޸��Ļ�����
				}
				else
				{
					tmp[SumRepair].x = x;
					tmp[SumRepair].y = y;
					tmp[SumRepair].type = type;
					SumRepair += 1;
				}
			}
			++praw;
		}
		raw += width;
	}
	return SumNotRepair;
}
static int JudgeType_COLOR(boolean D2, boolean D7, boolean D4, boolean D5)
{
	int  type = 0;

	if (D2&&D7&&D4&&D5)
		type = 1;
	else if (D4&&D5)
		type = 2;
	else if (D2&&D7)
		type = 3;
	else if (D7)
		type = 4;
	else if (D5)
		type = 5;
	else if (D4)
		type = 6;
	else if (D2)
		type = 7;

	return type;
}

static int generateBadPoint_COLOR(struct LVDS_SPCParam *SpcParam, unsigned char *raw, struct LVDS_BADPOINTINFO *tmp, struct LVDS_BADPOINTINFO *tmpNoRepair)
{
	int SumRepair = 0;
	int SumNotRepair = 0;

	int height = SpcParam->height;
	int width = SpcParam->width;

	boolean D2, D4, D5, D7;
	int y, x;
	for (y = 0; y<height; ++y)
	{
		unsigned char *praw = raw;
		for (x = 0; x<width; ++x)
		{
			if (1 == *praw)//����
			{
				D2 = FALSE;	//Ĭ�ϻ���
				D4 = FALSE; //Ĭ�ϻ���
				D5 = FALSE; //Ĭ�ϻ���
				D7 = FALSE;	//Ĭ�ϻ���
				if (y < 2)
				{
					if (x < 2)
					{	//���Ͻ�2x2
						if (0 == *(praw + 2))
							D5 = TRUE;
						if (0 == *(praw + width + width))
							D7 = TRUE;
					}
					else if (width - 2 <= x)
					{	//���Ͻ�2x2
						if (0 == *(praw - 2))
							D4 = TRUE;
						if (0 == *(praw + width + width))
							D7 = TRUE;
					}
					else
					{	//������2��
						if (0 == *(praw - 2))
							D4 = TRUE;
						if (0 == *(praw + 2))
							D5 = TRUE;
						if (0 == *(praw + width + width))
							D7 = TRUE;
					}
				}
				else if (height - 2 <= y)
				{
					if (x < 2)
					{	//���½�2x2
						if (0 == *(praw - width - width))
							D2 = TRUE;
						if (0 == *(praw + 2))
							D5 = TRUE;
					}
					else if (width - 2 <= x)
					{
						//���½�2x2
						if (0 == *(praw - width - width))
							D2 = TRUE;
						if (0 == *(praw - 2))
							D4 = TRUE;
					}
					else
					{	//������2��
						if (0 == *(praw - width - width))
							D2 = TRUE;
						if (0 == *(praw - 2))
							D4 = TRUE;
						if (0 == *(praw + 2))
							D5 = TRUE;
					}
				}
				else
				{
					if (x < 2)
					{	//�����2��
						if (0 == *(praw - width - width))
							D2 = TRUE;
						if (0 == *(praw + 2))
							D5 = TRUE;
						if (0 == *(praw + width + width))
							D7 = TRUE;
					}
					else if (width - 2 <= x)
					{	//���ұ�2��
						if (0 == *(praw - width - width))
							D2 = TRUE;
						if (0 == *(praw - 2))
							D4 = TRUE;
						if (0 == *(praw + width + width))
							D7 = TRUE;
					}
					else
					{
						if (0 == *(praw - width - width))
							D2 = TRUE;
						if (0 == *(praw - 2))
							D4 = TRUE;
						if (0 == *(praw + 2))
							D5 = TRUE;
						if (0 == *(praw + width + width))
							D7 = TRUE;
					}
				}

				int  type = JudgeType_COLOR(D2, D7, D4, D5);
				if (0 == type)
				{
					tmpNoRepair[SumNotRepair].x = x;
					tmpNoRepair[SumNotRepair].y = y;
					tmpNoRepair[SumNotRepair].type = type;
					SumNotRepair += 1;  //   ,out, ��⵽���޷����޸��Ļ�����
				}
				else
				{
					tmp[SumRepair].x = x;
					tmp[SumRepair].y = y;
					tmp[SumRepair].type = type;
					SumRepair += 1;
				}
			}
			++praw;
		}
		raw += width;
	}
	return SumNotRepair;
}
