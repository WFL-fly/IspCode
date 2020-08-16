#ifndef _ALG_CALCBADCOLUMNMAP_H_
#define _ALG_CALCBADCOLUMNMAP_H_

#include "alg_calcMap.h"

void judgebadPointsIsbadColumn(unsigned char *raw, int imgHeight, int imgWidth, int rawType);
void generateBadColumnMap_Raw(unsigned short *res, int imgHeight, int imgWidth, int threshold, int rawType, unsigned char *raw);

#endif