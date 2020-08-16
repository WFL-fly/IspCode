
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
	//初始化输出，可修复/不可修复点数都少于总点数，申请总点数空间
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

	//分配内存乘以2的原因：如果同一列的上下两部分都有坏列，该列的坏列个数记为1；但是产线工具要知道坏列上所有点的坐标，用于检测坏列是否被修复。所以分配的内存要放大2倍
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

	//检测坏列上每个点的坐标、类型
	for(y=0; y<height; ++y)
	{
		unsigned char *praw = raw;
	    for(x=0; x<width ; ++x)
	    {
			if(2 == *praw)//坏列
			{
				R1 = FALSE; //默认坏点
				R2 = FALSE; //默认坏点
				R3 = FALSE; //默认坏点
				L1 = FALSE; //默认坏点
				L2 = FALSE; //默认坏点
				L3 = FALSE; //默认坏点
				
				if(x < 1)
				{	//第一列
					if(0 == *(praw + 1))
						R1 = TRUE;
					if(0 == *(praw + 2))
						R2 = TRUE;
					if (0 == *(praw + 3))
						R3 = TRUE;
				}
				else if(1 == x)
				{	//第二列
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
				{	//第三列
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
				{	//倒数第一列
					if(0 == *(praw - 1))
						L1 = TRUE;
					if(0 == *(praw - 2))
						L2 = TRUE;
					if(0 == *(praw - 3))
						L3 = TRUE;
				}
				else if (width - 2 == x)
				{	//倒数第二列
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
				{	//倒数第三列
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
					badPonitInfo->canNotRepairBadColumnSum += 1;  //   ,out, 检测到的无法被修复的坏点数
				}
				else
				{
					canRepairPointCoordinateatBadCol[badPonitInfo->canRepairPointsSumatBadCol].x    = x;
					canRepairPointCoordinateatBadCol[badPonitInfo->canRepairPointsSumatBadCol].y    = y;
					canRepairPointCoordinateatBadCol[badPonitInfo->canRepairPointsSumatBadCol].type = type;
					badPonitInfo->canRepairPointsSumatBadCol += 1;  //   ,out, 检测到坏列上可以被修复的坏点数
				}
			}
			praw++;
		}
		raw += width;
	}

	raw = badPonitInfo->badRaw[0];

	//在raw中分别取图像上半部分中的一行（y = 0）和图像下半部分中的一行(y = height/2)，如果是坏列，则存储坏列的信息
	for(x=0; x<width ; ++x)
	{
		if ((2 == *raw) && (2 == *(raw + width*height / 2)))//图像上、下半部分都是坏列
		{
			canRepairBadColumn[badPonitInfo->canRepairBadColumnSum].x = x;
			canRepairBadColumn[badPonitInfo->canRepairBadColumnSum].positionInImageFlag = BAD_COLUMN_IN_ALL_IMAGE;
			badPonitInfo->canRepairBadColumnSum += 1;
		}
		else if(2 == *raw)//图像上半部分的坏列
		{
			canRepairBadColumn[badPonitInfo->canRepairBadColumnSum].x = x;
			canRepairBadColumn[badPonitInfo->canRepairBadColumnSum].positionInImageFlag = BAD_COLUMN_IN_UPPER_IMAGE;
			badPonitInfo->canRepairBadColumnSum += 1;
		}
		else if(2 == *(raw + width*height/2))//图像下半部分的坏列
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