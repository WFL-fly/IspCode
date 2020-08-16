#ifndef _ALG_CALCMAP_LVDS_H_
#define _ALG_CALCMAP_LVDS_H_

#ifdef __cplusplus
extern "C" {
#endif 

#include "lvds_alg_spcTool.h"

int generateMap_no(struct LVDS_SPCParam *SpcParam, unsigned char * map_no);

int generateMap_x(struct LVDS_SPCParam *SpcParam, unsigned char * map_x);

void generateMap_y(struct LVDS_BADPOINTINFO *tmp1, struct LVDS_BADPOINTINFO *tmp2, int  count, int height);

#ifdef __cplusplus
}
#endif

#endif