#ifndef _FFC_H_
#define _FFC_H_

#include "isp.h"
#include "isp_base.h"

#define FFC_BASE	ISP_FFC_BASE
#define FFC_DATA_BASE_ADDR *(volatile unsigned int *)(MMU_BASE + 0x58)
#define FFC_DATA_LEN_ADDR *(volatile unsigned int *)(MMU_BASE + 0X5C)
#define FFC_BUF_RD_WIDTH_ADDR *(volatile unsigned int *)(MMU_BASE + 0X90)
#define FFC_ENABLE_ADDR	*(volatile unsigned int *)((FFC_BASE + 0xC0) | (1 << 31))
#define FFC_HEIGTH_ADDR	*(volatile unsigned short *)((FFC_BASE + COV_SHORT(0xC4)) | (1 << 31))
#define FFC_WIDTH_ADDR	*(volatile unsigned short *)((FFC_BASE + COV_SHORT(0xC6)) | (1 << 31))

void set_ffc_data_info(unsigned int baseAddr, unsigned int len, unsigned int RD_width);
void set_ffc_enable(unsigned int enable);
void set_ffc_size(unsigned short width, unsigned short heigth);

void get_ffc_SkipIsp(unsigned int *ffc_enable, unsigned int *skip_data);
void set_ffc_SkipIsp(unsigned int ffc_enable, unsigned int skip_data);

#endif/*_FFC_H_*/
