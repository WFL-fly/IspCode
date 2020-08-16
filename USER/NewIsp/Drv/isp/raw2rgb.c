#include "raw2rgb.h"
#include "isp_utils.h"

//set, get and init value for RAW2RGB module
void INIT_RAW2RGB(void)
{
	RAW2RGB_Level = 0x00;
	RAW2RGB_RB_invert = 0x00;
	RAW2RGB_Sel_Mode = 0x01;
}

void set_color_mono_mode_RAW2RGB(unsigned char sensor_mode)
{
	RAW2RGB_COLOR_MONO_Mode = sensor_mode;
}

void set_value_Level_RAW2RGB(unsigned char level)
{
	RAW2RGB_Level = level;
}

void get_value_Level_RAW2RGB(unsigned char *level)
{
	*level = RAW2RGB_Level;
}

void set_value_RB_invert_RAW2RGB(unsigned char rb_invert)
{
	RAW2RGB_RB_invert = rb_invert;
}

void get_value_RB_invert_RAW2RGB(unsigned char *rb_invert)
{
	*rb_invert = RAW2RGB_RB_invert;
}

void set_value_Sel_Mode_RAW2RGB(unsigned char sel_mode)
{
	RAW2RGB_Sel_Mode = sel_mode;
}

void get_value_Sel_Mode_RAW2RGB(unsigned char *sel_mode)
{
	*sel_mode = RAW2RGB_Sel_Mode;
}
