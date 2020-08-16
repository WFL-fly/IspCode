#include "rgb2yuv.h"
#include "isp_utils.h"

//set  get, and init value for CSC_CDC module
void INIT_CSC_CDC(void)
{
	CSC_CDC_Module_Select = 0x00;
	CSC_CDC_Y_Switch = 0x00;
	CSC_CDC_UV_Select = 0x00;
	CSC_CDC_BW_Ena = 0x00;
	CSC_CDC_KY_G = 0x96;
	CSC_CDC_KY_B = 0x1D;
	CSC_CDC_KY_R = 0x4D;
	CSC_CDC_KCr_R = 0x80;
	CSC_CDC_KCb_B = 0x80;
	CSC_CDC_KCb_G = 0xFFAC;
	CSC_CDC_KCb_R = 0xFFD5;
	CSC_CDC_KCr_B = 0xFFEC;
	CSC_CDC_KCr_G = 0xFF95;
	CSC_CDC_Offset_Cr = 0x80;
	CSC_CDC_Offset_Cb = 0x80;
	CSC_CDC_Offset_Y = 0x0000;
	CSC_CDC_KNEE = 0x0040;
	CSC_CDC_KNEEP = 0x01FF;
	CSC_CDC_Y_Gain = 0x80;
	CSC_CDC_Thres_l = 0x00;
	CSC_CDC_Y_Level = 0xFF;
	CSC_CDC_Ctr = 0x10;
	CSC_CDC_Cos = 0x20;
	CSC_CDC_Sin = 0x00;
	CSC_CDC_Sat = 0x20;
	CSC_CDC_Brt = 0x00;
}

void set_value_module_UV_CSC_CDC(unsigned char module, unsigned char uv)
{
	CSC_CDC_Module_Select = module;
	CSC_CDC_UV_Select = uv;
}

void get_value_module_UV_CSC_CDC(unsigned char *module, unsigned char *uv)
{
	*module = CSC_CDC_Module_Select;
	*uv = CSC_CDC_UV_Select;
}

void set_value_Y_Switch_CSC_CDC(unsigned char y_switch)
{
	CSC_CDC_Y_Switch = y_switch;
}

void get_value_Y_Switch_CSC_CDC(unsigned char *y_switch)
{
	*y_switch = CSC_CDC_Y_Switch;
}

void set_value_BW_Ena_Switch_CSC_CDC(unsigned char bw_ena)
{
	CSC_CDC_BW_Ena = bw_ena;
}

void get_value_BW_Ena_Switch_CSC_CDC(unsigned char *bw_ena)
{
	*bw_ena = CSC_CDC_BW_Ena;
}

void set_value_module_RGB2YUV_CSC_CDC(float y_g, float y_b, float y_r, float cr_r, float cb_b, float cb_g, float cb_r, float cr_b, float cr_g)
{
	CSC_CDC_KY_G = FLOTOFIX(unsigned char, 8, y_g + 1.0/512);
	CSC_CDC_KY_B = FLOTOFIX(unsigned char, 8, y_b + 1.0/512);
	CSC_CDC_KY_R = FLOTOFIX(unsigned char, 8, y_r + 1.0/512);
	CSC_CDC_KCr_R = FLOTOFIX(unsigned char, 8, cr_r + 1.0/512);
	CSC_CDC_KCb_B = FLOTOFIX(unsigned char, 8, cb_b + 1.0/512);
	CSC_CDC_KCb_G = FLOTOFIX(short, 8, cb_g - 1.0/512);
	CSC_CDC_KCb_R = FLOTOFIX(short, 8, cb_r - 1.0/512);
	CSC_CDC_KCr_B = FLOTOFIX(short, 8, cr_b - 1.0/512);
	CSC_CDC_KCr_G = FLOTOFIX(short, 8, cr_g - 1.0/512);
}

void get_value_module_RGB2YUV_CSC_CDC(unsigned char *y_g, unsigned char *y_b, unsigned char *y_r, unsigned char *cr_r, unsigned char *cb_b, short *cb_g, short *cb_r, short *cr_b, short *cr_g)
{
	*y_g = CSC_CDC_KY_G;
	*y_b = CSC_CDC_KY_B;
	*y_r = CSC_CDC_KY_R;
	*cr_r = CSC_CDC_KCr_R;
	*cb_b = CSC_CDC_KCb_B;
	*cb_g = CSC_CDC_KCb_G;
	*cb_r = CSC_CDC_KCb_R;
	*cr_b = CSC_CDC_KCr_B;
	*cr_g = CSC_CDC_KCr_G;
}

void set_value_offset_CSC_CDC(unsigned char cr, unsigned char cb, short y)
{
	CSC_CDC_Offset_Cr = cr;
	CSC_CDC_Offset_Cb = cb;
	CSC_CDC_Offset_Y = y;
}

void get_value_offset_CSC_CDC(unsigned char *cr, unsigned char *cb, short *y)
{
	*cr = CSC_CDC_Offset_Cr;
	*cb = CSC_CDC_Offset_Cb;
	*y = CSC_CDC_Offset_Y;
}

void set_value_Hist_Gain_CSC_CDC(float y_gain, unsigned char thres_l)
{
	CSC_CDC_Y_Gain = FLOTOFIX(unsigned char, 7, y_gain);
	CSC_CDC_Thres_l = thres_l;
}

void get_value_Hist_Gain_CSC_CDC(unsigned char *y_gain, unsigned char *thres_l)
{
	*y_gain = CSC_CDC_Y_Gain;
	*thres_l = CSC_CDC_Thres_l;
}

void set_value_Y_Level_CSC_CDC(unsigned short y_level)
{
	CSC_CDC_Y_Level = y_level;
}

void get_value_Y_Level_CSC_CDC(unsigned short *y_level)
{
	*y_level = CSC_CDC_Y_Level;
}

void set_value_Ctr_CSC_CDC(float ctr)
{
	CSC_CDC_Ctr = FLOTOFIX(unsigned char, 4, ctr);
}

void get_value_Ctr_CSC_CDC(unsigned char *ctr)
{
	*ctr = CSC_CDC_Ctr;
}

void set_value_Hue_CSC_CDC(float cos, float sin)
{
	CSC_CDC_Cos = FLOTOFIX(char, 5, cos);
	CSC_CDC_Sin = FLOTOFIX(char, 5, sin);
}

void get_value_Hue_CSC_CDC(char *cos, char *sin)
{
	*cos = CSC_CDC_Cos;
	*sin = CSC_CDC_Sin;
}

void set_value_Sat_CSC_CDC(float sat)
{
	CSC_CDC_Sat = FLOTOFIX(unsigned char, 5, sat);
}

void get_value_Sat_CSC_CDC(unsigned char *sat)
{
	*sat = CSC_CDC_Sat;
}

void set_value_Brt_CSC_CDC(short brt)
{
	CSC_CDC_Brt = brt;
}

void get_value_Brt_CSC_CDC(short *brt)
{
	*brt = CSC_CDC_Brt;
}
