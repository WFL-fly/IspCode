/*
* define register names of BOC module ,reduce black offset 
* BOC_BASE:	base address of BOC module
* BOC_Gr:      offset of Gr pixel's black level 
* BOC_R:	offset of R pixel's black level 
* BOC_B:		offset of B pixel's black level 
* BOC_Gb:	offset of Gb pixel's black level  
*/
#ifndef _BOC_H_
#define _BOC_H_

#include "isp_base.h"
#include "isp_utils.h"

#define BOC_BASE ISP_BOC_BASE
#define BOC_Gr *(volatile unsigned short *) ((BOC_BASE + COV_SHORT(0x00)) | (1 << 31))
#define BOC_R  *(volatile unsigned short *) ((BOC_BASE + COV_SHORT(0x02)) | (1 << 31))
#define	BOC_B  *(volatile unsigned short *) ((BOC_BASE + COV_SHORT(0x04)) | (1 << 31))
#define BOC_Gb *(volatile unsigned short *) ((BOC_BASE + COV_SHORT(0x06)) | (1 << 31))
#define BOC_DEC *(volatile unsigned int *) (BOC_BASE + 0x40) | (1 << 31))

/* * set, get and init value for BOC module * */
//init BOC modulevoid INIT_BOC(void);
/* * set the offset of black level for RGB channels * parameter list
*   coff:	R,Gr,B,Gb pixel's black level offset, 
* 			  this coff will be applied for all the 4 color channels  
*        parameter type is float, which will be converted to u.10.4 configuring HW register * 
*/

void set_value_Offset_BOC(float coff);
void get_value_Offset_BOC(short *coff);

#endif/*_BOC_H_*/
