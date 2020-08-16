#include "alg_spcTool.h"
#include "alg_calcCoor_cl.h"

static int ALG_comparePoint(const void *a, const void *b);
static unsigned int changeType(unsigned int type, int version, int flip);

int getBadPointInfo_cl(struct SPC_BADPOINTINFOS *badPonitInfo)
{	
	int i = 0;
	unsigned int currentX, currentY, type;
	for (i = 0; i < 4; i++)
	{
		badPonitInfo->canRepairInfo_CL[i] = (unsigned int *)malloc(badPonitInfo->canRepairSum * sizeof(unsigned int));
		if (NULL == badPonitInfo->canRepairInfo_CL[i])
		{
			return -1;
		}
	}
	
	for (i = 0; i < (int)badPonitInfo->canRepairSum; i++)
	{
		currentX = (unsigned int)((badPonitInfo->canRepairCoordinate + i)->x);
		currentY = (unsigned int)((badPonitInfo->canRepairCoordinate + i)->y);
		type = (unsigned int)((badPonitInfo->canRepairCoordinate + i)->type);
		(badPonitInfo->canRepairInfo_CL[0])[i] = (changeType(type, badPonitInfo->version, 0) << 28) | (currentY << 14) | currentX;
		(badPonitInfo->canRepairInfo_CL[1])[i] = (changeType(type, badPonitInfo->version, 1) << 28) | (currentY << 14) | (unsigned int)(badPonitInfo->width - currentX);
		(badPonitInfo->canRepairInfo_CL[2])[i] = (changeType(type, badPonitInfo->version, 2) << 28) | ((unsigned int)(badPonitInfo->height - currentY) << 14) | currentX;
		(badPonitInfo->canRepairInfo_CL[3])[i] = (changeType(type, badPonitInfo->version, 3) << 28) | ((unsigned int)(badPonitInfo->height - currentY) << 14) | (unsigned int)(badPonitInfo->width - currentX);
	}
	qsort(badPonitInfo->canRepairInfo_CL[1], badPonitInfo->canRepairSum, 4, ALG_comparePoint);
	qsort(badPonitInfo->canRepairInfo_CL[2], badPonitInfo->canRepairSum, 4, ALG_comparePoint);
	qsort(badPonitInfo->canRepairInfo_CL[3], badPonitInfo->canRepairSum, 4, ALG_comparePoint);
	return 0;
}

static unsigned int changeType(unsigned int type, int version, int flip)
{
	unsigned int outType = 0;
	if (SPC_VERSION_101 == version)
	{
		outType = type;
		if (1 == flip)
		{
			if (type == 5)
			{
				outType = 6;
			}
			if (type == 6)
			{
				outType = 5;
			}
			if (type == 13)
			{
				outType = 14;
			}
			if (type == 14)
			{
				outType = 13;
			}
		}
		if (2 == flip)
		{
			if (type == 4)
			{
				outType = 7;
			}
			if (type == 7)
			{
				outType = 4;
			}
			if (type == 12)
			{
				outType = 15;
			}
			if (type == 15)
			{
				outType = 12;
			}
		}
		if (3 == flip)
		{	
			if (type == 5)
			{
				outType = 6;
			}
			if (type == 6)
			{
				outType = 5;
			}
			if (type == 13)
			{
				outType = 14;
			}
			if (type == 14)
			{
				outType = 13;
			}
			if (type == 4)
			{
				outType = 7;
			}
			if (type == 7)
			{
				outType = 4;
			}
			if (type == 12)
			{
				outType = 15;
			}
			if (type == 15)
			{
				outType = 12;
			}
		}
	}

	return outType;
}

static int ALG_comparePoint(const void *a, const void *b)
{
	if ((*(unsigned int *)a & 0xFFFFFFF) < (*(unsigned int *)b & 0xFFFFFFF))
	{
		return -1;
	}
	else if ((*(unsigned int *)a & 0xFFFFFFF) == (*(unsigned int *)b & 0xFFFFFFF))
	{
		return 0;
	}
	else
	{
		return 1;
	}
}