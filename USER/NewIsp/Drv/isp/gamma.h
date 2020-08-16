#ifndef _GAMMA_H_
#define _GAMMA_H_

#include "isp_base.h"

/*
 * define the register name of GAMMA module
 * gamma :10.2
 * GAMMA_BASE:		    base address of GAMMA module
 * MAX_GAMMA_NUM:	    max num of data in gamma RAM
 * GAMMA_RAM_BASE:		base address of RAM table , type :int
 * GAMMA_DATA_BASE:		base address of RAM table , type :short
 * GAMMA_PAGE_SEL:      0:write r=g=b 1:r 2:g 3:b [25:24]
 * */
#define GAMMA_BASE ((ISP_LUT2D_BASE) | (1 << 31))
#define GAMMA_RAM_BASE (volatile unsigned int *) ((GAMMA_BASE) | (1 << 31))

//=0, W r=g=b; =1 rw r table; =2 rw g table; =3 rw b table;
//void GAMMA_SEL();

/*
 * set LUT content for Y table
 * parameter list:
 * gamma_data:	the base for gamma_ram configuration table
 * */
void set_value_DATA_GAMMA(int *gamma_data, int count);

/*
 * get LUT content of Y table
 * parameter list:
 * gamma_data:	 get base address for gamma_ram
 * i		 :   get base address for RAM
 * */
void get_value_DATA_GAMMA(int *gamma_data, short i);

void disable_GAMMA(void);
void enable_GAMMA(void);

#endif
