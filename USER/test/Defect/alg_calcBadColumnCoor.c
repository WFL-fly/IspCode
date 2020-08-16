
#include "alg_calcMap.h"
#include "alg_calcBadColumnCoor.h"
#include "alg_spcTool.h"

static int getBadColumnCoordinate_101(struct SPC_BADPOINTINFOS *badPonitInfo);
static int JudgeType_BW(boolean R1, boolean R2, boolean R3, boolean L1, boolean L2,boolean L3);
static int JudgeType_COLOR(boolean D3, boolean D4, boolean D7, boolean D8);
static void generateBadColumnCoor_BW(struct SPC_BADPOINTINFOS *badPonitInfo);
static void generateBadColumnCoor_COLOR(struct SPC_BADPOINTINFOS *badPonitInfo);

int getBadColumnCoordinate(struct SPC_BADPOINTINFOS *badPonitInfo)
{	
	//��ʼ����������޸�/�����޸������������ܵ����������ܵ����ռ�
	int i = 0;
	badPonitInfo->canRepairBadColumnSum = 0;
	badPonitInfo->canNotRepairBadColumnSum = 0;
	badPonitInfo->badColumnSum = 0;
	badPonitInfo->canRepairPointsSumatBadCol = 0;
	for (i = 0; i < (int)(badPonitInfo->width); i++)
	{
		if ((2 == badPonitInfo->badRaw[0][i]) || (2 == badPonitInfo->badRaw[0][i + badPonitInfo->width*badPonitInfo->height/2]))
		{
			badPonitInfo->badColumnSum++;
		}
	}
	
	badPonitInfo->canRepairBadColumnCoordinate = (struct SPC_BADCOLUMNINFO *)malloc((badPonitInfo->badColumnSum + 1) * sizeof(struct SPC_BADCOLUMNINFO));
	if (NULL == badPonitInfo->canRepairBadColumnCoordinate)
	{
		return -1;
	}

	badPonitInfo->canNotRepairBadColumnCoordinate = (struct SPC_BADCOLUMNINFO *)malloc((badPonitInfo->badColumnSum * 2 + 1) *  (badPonitInfo->height / 2) * sizeof(struct SPC_BADCOLUMNINFO));
	if (NULL == badPonitInfo->canNotRepairBadColumnCoordinate)
	{
		return -1;
	}

	//�����ڴ����2��ԭ�����ͬһ�е����������ֶ��л��У����еĻ��и�����Ϊ1�����ǲ��߹���Ҫ֪�����������е�����꣬���ڼ�⻵���Ƿ��޸������Է�����ڴ�Ҫ�Ŵ�2��
	badPonitInfo->canRepairPointCooratBadCol = (struct SPC_BADCOLUMNINFO *)malloc((badPonitInfo->badColumnSum * 2 + 1) * (badPonitInfo->height / 2) * sizeof(struct SPC_BADCOLUMNINFO));
	if (NULL == badPonitInfo->canRepairPointCooratBadCol)
	{
		return -1;
	}

	if (BADCOLUMN_VERSION_101 == badPonitInfo->badColumnVersion)
	{
		getBadColumnCoordinate_101(badPonitInfo);
	}
	else
	{
		return -1;
	}
	
	return 0;
}

static int getBadColumnCoordinate_101(struct SPC_BADPOINTINFOS *badPonitInfo)
{
	if (SPC_RAW_TYPE_BW == badPonitInfo->rawType)
	{
		generateBadColumnCoor_BW(badPonitInfo);
	}
	else if (SPC_RAW_TYPE_COLOR == badPonitInfo->rawType)
	{
		generateBadColumnCoor_COLOR(badPonitInfo);
	}
	else
	{
		return -1;
	}
}

static int JudgeType_BW(boolean R1, boolean R2, boolean R3, boolean L1, boolean L2,boolean L3)
{
	int  type = 0;

	if(L1&&R1)
		type = 9;
	else if(R1)
		type = 10;
	else if(L1)
		type = 11;
	else if (L2&&R2)
		type = 12;
	else if(L2)
		type = 13;
	else if(R2)
		type = 14;
	else if (L3&&R3)
		type = 15;
	else if (L3)
		type = 16;
	else if (R3)
		type = 17;
		
	return type;
}

static int JudgeType_COLOR(boolean D3, boolean D4, boolean D7, boolean D8)
{
	int  type = 0;

	if(D3&&D4)
		type = 1;
	else if(D3)
		type = 2;
	else if(D4)
		type = 3;
	else if (D7&&D8)
		type = 4;
	else if(D7)
		type = 5;
	else if(D8)
		type = 6;

	return type;
}

static void generateBadColumnCoor_BW(struct SPC_BADPOINTINFOS *badPonitInfo)
{
	struct SPC_BADCOLUMNINFO  *canRepairBadColumn = badPonitInfo->canRepairBadColumnCoordinate;
	struct SPC_BADCOLUMNINFO  *canNotRepairBadColumn = badPonitInfo->canNotRepairBadColumnCoordinate;
	struct SPC_BADCOLUMNINFO  *canRepairPointCoordinateatBadCol = badPonitInfo->canRepairPointCooratBadCol;
	
	int height = badPonitInfo->height;
	int width = badPonitInfo->width;
	unsigned char *raw = badPonitInfo->badRaw[0];
	boolean R1,R2,R3,L1,L2,L3;
	int y, x;
	int type;

	//��⻵����ÿ��������ꡢ����
	for(y=0; y<height; ++y)
	{
		unsigned char *praw = raw;
	    for(x=0; x<width ; ++x)
	    {
			if(2 == *praw)//����
			{
				R1 = FALSE; //Ĭ�ϻ���
				R2 = FALSE; //Ĭ�ϻ���
				R3 = FALSE; //Ĭ�ϻ���
				L1 = FALSE; //Ĭ�ϻ���
				L2 = FALSE; //Ĭ�ϻ���
				L3 = FALSE; //Ĭ�ϻ���
				
				if(x < 1)
				{	//��һ��
					if(0 == *(praw + 1))
						R1 = TRUE;
					if(0 == *(praw + 2))
						R2 = TRUE;
					if (0 == *(praw + 3))
						R3 = TRUE;
				}
				else if(1 == x)
				{	//�ڶ���
					if(0 == *(praw - 1))
						L1 = TRUE;
					if(0 == *(praw + 1))
						R1 = TRUE;
					if (0 == *(praw + 2))
						R2 = TRUE;
					if (0 == *(praw + 3))
						R3 = TRUE;
				}
				else if (x == 2)
				{	//������
					if (0 == *(praw - 2))
						L2 = TRUE;
					if (0 == *(praw - 1))
						L1 = TRUE;
					if (0 == *(praw + 1))
						R1 = TRUE;
					if (0 == *(praw + 2))
						R2 = TRUE;
					if (0 == *(praw + 3))
						R3 = TRUE;
				}
				else if(width - 1 <= x)
				{	//������һ��
					if(0 == *(praw - 1))
						L1 = TRUE;
					if(0 == *(praw - 2))
						L2 = TRUE;
					if(0 == *(praw - 3))
						L3 = TRUE;
				}
				else if (width - 2 == x)
				{	//�����ڶ���
					if (0 == *(praw - 1))
						L1 = TRUE;
					if (0 == *(praw - 2))
						L2 = TRUE;
					if (0 == *(praw - 3))
						L3 = TRUE;
					if (0 == *(praw +1))
						R1 = TRUE;
				}
				else if (x == width - 3)
				{	//����������
					if (0 == *(praw - 1))
						L1 = TRUE;
					if (0 == *(praw - 2))
						L2 = TRUE;
					if (0 == *(praw - 3))
						L3 = TRUE;
					if (0 == *(praw + 1))
						R1 = TRUE;
					if (0 == *(praw + 2))
						R2 = TRUE;
				}
				else
				{
					if (0 == *(praw - 1))
						L1 = TRUE;
					if (0 == *(praw - 2))
						L2 = TRUE;
					if (0 == *(praw - 3))
						L3 = TRUE;
					if (0 == *(praw + 1))
						R1 = TRUE;
					if (0 == *(praw + 2))
						R2 = TRUE;
					if (0 == *(praw + 3))
						R3 = TRUE;
				}
							
				type = JudgeType_BW(R1,R2,R3,L1,L2,L3);
				if(0 == type)
				{
					canNotRepairBadColumn[badPonitInfo->canNotRepairBadColumnSum].x    = x;
					canNotRepairBadColumn[badPonitInfo->canNotRepairBadColumnSum].y    = y;
					canNotRepairBadColumn[badPonitInfo->canNotRepairBadColumnSum].type = type;
					badPonitInfo->canNotRepairBadColumnSum += 1;  //   ,out, ��⵽���޷����޸��Ļ�����
				}
				else
				{
					canRepairPointCoordinateatBadCol[badPonitInfo->canRepairPointsSumatBadCol].x    = x;
					canRepairPointCoordinateatBadCol[badPonitInfo->canRepairPointsSumatBadCol].y    = y;
					canRepairPointCoordinateatBadCol[badPonitInfo->canRepairPointsSumatBadCol].type = type;
					badPonitInfo->canRepairPointsSumatBadCol += 1;  //   ,out, ��⵽�����Ͽ��Ա��޸��Ļ�����
				}
			}
			praw++;
		}
		raw += width;
	}

	raw = badPonitInfo->badRaw[0];

	//��raw�зֱ�ȡͼ���ϰ벿���е�һ�У�y = 0����ͼ���°벿���е�һ��(y = height/2)������ǻ��У���洢���е���Ϣ
	for(x=0; x<width ; ++x)
	{
		if ((2 == *raw) && (2 == *(raw + width*height / 2)))//ͼ���ϡ��°벿�ֶ��ǻ���
		{
			canRepairBadColumn[badPonitInfo->canRepairBadColumnSum].x = x;
			canRepairBadColumn[badPonitInfo->canRepairBadColumnSum].positionInImageFlag = BAD_COLUMN_IN_ALL_IMAGE;
			badPonitInfo->canRepairBadColumnSum += 1;
		}
		else if(2 == *raw)//ͼ���ϰ벿�ֵĻ���
		{
			canRepairBadColumn[badPonitInfo->canRepairBadColumnSum].x = x;
			canRepairBadColumn[badPonitInfo->canRepairBadColumnSum].positionInImageFlag = BAD_COLUMN_IN_UPPER_IMAGE;
			badPonitInfo->canRepairBadColumnSum += 1;
		}
		else if(2 == *(raw + width*height/2))//ͼ���°벿�ֵĻ���
		{	
			canRepairBadColumn[badPonitInfo->canRepairBadColumnSum].x = x;
			canRepairBadColumn[badPonitInfo->canRepairBadColumnSum].positionInImageFlag = BAD_COLUMN_IN_LOWER_IMAGE;
			badPonitInfo->canRepairBadColumnSum += 1;
		}
		++raw;
	}	
}

static void generateBadColumnCoor_COLOR(struct SPC_BADPOINTINFOS *badPonitInfo)
{
	return;
}