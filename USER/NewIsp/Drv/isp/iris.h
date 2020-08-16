#ifndef _IRIS_H_
#define _IRIS_H_

#include "isp_base.h"




#define IRIS_DC_PWM_DUTY  *(volatile unsigned short *)  ((IRIS_DC_PWM0_BASE+COV_SHORT(0x0))|(1<<31))
#define IRIS_DC_PWM_CYCLE *(volatile unsigned short *)  ((IRIS_DC_PWM0_BASE+COV_SHORT(0x2))|(1<<31))


/* ÉèÖÃdc pwm  */
void set_value_DC_PWM_cycle(unsigned short cycle);

void set_value_DC_PWM_duty(unsigned short duty);

void set_value_DC_strength(unsigned char level);

/* »ñÈ¡dc pwm  */
void get_value_DC_PWM(unsigned short *cycle, unsigned short *duty);


#endif
