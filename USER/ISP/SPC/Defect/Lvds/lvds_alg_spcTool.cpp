/* ========================================================================== */
/*                             头文件区                                       */
/* ========================================================================== */

#include "lvds_alg_spcTool.h"
#include "lvds_alg_calcMap.h"
#include "lvds_getCoor.h"

static boolean CHECK_ERROR_SPC_BADPOINT_RESOUCE(struct LVDS_SPCParam *SpcParam);

int detectBadPointInfo_lvds(struct LVDS_SPCParam *SpcParam, struct LVDS_SPCTable *SpcTable)
{
	int i, num_no, num_x;
	int RepairSum_no=0;
	int RepairSum_x=0;
	int RepairSum_y = 0;
	int RepairSum_xy = 0;
	int NotRepairSum_no=0;
	int NotRepairSum_x = 0;

	if (! CHECK_ERROR_SPC_BADPOINT_RESOUCE(SpcParam))
	{
		return -1;
	}
	unsigned int width = SpcParam->width;
	unsigned int height = SpcParam->height;
	int reverseFlag = SpcParam->reverseFlag;

	unsigned char *map_no = (unsigned char *)malloc(width * height * sizeof(unsigned char));
	if (map_no == NULL)
	{
		printf("%s map_no : malloc failed\n", __FUNCTION__);
		return -1;
	}
	memset(map_no, 0, height * width * sizeof(unsigned char));

	unsigned char *map_x = (unsigned char *)malloc(width * height * sizeof(unsigned char));
	if (map_x == NULL)
	{
		printf("%s map_x : malloc failed\n", __FUNCTION__);
		return -1;
	}
	memset(map_x, 0, height * width * sizeof(unsigned char));

	num_no = generateMap_no(SpcParam, map_no); //spcRawData  原图的坏点信息图
	num_x = generateMap_x(SpcParam,map_x); //spcRawData   x轴翻转的坏点信息图   
	
	LVDS_BADPOINTINFO* tmp[4] = { NULL };
	LVDS_BADPOINTINFO* tmpNoRepair[2] = { NULL };
	tmp[0] = (LVDS_BADPOINTINFO *)malloc(num_no * sizeof(LVDS_BADPOINTINFO));
	tmp[2] = (LVDS_BADPOINTINFO *)malloc(num_no * sizeof(LVDS_BADPOINTINFO));
	tmpNoRepair[0] = (LVDS_BADPOINTINFO *)malloc(num_no * sizeof(LVDS_BADPOINTINFO));

	tmp[1] = (LVDS_BADPOINTINFO *)malloc(num_x * sizeof(LVDS_BADPOINTINFO));
	tmp[3] = (LVDS_BADPOINTINFO *)malloc(num_x * sizeof(LVDS_BADPOINTINFO));
	tmpNoRepair[1] = (LVDS_BADPOINTINFO *)malloc(num_x * sizeof(LVDS_BADPOINTINFO));

	NotRepairSum_no = getCoor(SpcParam, map_no, tmp[0], tmpNoRepair[0]);
	RepairSum_no = num_no -NotRepairSum_no;

	//for (int i = 0; i < num_no; i++)
	//{
	//	printf("原图\n >> >> > (%d, %d, %d)\n", (tmp[0] + i)->y, (tmp[0] + i)->x, (tmp[0] + i)->type);
	//}

	NotRepairSum_x = getCoor(SpcParam, map_x, tmp[1], tmpNoRepair[1]);
	RepairSum_x = num_x - NotRepairSum_x;

	//for (int i = 0; i < num_x; i++)
	//{
	//	printf("x轴翻转\n >> >> > (%d, %d, %d)\n", (tmp[1] + i)->y, (tmp[1] + i)->x, (tmp[1] + i)->type);
	//}

	generateMap_y(tmp[0], tmp[2], RepairSum_no, height);//  可修复坏点   y轴翻转的坏点信息

	//for (int i = 0; i < num_no; i++)
	//{
	//	printf("y轴翻转\n >> >> > (%d, %d, %d)\n", (tmp[2] + i)->y, (tmp[2] + i)->x, (tmp[2] + i)->type);
	//}

	generateMap_y(tmp[1], tmp[3], RepairSum_x, height);//  xy轴翻转的坏点信息
	
	//for (int i = 0; i < num_x; i++)
	//{
	//	printf("xy轴翻转\n >> >> > (%d, %d, %d)\n", (tmp[3] + i)->y, (tmp[3] + i)->x, (tmp[3] + i)->type);
	//}
	


	if (!reverseFlag)
	{
		SpcTable->canNotRepairSum_no = NotRepairSum_no;
		SpcTable->canNotRepairSum_x = NotRepairSum_x;
		SpcTable->canRepairSum_no = RepairSum_no;
		SpcTable->canRepairSum_x = RepairSum_x;
		SpcTable->canRepairSum_y = RepairSum_no;
		SpcTable->canRepairSum_xy = RepairSum_x;
			;
		SpcTable->canRepairPoint_no = tmp[0];
		SpcTable->canRepairPoint_x = tmp[1];
		SpcTable->canRepairPoint_y = tmp[2];
		SpcTable->canRepairPoint_xy = tmp[3];
		SpcTable->canNotRepairPoint_no = tmpNoRepair[0];
		SpcTable->canNotRepairPoint_x = tmpNoRepair[1];

	}
	else
	{
		SpcTable->canNotRepairSum_no = NotRepairSum_x;
		SpcTable->canNotRepairSum_x = NotRepairSum_no;
		SpcTable->canRepairSum_no = RepairSum_x;
		SpcTable->canRepairSum_x = RepairSum_no;
		SpcTable->canRepairSum_y = RepairSum_x;
		SpcTable->canRepairSum_xy = RepairSum_no;

		SpcTable->canRepairPoint_no = tmp[1];
		SpcTable->canRepairPoint_x = tmp[0];
		SpcTable->canRepairPoint_y = tmp[3];
		SpcTable->canRepairPoint_xy = tmp[2];
		SpcTable->canNotRepairPoint_no = tmpNoRepair[1];
		SpcTable->canNotRepairPoint_x = tmpNoRepair[0];

	}
	
	free(map_no);
	free(map_x);

	return 0;
}
static boolean CHECK_ERROR_SPC_BADPOINT_RESOUCE(struct LVDS_SPCParam *SpcParam)
{
	//指针为空
	if (NULL == SpcParam)
	{
		return FALSE;
	}
	if (0 == SpcParam->width)
	{
		return FALSE;
	}

	if (0 == SpcParam->height)
	{
		return FALSE;
	}

	if ((0 != SpcParam->rawType)&&(1 != SpcParam->rawType))
	{
		return FALSE;
	}

	if (0 == SpcParam->version)
	{
		return FALSE;
	}
	if (0 == SpcParam->defectCount)
	{
		return FALSE;
	}
	if ((0 != SpcParam->reverseFlag)&&(1 != SpcParam->reverseFlag))
	{
		return FALSE;
	}
	
	
	return TRUE;
}
int deleteBadPointInfo_lvds(LVDS_SPCTable *SpcTable)
{
	if (NULL != SpcTable->canRepairPoint_no)
	{
		free(SpcTable->canRepairPoint_no);
		SpcTable->canRepairPoint_no = NULL;
	}
	if (NULL != SpcTable->canRepairPoint_x)
	{
		free(SpcTable->canRepairPoint_x);
		SpcTable->canRepairPoint_x = NULL;
	}
	if (NULL != SpcTable->canRepairPoint_y)
	{
		free(SpcTable->canRepairPoint_y);
		SpcTable->canRepairPoint_y = NULL;
	}
	if (NULL != SpcTable->canRepairPoint_xy)
	{
		free(SpcTable->canRepairPoint_xy);
		SpcTable->canRepairPoint_xy = NULL;
	}
	if (NULL != SpcTable->canNotRepairPoint_no)
	{
		free(SpcTable->canNotRepairPoint_no);
		SpcTable->canNotRepairPoint_no = NULL;
	}
	if (NULL != SpcTable->canNotRepairPoint_x)
	{
		free(SpcTable->canNotRepairPoint_x);
		SpcTable->canNotRepairPoint_x = NULL;
	}
	return 0;
}