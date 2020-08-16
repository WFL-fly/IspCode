#include "ccm.h"
#include "isp_utils.h"

//set  get, and init value for CCM module
void INIT_CCM(void)
{
	CCM_GainRR = 0x0400;
	CCM_GainGR = 0x0000;
	CCM_GainBR = 0x0000;
	CCM_GainRG = 0x0000;
	CCM_GainGG = 0x0400;
	CCM_GainBG = 0x0000;
	CCM_GainRB = 0x0000;
	CCM_GainGB = 0x0000;
	CCM_GainBB = 0x0400;
	CCM_Offset_R = 0x0000;
	CCM_Offset_G = 0x0000;
	CCM_Offset_B = 0x0000;
}

//void set_value_GainRGB_CCM(short rr, short gr, short br, short rg, short gg, short bg, short rb, short gb, short bb)
void set_value_GainRGB_CCM(float rr, float gr, float br, float rg, float gg, float bg, float rb, float gb, float bb)
{
	CCM_GainRR = FLOTOFIX(short, 10, rr);
	CCM_GainGR = FLOTOFIX(short, 10, gr);
	CCM_GainBR = FLOTOFIX(short, 10, br);
	CCM_GainRG = FLOTOFIX(short, 10, rg);
	CCM_GainGG = FLOTOFIX(short, 10, gg);
	CCM_GainBG = FLOTOFIX(short, 10, bg);
	CCM_GainRB = FLOTOFIX(short, 10, rb);
	CCM_GainGB = FLOTOFIX(short, 10, gb);
	CCM_GainBB = FLOTOFIX(short, 10, bb);
}
void get_value_GainRGB_CCM(short *rr, short *gr, short *br, short *rg, short *gg, short *bg, short *rb, short *gb, short *bb)
{
	*rr = CCM_GainRR;
	*gr = CCM_GainGR;
	*br = CCM_GainBR;
	*rg = CCM_GainRG;
	*gg = CCM_GainGG;
	*bg = CCM_GainBG;
	*rb = CCM_GainRB;
	*gb = CCM_GainGB;
	*bb = CCM_GainBB;
}

void set_value_OffsetRGB_CCM(float offset_r, float offset_g, float offset_b)
{
	CCM_Offset_R = FLOTOFIX(short, 4, offset_r);
	CCM_Offset_G = FLOTOFIX(short, 4, offset_g);
	CCM_Offset_B = FLOTOFIX(short, 4, offset_b);
}

void get_value_OffsetRGB_CCM(short *offset_r, short *offset_g, short *offset_b)
{
	*offset_r = CCM_Offset_R;
	*offset_g = CCM_Offset_G;
	*offset_b = CCM_Offset_B;
}
