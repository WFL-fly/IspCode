#ifndef _AVG_H_
#define _AVG_H_

#include "isp_base.h"

#if defined(AX7B96XG060) || defined(AX7B96XG06A) || defined(AX7B96XG35B)

#define AVG_num    *(volatile unsigned int *) ((0x8E000DE4)|(1U<<31))
#define AVG_enable *(volatile unsigned int *) ((0x8E000DE4)|(1U<<31))

#define AVG_version 2
#else

#define AVG_BASE ISP_AVG_BASE

#define AVG_num    *(volatile uint8_t *) ((AVG_BASE+0x03)|(1U<<31))
#define AVG_enable *(volatile uint8_t *) ((AVG_BASE+0x02)|(1U<<31))
#define AVG_version 1

#endif


void AVG_Set_num(uint8_t nAVG_num);
void AVG_Get_num(uint8_t *nAVG_num);
void AVG_Set_enable(uint8_t nAVG_enable);
void AVG_Get_enable(uint8_t *nAVG_enable);

#endif
