#include "alg_spc_103.h"

static int JudgeType_BW(boolean D1, boolean D2, boolean D3, boolean D4, boolean D5, boolean D6, boolean D7, boolean D8);
static void generateBadPoint_BW(struct SPC_BADPOINTINFOS *badPonitInfo);
static int JudgeType_COLOR(boolean D1, boolean D2, boolean D3, boolean D4, boolean D5, boolean D6, boolean D7, boolean D8);
static void generateBadPoint_COLOR(struct SPC_BADPOINTINFOS *badPonitInfo);

int getBadPointCoordinate_103(struct SPC_BADPOINTINFOS *badPonitInfo)
{
	if (SPC_RAW_TYPE_BW == badPonitInfo->rawType)
	{
		generateBadPoint_BW(badPonitInfo);
	}
	else if (SPC_RAW_TYPE_COLOR == badPonitInfo->rawType)
	{
		generateBadPoint_COLOR(badPonitInfo);
	}
	else
	{
		return -1;
	}

	return 0;
}

static int JudgeType_BW(boolean D1, boolean D2, boolean D3, boolean D4, boolean D5, boolean D6, boolean D7, boolean D8)
{
	int  type = 0;

	if (D2&&D4&&D5&&D7)
		type = 20;
	else if (D4&&D5)
		type = 21;
	else if (D2&&D7)
		type = 22;
	else if (D7)
		type = 23;
	else if (D5)
		type = 24;
	else if (D4)
		type = 25;
	else if (D2)
		type = 26;
	else if (D1&&D3&&D6&&D8)
		type = 27;
	else if (D6&&D8)
		type = 28;
	else if (D3&&D8)
		type = 29;
	else if (D1&&D3)
		type = 30;
	else if (D1&&D6)
		type = 31;
	else if (D3&&D6)
		type = 32;
	else if (D1&&D8)
		type = 33;
	else if (D1)
		type = 34;
	else if (D3)
		type = 35;
	else if (D6)
		type = 36;
	else if (D8)
		type = 37;

	return type;
}

static void generateBadPoint_BW(struct SPC_BADPOINTINFOS *badPonitInfo)
{
	struct SPC_BADPOINTINFO  *canRepair = badPonitInfo->canRepairCoordinate;
	struct SPC_BADPOINTINFO  *canNotRepair = badPonitInfo->canNotRepairCoordinate;


	int height = badPonitInfo->height;
	int width = badPonitInfo->width;

	boolean D1, D2, D3, D4, D5, D6, D7, D8;
	int y, x;
	int  type;
	unsigned char *raw = badPonitInfo->raw[0];
	if (badPonitInfo->needBadColumnCorrect)
	{
		raw = badPonitInfo->badRaw[0];
	}
	for (y = 0; y<height; ++y)
	{
		unsigned char *praw = raw;
		for (x = 0; x<width; ++x)
		{
			if (1 == *praw)//坏点
			{
				D1 = FALSE; //默认坏点
				D2 = FALSE; //默认坏点
				D3 = FALSE; //默认坏点
				D4 = FALSE; //默认坏点
				D5 = FALSE; //默认坏点
				D6 = FALSE; //默认坏点
				D7 = FALSE; //默认坏点
				D8 = FALSE; //默认坏点
				if (y < 1)
				{
					if (x < 1)
					{	//左上角1x1
						if (0 == *(praw + 1))
							D5 = TRUE;
						if (0 == *(praw + width))
							D7 = TRUE;					
						if (0 == *(praw + width + 1))
							D8 = TRUE;
					}
					else if (width - 1 <= x)
					{	//右上角1x1
						if (0 == *(praw - 1))
							D4 = TRUE;
						if (0 == *(praw + width - 1))
							D6 = TRUE;
						if (0 == *(praw + width))
							D7 = TRUE;
					}
					else
					{	//最上面1行
						if (0 == *(praw - 1))
							D4 = TRUE;
						if (0 == *(praw + 1))
							D5 = TRUE;
						if (0 == *(praw + width - 1))
							D6 = TRUE;
						if (0 == *(praw + width))
							D7 = TRUE;
						if (0 == *(praw + width + 1))
							D8 = TRUE;
					}
				}
				else if (height - 1 <= y)
				{
					if (x < 1)
					{	//左下角1x1
						if (0 == *(praw - width))
							D2 = TRUE;
						if (0 == *(praw - width + 1))
							D3 = TRUE;
						if (0 == *(praw + 1))
							D5 = TRUE;
					}
					else if (width - 1 <= x)
					{
						//右下角1x1
						if (0 == *(praw - width - 1))
							D1 = TRUE;
						if (0 == *(praw - width))
							D2 = TRUE;
						if (0 == *(praw - 1))
							D4 = TRUE;
					}
					else
					{	//最下面1行
						if (0 == *(praw - width -1))
							D1 = TRUE;
						if (0 == *(praw - width))
							D2 = TRUE;
						if (0 == *(praw - width +1))
							D3 = TRUE;
						if (0 == *(praw - 1))
							D4 = TRUE;
						if (0 == *(praw + 1))
							D5 = TRUE;
					}
				}
				else
				{
					if (x < 1)
					{	//最左边1列
						if (0 == *(praw - width))
							D2 = TRUE;
						if (0 == *(praw - width + 1))
							D3 = TRUE;
						if (0 == *(praw + 1))
							D5 = TRUE;
						if (0 == *(praw + width))
							D7 = TRUE;
						if (0 == *(praw + width +1))
							D8 = TRUE;
					}
					else if (width - 1 <= x)
					{	//最右边1列
						if (0 == *(praw - width-1))
							D1 = TRUE;
						if (0 == *(praw - width))
							D2 = TRUE;
						if (0 == *(praw - 1))
							D4 = TRUE;
						if (0 == *(praw + width - 1))
							D6 = TRUE;
						if (0 == *(praw + width))
							D7 = TRUE;
					}
					else
					{
						if (0 == *(praw - width - 1))
							D1 = TRUE;
						if (0 == *(praw - width))
							D2 = TRUE;
						if (0 == *(praw - width + 1))
							D3 = TRUE;
						if (0 == *(praw - 1))
							D4 = TRUE;
						if (0 == *(praw + 1))
							D5 = TRUE;
						if (0 == *(praw + width - 1))
							D6 = TRUE;
						if (0 == *(praw + width))
							D7 = TRUE;
						if (0 == *(praw + width + 1))
							D8 = TRUE;
					}
				}

				type = JudgeType_BW(D1, D2, D3, D4, D5, D6,D7, D8);
				if (0 == type)
				{
					canNotRepair[badPonitInfo->canNotRepairSum].x = x;
					canNotRepair[badPonitInfo->canNotRepairSum].y = y;
					canNotRepair[badPonitInfo->canNotRepairSum].type = type;
					badPonitInfo->canNotRepairSum += 1;  //   ,out, 检测到的无法被修复的坏点数
				}
				else
				{
					canRepair[badPonitInfo->canRepairSum].x = x;
					canRepair[badPonitInfo->canRepairSum].y = y;
					canRepair[badPonitInfo->canRepairSum].type = type;
					badPonitInfo->canRepairSum += 1;
				}
			}
			++praw;
		}
		raw += width;
	}
}

static int JudgeType_COLOR(boolean D1, boolean D2, boolean D3, boolean D4, boolean D5, boolean D6, boolean D7, boolean D8)
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
	else if (D1&&D3&&D6&&D8)
		type = 8;
	else if (D6&&D8)
		type = 9;
	else if (D3&&D8)
		type = 10;
	else if (D1&&D3)
		type = 11;
	else if (D1&&D6)
		type = 12;
	else if (D3&&D6)
		type = 13;
	else if (D1&&D8)
		type = 14;
	else if (D1)
		type = 15;
	else if (D3)
		type = 16;
	else if (D6)
		type = 17;
	else if (D8)
		type = 18;

	return type;
}

static void generateBadPoint_COLOR(struct SPC_BADPOINTINFOS *badPonitInfo)
{
	struct SPC_BADPOINTINFO  *canRepair = badPonitInfo->canRepairCoordinate;
	struct SPC_BADPOINTINFO  *canNotRepair = badPonitInfo->canNotRepairCoordinate;

	int height = badPonitInfo->height;
	int width = badPonitInfo->width;

	boolean D1, D2, D3, D4, D5, D6, D7, D8;
	int y, x;
	int  type;
	unsigned char *raw = badPonitInfo->raw[0];
	if (badPonitInfo->needBadColumnCorrect)
	{
		raw = badPonitInfo->badRaw[0];
	}
	for (y = 0; y<height; ++y)
	{
		unsigned char *praw = raw;
		for (x = 0; x<width; ++x)
		{
			if (1 == *praw)//坏点
			{
				D1 = FALSE;	//默认坏点
				D2 = FALSE; //默认坏点
				D3 = FALSE; //默认坏点
				D4 = FALSE;	//默认坏点
				D5 = FALSE;	//默认坏点
				D6 = FALSE; //默认坏点
				D7 = FALSE; //默认坏点
				D8 = FALSE;	//默认坏点

				if (y < 2)
				{
					if (x < 2)
					{	//左上角2x2
						if (0 == *(praw + 2))
							D5 = TRUE;
						if (0 == *(praw + width + width))
							D7 = TRUE;
						if (0 == *(praw + width + width + 2))
							D5 = TRUE;
					}
					else if (width - 2 <= x)
					{	//右上角2x2
						if (0 == *(praw - 2))
							D4 = TRUE;
						if (0 == *(praw + width + width - 2))
							D6 = TRUE;
						if (0 == *(praw + width + width))
							D7 = TRUE;
					}
					else
					{	//最上面2行
						if (0 == *(praw - 2))
							D4 = TRUE;
						if (0 == *(praw + 2))
							D5 = TRUE;
						if (0 == *(praw + width + width - 2))
							D6 = TRUE;
						if (0 == *(praw + width + width))
							D7 = TRUE;
						if (0 == *(praw + width + width + 2))
							D8 = TRUE;
					}
				}
				else if (height - 2 <= y)
				{
					if (x < 2)
					{	//左下角2x2
						if (0 == *(praw - width - width))
							D2 = TRUE;
						if (0 == *(praw - width - width + 2))
							D3 = TRUE;
						if (0 == *(praw + 2))
							D5 = TRUE;
					}
					else if (width - 2 <= x)
					{
						//右下角2x2
						if (0 == *(praw - width - width - 2))
							D1 = TRUE;
						if (0 == *(praw - width - width))
							D2 = TRUE;
						if (0 == *(praw - 2))
							D4 = TRUE;
					}
					else
					{	//最下面2行
						if (0 == *(praw - width - width - 2))
							D1 = TRUE;
						if (0 == *(praw - width - width))
							D2 = TRUE;
						if (0 == *(praw - width - width + 2))
							D3 = TRUE;
						if (0 == *(praw - 2))
							D4 = TRUE;
						if (0 == *(praw + 2))
							D5 = TRUE;
					}
				}
				else
				{
					if (x < 2)
					{	//最左边2列
						if (0 == *(praw - width - width))
							D2 = TRUE;
						if (0 == *(praw - width - width + 2))
							D3 = TRUE;
						if (0 == *(praw + 2))
							D5 = TRUE;
						if (0 == *(praw + width + width))
							D7 = TRUE;
						if (0 == *(praw + width + width + 2))
							D8 = TRUE;
					}
					else if (width - 2 <= x)
					{	//最右边2列
						if (0 == *(praw - width - width - 2))
							D1 = TRUE;
						if (0 == *(praw - width - width))
							D2 = TRUE;
						if (0 == *(praw - 2))
							D4 = TRUE;
						if (0 == *(praw + width + width - 2))
							D6 = TRUE;
						if (0 == *(praw + width + width))
							D7 = TRUE;
					}
					else
					{
						if (0 == *(praw - width - width - 2))
							D1 = TRUE;
						if (0 == *(praw - width - width))
							D2 = TRUE;
						if (0 == *(praw - width - width + 2))
							D3 = TRUE;
						if (0 == *(praw - 2))
							D4 = TRUE;
						if (0 == *(praw + 2))
							D5 = TRUE;
						if (0 == *(praw + width + width - 2))
							D6 = TRUE;
						if (0 == *(praw + width + width))
							D7 = TRUE;
						if (0 == *(praw + width + width + 2))
							D8 = TRUE;
					}
				}

				type = JudgeType_COLOR(D1, D2, D3, D4, D5, D6, D7, D8);
				if (0 == type)
				{
					canNotRepair[badPonitInfo->canNotRepairSum].x = x;
					canNotRepair[badPonitInfo->canNotRepairSum].y = y;
					canNotRepair[badPonitInfo->canNotRepairSum].type = type;
					badPonitInfo->canNotRepairSum += 1;  //   ,out, 检测到的无法被修复的坏点数
				}
				else
				{
					canRepair[badPonitInfo->canRepairSum].x = x;
					canRepair[badPonitInfo->canRepairSum].y = y;
					canRepair[badPonitInfo->canRepairSum].type = type;
					badPonitInfo->canRepairSum += 1;
				}
			}
			++praw;
		}
		raw += width;
	}
}