#ifndef _SPC_H_
#define _SPC_H_

#include "isp_base.h"

#define SPC_BASE ISP_SPC_BASE

/// SPC module static pixel correction
#define BUG_PARAM_RAM_BASE  (volatile unsigned int *)   ((SPC_BASE + 0x0000) | (1 << 31))
#define BADCOLUMN_PARAM_RAM_BASE (volatile unsigned int *)   ((SPC_BASE + 0x400c) | (1 << 31))
/*#define BUG_SUM            *(volatile unsigned short *) ((SPC_BASE + COV_SHORT(0x4000)) | (1 << 31))
#define SPC_ENABLE         *(volatile unsigned char *)  ((SPC_BASE + COV_CHAR(0x4002)) | (1 << 31))
#define SPC_RAM_OFFSET     *(volatile unsigned char *)  ((SPC_BASE + COV_CHAR(0x4003)) | (1 << 31))
#define H_ORIGIN           *(volatile unsigned short *) ((SPC_BASE + COV_SHORT(0x4004)) | (1 << 31))
#define V_ORIGIN           *(volatile unsigned short *) ((SPC_BASE + COV_SHORT(0x4006)) | (1 << 31))*/

#define BUG_SUM			0
#define SPC_ENABLE		2
#define SPC_RAM_OFFSET	3
#define H_ORIGIN		4
#define V_ORIGIN		6

//SPC correction enable
void set_SPC_enable(unsigned char en);

//set SPC line ram offset
void set_SPC_line_ram_offset(unsigned char oft);

//set bug sum
void set_SPC_bug_sum(unsigned short sum);

//set offset origin
void set_SPC_origin(unsigned short H_origin, unsigned short V_origin);

//set bug location
void set_SPC_bug_location(unsigned short sum, unsigned int* buf);

void set_SPC_bug_cell(short addr, char type, short x, short y);

unsigned short get_SPC_bug_sum(void);

//spc_alg1,spc_alg2
unsigned char get_SPC_version(void);

//0:mono,1:color
void set_SPC_sensortype(unsigned int sensorType);

void set_image_height(unsigned int height);

void set_badColum_sum(unsigned short sum);

void set_badColumn_bug_loaction(unsigned short sum,unsigned short *buf);

#endif
