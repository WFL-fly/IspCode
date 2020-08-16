#ifndef __SIM_FFC__
#define __SIM_FFC__
#include "TypeDef.h"
void FFCAllParamProcess(uint8_t* pData,int len,uint32_t* paramData);
void FFCPickedParamProcess(uint8_t* pData,int b_h_num,int b_v_num,uint32_t* paramData);
void FFCParamParse(uint32_t* paramData, int len, float* kTable,int* bTable);
#endif