#ifndef _GIC_H_
#define _GIC_H_

#include "isp_base.h"

#define GIC_EN *(volatile unsigned char *) ((ISP_GIC_BASE + COV_CHAR(0x0b)) | (1 << 31))
#define GIC_SWELL *(volatile unsigned short *) ((ISP_GIC_BASE + COV_SHORT(0x08)) | (1 << 31))

void set_GIC_en(uint8_t enable);
void set_swell(uint16_t data_sw);

#endif /* _GIC_H_ */
