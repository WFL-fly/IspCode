/*
 * ee_driver.c
 *
 *  Created on: 2015-04-17
 *      Author: 21606
 */

#include "ee_driver.h"

/******************EE简化版本*************************/

void set_ee_enable(unsigned char enable)
{
	//	printf("%s,%d\n",__FUNCTION__,enable);
	boost_filter_en = enable;
}

//整体锐化强度设置函数
void set_ee_level(unsigned short level)
{
	//	printf("%s,%d\n",__FUNCTION__,level);
	boost_hf_level = level;
	boost_hf_level1 = level;
}

void set_ee_shrink_low(unsigned char level)
{
	//	printf("%s,%d\n",__FUNCTION__,level);
	boost_shrink_low = level;
}

void set_ee_shrink_high(unsigned short level)
{
	//	printf("%s,%d\n",__FUNCTION__,level);
	boost_shrink_high = level;
}

void set_ee_overall_factor(unsigned int level)
{
	//	printf("%s,%d\n",__FUNCTION__,level);
	boost_overall_factor = level;
}


