#ifndef _CCM_H_
#define _CCM_H_

#include "isp_base.h"

/*
 * define the register names of CCM module
 *
 * ctrl_base:		  base address of CCM module
 * CCM_GainRR:		CCM module correction matrix parameter  GainRR
 * CCM_GainGR:		CCM module correction matrix parameter  GainGR
 * CCM_GainBR:		CCM module correction matrix parameter  GainBR
 * CCM_GainRG:		CCM module correction matrix parameter  GainRG
 * CCM_GainGG:		CCM module correction matrix parameter  GainGG
 * CCM_GainBG:		CCM module correction matrix parameter  GainBG
 * CCM_GainRB:		CCM module correction matrix parameter  GainRB
 * CCM_GainGB:		CCM module correction matrix parameter  GainGB
 * CCM_GainBB:		CCM module correction matrix parameter  GainBB
 * CCM_Offset_R:	offset of R in CCM module
 * CCM_Offset_G:	offset of G in CCM module
 * CCM_Offset_B:	offset of B in CCM module
 */

#define CCM_BASE ISP_CCM_BASE

#define CCM_GainRR   *(volatile short *)((CCM_BASE + COV_SHORT(0x00)) | (1 << 31))
#define CCM_GainGR   *(volatile short *)((CCM_BASE + COV_SHORT(0x02)) | (1 << 31))
#define CCM_GainBR   *(volatile short *)((CCM_BASE + COV_SHORT(0x04)) | (1 << 31))
#define CCM_GainRG   *(volatile short *)((CCM_BASE + COV_SHORT(0x06)) | (1 << 31))
#define CCM_GainGG   *(volatile short *)((CCM_BASE + COV_SHORT(0x08)) | (1 << 31))
#define CCM_GainBG   *(volatile short *)((CCM_BASE + COV_SHORT(0x0A)) | (1 << 31))
#define CCM_GainRB   *(volatile short *)((CCM_BASE + COV_SHORT(0x0C)) | (1 << 31))
#define CCM_GainGB   *(volatile short *)((CCM_BASE + COV_SHORT(0x0E)) | (1 << 31))
#define CCM_GainBB   *(volatile short *)((CCM_BASE + COV_SHORT(0x10)) | (1 << 31))
#define CCM_Offset_R *(volatile short *)((CCM_BASE + COV_SHORT(0x12)) | (1 << 31))
#define CCM_Offset_G *(volatile short *)((CCM_BASE + COV_SHORT(0x14)) | (1 << 31))
#define CCM_Offset_B *(volatile short *)((CCM_BASE + COV_SHORT(0x16)) | (1 << 31))

/*
 * set, get and init value for CCM module
 * */
//init the CCM module
void INIT_CCM(void);

/*
 * set CCM module R G B's color correction matrix parameter
 * parameter list：
 * rr:	CCM module correction matrix parameter: GainRR,	float  type, then converted to s.5.10 configuring HW register
 * gr:	CCM module correction matrix parameter: GainGR,	float  type, then converted to s.5.10 configuring HW register
 * br:	CCM module correction matrix parameter: GainBR,	float  type, then converted to s.5.10 configuring HW register
 * rg:	CCM module correction matrix parameter: GainRG,	float  type, then converted to s.5.10 configuring HW register
 * gg:	CCM module correction matrix parameter: GainGG,	float  type, then converted to s.5.10 configuring HW register
 * bg:	CCM module correction matrix parameter: GainBG,	float  type, then converted to s.5.10 configuring HW register
 * rb:	CCM module correction matrix parameter: GainRB,	float  type, then converted to s.5.10 configuring HW register
 * gb:	CCM module correction matrix parameter: GainGB,	float  type, then converted to s.5.10 configuring HW register
 * bb:	CCM module correction matrix parameter: GainBB,	float  type, then converted to s.5.10 configuring HW register
 * */
void set_value_GainRGB_CCM(float rr, float gr, float br, float rg, float gg, float bg, float rb, float gb, float bb);

void get_value_GainRGB_CCM(short *rr, short *gr, short *br, short *rg, short *gg, short *bg, short *rb, short *gb, short *bb);

/*
 * set CCM module R G B's offset
 * parameter list：
 * offset_r:	R offset in CCM module, float,   converted to s.10.4
 * offset_g:	G offset in CCM module, float,	 converted to s.10.4
 * offset_b:	B offset in CCM module, float,	 converted to s.10.4
 * */
void set_value_OffsetRGB_CCM(float offset_r, float offset_g, float offset_b);

void get_value_OffsetRGB_CCM(short *offset_r, short *offset_g, short *offset_b);

#endif
