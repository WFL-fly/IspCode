#ifndef _LVDS_GETCOOR_H_
#define _LVDS_GETCOOR_H_

#ifdef __cplusplus
extern "C" {
#endif 

#include "lvds_alg_spcTool.h"

	int getCoor(struct LVDS_SPCParam *SpcParam, unsigned char *map, struct LVDS_BADPOINTINFO *tmp, struct LVDS_BADPOINTINFO *tmpNoRepair);

#ifdef __cplusplus
}
#endif

#endif