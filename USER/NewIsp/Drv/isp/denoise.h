#ifndef _DENOISE_H_
#define _DENOISE_H_

#include "isp_base.h"


//if(i_mm_ben[0]) mm_nr3d_en    <= i_mm_wdata[0];
//if(i_mm_ben[1]) mm_alpha[4:0] <= i_mm_wdata[12:8];
//if(i_mm_ben[2]) mm_level[7:0]       <= i_mm_wdata[23:16];
//if(i_mm_ben[3]) mm_level[  8]         <= i_mm_wdata[24];

#define DENOISE_3D_BASE     *(volatile unsigned short *)((ISP_NR3D_BASE + COV_SHORT(0x00)) | (1 << 31))
#define DENOISE_3D_LEVEL    *(volatile unsigned short *)((ISP_NR3D_BASE + COV_SHORT(0x02)) | (1 << 31))

//降噪模块配参
//使能：1：开启；0：关闭
void set_3Ddenoise_en(uint8_t enable);

//设置alpha值
void set_3Ddenoise_alpha(uint8_t alpha);

//设置level值
void set_3Ddenoise_level(uint16_t level);

//3d降噪功能配置
void DENOISE_setConfig(uint32_t baseAddr3D, uint16_t ispCnt);

#endif
