#include "alg_spc_102.h"

static int JudgeType_BW(boolean R1, boolean R2, boolean R3, boolean L1, boolean L2, boolean L3);
static void generateBadPoint_BW(struct SPC_BADPOINTINFOS *badPonitInfo);
static int JudgeType_COLOR(boolean D3, boolean D4, boolean D7, boolean D8);
static void generateBadPoint_COLOR(struct SPC_BADPOINTINFOS *badPonitInfo);

int getBadPointCoordinate_102(struct SPC_BADPOINTINFOS *badPonitInfo)
{		
	if(SPC_RAW_TYPE_BW == badPonitInfo->rawType)
     {
         generateBadPoint_BW(badPonitInfo);
     }
     else if(SPC_RAW_TYPE_COLOR == badPonitInfo->rawType)
     {
         generateBadPoint_COLOR(badPonitInfo);
     }
     else
     {
		return -1;
     }
	 
	 return 0;
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

static void generateBadPoint_BW(struct SPC_BADPOINTINFOS *badPonitInfo)
{

	struct SPC_BADPOINTINFO  *canRepair = badPonitInfo->canRepairCoordinate;
	struct SPC_BADPOINTINFO  *canNotRepair = badPonitInfo->canNotRepairCoordinate;
	

	int height = badPonitInfo->height;
	int width = badPonitInfo->width;

	boolean R1,R2,R3,L1,L2,L3;
	int y, x;
	int  type; 
	unsigned char *raw = badPonitInfo->raw[0];
	if (badPonitInfo->needBadColumnCorrect)
	{
		raw = badPonitInfo->badRaw[0];
	}
	for(y=0; y<height; ++y)
	{
		unsigned char *praw = raw;
	    for(x=0; x<width ; ++x)
	    {
			if(1 == *praw)//坏点
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
					canNotRepair[badPonitInfo->canNotRepairSum].x    = x;
					canNotRepair[badPonitInfo->canNotRepairSum].y    = y;
					canNotRepair[badPonitInfo->canNotRepairSum].type = type;
					badPonitInfo->canNotRepairSum += 1;  //   ,out, 检测到的无法被修复的坏点数
				}
				else
				{
					canRepair[badPonitInfo->canRepairSum].x    = x;
					canRepair[badPonitInfo->canRepairSum].y    = y;
					canRepair[badPonitInfo->canRepairSum].type = type;
					badPonitInfo->canRepairSum += 1;
				}
			}
			++praw;
		}
		raw += width;
	}	
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

static void generateBadPoint_COLOR(struct SPC_BADPOINTINFOS *badPonitInfo)
{

	struct SPC_BADPOINTINFO  *canRepair = badPonitInfo->canRepairCoordinate;
	struct SPC_BADPOINTINFO  *canNotRepair = badPonitInfo->canNotRepairCoordinate;

	int height = badPonitInfo->height;
	int width = badPonitInfo->width;

	boolean D3, D4, D7, D8;
	int y, x;
	int  type;
	unsigned char *raw = badPonitInfo->raw[0];
	if (badPonitInfo->needBadColumnCorrect)
	{
		raw = badPonitInfo->badRaw[0];
	}
	for(y=0; y<height; ++y)
	{
		unsigned char *praw = raw;
	    for(x=0; x<width; ++x)
	    {
			if(1 == *praw)//坏点
			{
				D3 = FALSE;	//默认坏点
				D4 = FALSE; //默认坏点
				D8 = FALSE; //默认坏点
				D7 = FALSE;	//默认坏点
						
				if(x < 2)
				{	//最左边两列
					if(0 == *(praw + 2))
						D3 = TRUE;
					if(0 == *(praw + 4))
						D7 = TRUE;
				}
				else if(3 == x || 4 == x)
				{	//左边第三列或第四列
					if(0 == *(praw - 2))
						D4 = TRUE;
					if (0 == *(praw + 2))
						D3 = TRUE;
					if (0 == *(praw + 4))
						D7 = TRUE;
				}
				else if(width - 2 <= x)
				{	//最右边2列
					if(0 == *(praw - 2))
						D4 = TRUE;
					if(0 == *(praw - 4))
						D8 = TRUE;
				}
				else if (x == width - 3 || x == width - 4)
				{	//最右边第三列或第四列
					if (0 == *(praw + 2))
						D3 = TRUE;
					if (0 == *(praw - 2))
						D4 = TRUE;
					if (0 == *(praw - 4))
						D8 = TRUE;
				}
				else
				{
					if (0 == *(praw + 2))
						D3 = TRUE;
					if (0 == *(praw + 4))
						D7 = TRUE;
					if (0 == *(praw - 2))
						D4 = TRUE;
					if (0 == *(praw - 4))
						D8 = TRUE;
				}
				
				type = JudgeType_COLOR(D3, D4, D7, D8);
				if(0 == type)
				{
					canNotRepair[badPonitInfo->canNotRepairSum].x    = x;
					canNotRepair[badPonitInfo->canNotRepairSum].y    = y;
					canNotRepair[badPonitInfo->canNotRepairSum].type = type;
					badPonitInfo->canNotRepairSum += 1;  //   ,out, 检测到的无法被修复的坏点数
				}
				else
				{
					canRepair[badPonitInfo->canRepairSum].x    = x;
					canRepair[badPonitInfo->canRepairSum].y    = y;
					canRepair[badPonitInfo->canRepairSum].type = type;
					badPonitInfo->canRepairSum += 1;
				}
			}
			++praw;
		}
		raw += width;
	}
}






