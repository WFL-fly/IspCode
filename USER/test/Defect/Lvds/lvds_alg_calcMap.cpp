#include "lvds_alg_calcMap.h"
#include"lvds_alg_spcTool.h"


int generateMap_no(struct LVDS_SPCParam *SpcParam, unsigned char * map_no)
{
	unsigned int imgWidth = SpcParam->width;
	int defectCount = SpcParam->defectCount;
	int vaildCount_no = 0;
	int i = 0;
	int x_no = 0, y_no = 0;

	for ( i = 0; i < defectCount; i++)
	{
		x_no = SpcParam->spcRawData[i].x;
		y_no = SpcParam->spcRawData[i].y;

		if (*(map_no + y_no*imgWidth + x_no) == 0)
		{
			*(map_no + y_no*imgWidth + x_no) = 1;
			vaildCount_no++;
		}
	}

	return vaildCount_no;
}
int generateMap_x(struct LVDS_SPCParam *SpcParam, unsigned char * map_x)
{
	unsigned int imgWidth = SpcParam->width;
	int defectCount = SpcParam->defectCount;
	int vaildCount_x = 0;
	int i = 0;
	int x_x = 0, y_x = 0;

	for (i = 0; i < defectCount; i++)
	{
		if ((imgWidth - 1) == SpcParam->spcRawData[i].x)
		{
			continue;
		}
		else
		{
			x_x = imgWidth - 2 - (SpcParam->spcRawData[i].x);
			y_x = SpcParam->spcRawData[i].y;

			if (*(map_x + y_x*imgWidth + x_x) == 0)
			{
				*(map_x + y_x*imgWidth + x_x) = 1;
				vaildCount_x++;
			}
			if (imgWidth - 3 == x_x)
			{
				if (*(map_x + y_x*imgWidth + imgWidth - 1) == 0)
				{
					*(map_x + y_x*imgWidth + imgWidth - 1) = 1;
					vaildCount_x++;
				}
			}
		}
	}

	return vaildCount_x;
}
static int Compare_Point(const void *a, const void *b)
{
	struct LVDS_BADPOINTINFO *c = (struct LVDS_BADPOINTINFO*)a;
	struct LVDS_BADPOINTINFO *d = (struct LVDS_BADPOINTINFO*)b;

	if (c->y == d->y)
	{
		return c->x - d->x;
	}
	else
	{
		return c->y - d->y;
	}
}
void generateMap_y(struct LVDS_BADPOINTINFO *tmp1, struct LVDS_BADPOINTINFO *tmp2, int  count,int height)
{
	int i;
	
	for (i = 0; i < count; i++)
	{
		tmp2[i].x = tmp1[i].x;
		tmp2[i].y = height-1-tmp1[i].y;
		if (12 == tmp1[i].type)
		{
			tmp2[i].type = 15;
		}
		else if (15 == tmp1[i].type)
		{
			tmp2[i].type = 12;
		}
		else
		{
			tmp2[i].type = tmp1[i].type;
		}
	}
	qsort(tmp2, count, sizeof(LVDS_BADPOINTINFO),Compare_Point);
}

