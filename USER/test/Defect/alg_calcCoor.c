#include "alg_spcTool.h"
#include "alg_calcCoor.h"
#include "alg_spc_101.h"
#include "alg_spc_102.h"
#include "alg_spc_103.h"

int getBadPointCoordinate(struct SPC_BADPOINTINFOS *badPonitInfo)
{	
	//初始化输出，可修复/不可修复点数都少于总点数，申请总点数空间
	int i = 0;
	unsigned char *raw = badPonitInfo->raw[0];
	badPonitInfo->canRepairSum = 0;
	badPonitInfo->canNotRepairSum = 0;
	badPonitInfo->badPointSum = 0;
	
	if (badPonitInfo->needBadColumnCorrect)
	{
		raw =  badPonitInfo->badRaw[0];
	}
	for (i = 0; i < (int)(badPonitInfo->width * badPonitInfo->height); i++)
	{
		if (1 == raw[i])
		{
			badPonitInfo->badPointSum++;
		}
	}

	badPonitInfo->canRepairCoordinate = (struct SPC_BADPOINTINFO *)malloc((badPonitInfo->badPointSum + 1) * sizeof(struct SPC_BADPOINTINFO));
	if (NULL == badPonitInfo->canRepairCoordinate)
	{
		return -1;
	}

	badPonitInfo->canNotRepairCoordinate = (struct SPC_BADPOINTINFO *)malloc((badPonitInfo->badPointSum + 1) * sizeof(struct SPC_BADPOINTINFO));
	if (NULL == badPonitInfo->canNotRepairCoordinate)
	{
		return -1;
	}
	
	if (SPC_VERSION_101 == badPonitInfo->version)
	{
		getBadPointCoordinate_101(badPonitInfo);
	}
	else if (SPC_VERSION_102 == badPonitInfo->version)
	{
		getBadPointCoordinate_102(badPonitInfo);
	}
	else if (SPC_VERSION_103 == badPonitInfo->version)
	{
		getBadPointCoordinate_103(badPonitInfo);
	}
	else
	{
		return -1;
	}
	
	return 0;
}