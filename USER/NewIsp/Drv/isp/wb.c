#include "wb.h"
#include "isp_utils.h"

//set, get and init value for WB module
void INIT_WB(void)
{
	WB_Gr = 0x0100;
	WB_R = 0x0100;
	WB_B = 0x0100;
	WB_Gb = 0x0100;
}

void set_value_Gain_WB(float gr, float r, float b, float gb)
{
	WB_Gr = FLOTOFIX(unsigned short, 8, gr);
	WB_R = FLOTOFIX(unsigned short, 8, r);
	WB_B = FLOTOFIX(unsigned short, 8, b);
	WB_Gb = FLOTOFIX(unsigned short, 8, gb);
}

void get_value_Gain_WB(unsigned short *gr, unsigned short *r, unsigned short *b, unsigned short *gb)
{
	*gr = WB_Gr;
	*r = WB_R;
	*b = WB_B;
	*gb = WB_Gb;
}

void set_value_Gain_WB_thrd(unsigned short gr, unsigned short r, unsigned short b, unsigned short gb)
{
	WB_Gr_CLIP = gr;
	WB_R_CLIP = r;
	WB_B_CLIP = b;
	WB_Gb_CLIP = gb;
}
