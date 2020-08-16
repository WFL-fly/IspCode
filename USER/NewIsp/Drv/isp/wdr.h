#ifndef _WDR_H_
#define _WDR_H_

#include "isp_base.h"



#define DOL_MODE_SEL *(volatile unsigned char *) ((DOL_BASE + COV_CHAR(0x04)) | (1 << 31))
#define DOL_Exp_Gain *(volatile unsigned char *) ((DOL_BASE + COV_CHAR(0x08)) | (1 << 31))
#define DOL_Thr1     *(volatile unsigned char *) ((DOL_BASE + COV_CHAR(0x0c)) | (1 << 31))
#define DOL_Resi_Thr1 *(volatile unsigned int *) ((DOL_BASE +  0x10 ) | (1 << 31))
#define DOL_Resi_Thr2 *(volatile unsigned int *) ((DOL_BASE +  0x14) | (1 << 31))
                                                                           
#define HDR305_EN           *(volatile unsigned char *) ((DRC_V305_BASE+COV_CHAR(0x4))|(1<<31))
#define HDR305_R_G_sel      *(volatile unsigned char *) ((DRC_V305_BASE+0x5)|(1<<31))

#define HDR305_HF_THR1      *(volatile unsigned int *) ((DRC_V305_BASE+0x8)|(1<<31))		//Ĭ��:1280
#define HDR305_HF_THR2      *(volatile unsigned int *) ((DRC_V305_BASE+0xC)|(1<<31))		//Ĭ��:16384
#define HDR305_HF_Strength  *(volatile unsigned int *) ((DRC_V305_BASE+0x10)|(1<<31))      //Ĭ��:128
	
#define HDR305_Config_ADDR           *(volatile unsigned int *) ((DRC_V305_BASE+0x14)|(1<<31))
#define HDR305_Config_Wdata          *(volatile unsigned int *) ((DRC_V305_BASE+0x18)|(1<<31))
#define HDR305_Config_Rdata          *(volatile unsigned int *) ((DRC_V305_BASE+0x1C)|(1<<31))

//wdrģ�����
//ģʽѡ��1��dolģʽ��0��������ع�֡��2��������ع�֡
void set_dol_model(uint8_t mode);

//���ع�����ֵ,u.5.0   
void set_dol_exp_gain(uint8_t gain);

//������ֵ,u.8.0
void set_dol_thr1(uint8_t thr1);

//������ֵ���޲���1,б��1/(th2-th1), u.1.16
void set_dol_resi_thr1(float resi_thr1);

//������ֵ���޲���2,б�� 1/(256-th1),u.1.16
void set_dol_resi_thr2(float resi_thr2);

void set_HDR305_enable(unsigned char enable);
void HDR305_Wdata(unsigned int addr,  unsigned int  data);
int  HDR305_Rdata(unsigned int addr);
int  set_HDR305_Table();

#endif
