#include "isp.h"
#include "filter.h"

void filter_median(unsigned char enable)
{
	FILTER_MEDIAN_EN = enable;
}

void filter_gauss(unsigned char enable)
{
	FILTER_GAUSS_EN = enable;
}

void filter_gauss_param(unsigned char param_a, unsigned char param_b,
	unsigned char param_c, unsigned short sum_inv)
{
	FILTER_GAUSS_A = param_a;
	FILTER_GAUSS_B = param_b;
	FILTER_GAUSS_C = param_c;
	FILTER_GAUSS_SUM_INV = sum_inv;
}

void filter_bilateral(unsigned char enable)
{
	FILTER_BILATERAL_EN = enable;
}

void filter_bilateral_param(unsigned short slope, unsigned char alpha, 
	unsigned char weight_0, unsigned char weight_1, unsigned char weight_2)
{
	FILTER_BILATERAL_ALPHA = alpha;
	FILTER_BILATERAL_SLOPE = slope;
	FILTER_BILATERAL_WEIGHT = (weight_2 & 0x07) | ((weight_1 & 0x07) << 8) | ((weight_0 & 0x07) << 16);
}
