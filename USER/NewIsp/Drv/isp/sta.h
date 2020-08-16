#ifndef _STA_H_
#define _STA_H_

#include "isp.h"
#include "isp_base.h"

#define Adjust_en *(volatile unsigned long *) ((ISP_STA_BASE + 0x08) | (1<<31))
//#define Hist_aver *(volatile unsigned long *) ((ISP_STA_BASE + 0x10)|(1<<31))
#define DATA_BASE_STA (volatile unsigned long *)(ISP_STAMEM_BASE | (1<<31))

#define STA_TOTAL *(volatile unsigned int *)((ISP_STA_BASE + 0x10) | (1<<31))
#define PIXEL_SUM *(volatile unsigned int *)((ISP_STA_BASE + 0x14) | (1<<31))

#define STA_BRT *(volatile short *)((ISP_STA_BASE + COV_SHORT(0x18)) | (1<<31))
#define STA_CTR *(volatile unsigned char *)((ISP_STA_BASE + COV_CHAR(0x1A)) | (1<<31))

#define Start_X *(volatile unsigned int *)((ISP_STA_BASE + 0x20) | (1<<31))
#define Start_Y *(volatile unsigned int *)((ISP_STA_BASE + 0x24) | (1<<31))

#define End_X *(volatile unsigned int *)((ISP_STA_BASE + 0x28) | (1<<31))
#define End_Y *(volatile unsigned int *)((ISP_STA_BASE + 0x2C) | (1<<31))

void set_STA_en(uint8_t enable);
void set_STA_Param(unsigned short strX, unsigned short strY, unsigned short endX, unsigned short endY);
uint16_t get_STA_hist_aver(void);
int Y_adj_lut_conf(int *adj_ram_256x9, int count);
void get_hist(int *hist, int count);
void set_Ctr(float ctr);
int get_STA_hist_pixelsum(void);


#endif /* _STA_H_ */
