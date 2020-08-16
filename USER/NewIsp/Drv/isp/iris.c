#include "iris.h"
#include "isp_utils.h"
#include "dcp.h"


void set_value_DC_PWM_duty(unsigned short duty)
{
	//printf("%d, cycle=%d, duty=%d\n", __LINE__, cycle, duty);
    //IRIS_DC_PWM_CYCLE = cycle;
    IRIS_DC_PWM_DUTY  = duty;
}

void set_value_DC_PWM_cycle(unsigned short cycle)
{
	IRIS_DC_PWM_CYCLE = cycle;
}

void get_value_DC_PWM(unsigned short *cycle, unsigned short *duty)
{
    *cycle  = IRIS_DC_PWM_CYCLE;
    *duty   = IRIS_DC_PWM_DUTY;
}

void set_value_DC_strength(unsigned char level)
{
	dcp_conf(level);
}