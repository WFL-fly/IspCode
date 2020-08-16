#ifndef _EE_H_
#define _EE_H_

#include "isp_base.h"

#define EE_BASE ISP_NR2D_BASE

#define boost_filter_en  *(volatile unsigned char *) ((EE_BASE+COV_CHAR(0x18))|(1<<31))
//u.4.8
#define boost_hf_level  *(volatile unsigned short *) ((EE_BASE+COV_SHORT(0x1a))|(1<<31))
#define boost_shrink_low  *(volatile unsigned char *) ((EE_BASE+COV_CHAR(0x1c))|(1<<31))
#define boost_shrink_high  *(volatile unsigned short *) ((EE_BASE+COV_SHORT(0x1e))|(1<<31))
#define boost_overall_factor  *(volatile unsigned int *)   ((EE_BASE+0x20)|(1<<31))
#define boost_hf_level1  *(volatile unsigned short *)   ((EE_BASE+COV_SHORT(0x24))|(1<<31))



//开关函数
//U.1.0     1----开
void set_ee_enable(unsigned char enable);

//整体锐化强度设置函数,u.4.8 ，255->1*8
void set_ee_level(unsigned short level);

//shrink_low 需要x8
void set_ee_shrink_low(unsigned char level);
void set_ee_shrink_high(unsigned short level);

//亮度因子
void set_ee_overall_factor(unsigned int level);

#endif/**/
