#include "isp_utils.h"
#include "boc.h"

//ISP 的boc减黑电平模块
void set_value_Offset_BOC(float coff)
{
	unsigned short offset_boc = FLOTOFIX(unsigned short, 4, coff);	

	BOC_Gr = offset_boc;
	BOC_R = offset_boc;
	BOC_B = offset_boc;
	BOC_Gb = offset_boc;
}

void get_value_Offset_BOC(short * coff)
{
	*coff = FIXTOFLOAT(unsigned short, 4, BOC_R);
}
