#include "isp.h"
#include "gic.h"

void set_GIC_en(uint8_t enable)
{
	GIC_EN = enable;
}

void set_swell(uint16_t data_sw)
{
	GIC_SWELL = data_sw;
}
