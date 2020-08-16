#include <stdio.h>
#include "denoise.h"
#include "isp_utils.h"

//使能：1：开启；0：关闭
void set_3Ddenoise_en(uint8_t enable)
{
    uint32_t data = 0;
    data = (DENOISE_3D_BASE & 0xFFFE) | (enable & 0x1);
    DENOISE_3D_BASE = data;
}

//设置alpha值
void set_3Ddenoise_alpha(uint8_t alpha)
{
    uint32_t data = 0;
    data = (DENOISE_3D_BASE & 0x00FF) | ((alpha & 0x10) << 8);
    DENOISE_3D_BASE = data;
}

//设置level值
void set_3Ddenoise_level(uint16_t level)
{
    DENOISE_3D_LEVEL = (level & 0x1FF);
}


//3d降噪功能配置
void DENOISE_setConfig(uint32_t baseAddr3D, uint16_t ispCnt)
{
    MMU_Buf1_Rd_base = baseAddr3D; // 3D 缓存地址
    MMU_Data_Width   = 0x10 * ispCnt;  // 2ISP 数据 32位
}


