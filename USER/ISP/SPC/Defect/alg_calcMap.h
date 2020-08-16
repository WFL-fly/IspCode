#ifndef _ALG_CALCMAP_H_
#define _ALG_CALCMAP_H_


#ifdef __cplusplus
extern "C" {
#endif 

#include "alg_spcTool.h"



#ifndef CLIP
#define CLIP(_val, _min, _max) ((_val)<(_min) ? (_min) : ((_val)>(_max)?(_max):(_val)))
#endif
#ifndef ABS
#define ABS(_val) ((_val)>0?(_val):(-(_val)))
#endif
#ifndef DIV
#define DIV(a,b) (((b) == 0) ? 0 : (a) / (b))
#endif

//int generateBlackMap(struct SPC_BADPOINT_RESOUCE *pImageBuffer, struct SPC_BADPOINTINFOS *badPonitInfo);
int generateMap(struct SPC_BADPOINT_RESOUCE *pImageBuffer, struct SPC_BADPOINTINFOS *badPonitInfo);
static void generateMap_Raw(unsigned short *res, int imgHeight, int imgWidth, int threshold, int rawType, unsigned char *raw);
void QuickSort(int* values, const int lo, const int hi);

static void generateMap_Raw_cxp(unsigned short *res, int imgHeight, int imgWidth, int threshold, int rawType, unsigned char *raw);
static int AvgFilter(int* values, const int N);
#ifdef __cplusplus
}
#endif

#endif


