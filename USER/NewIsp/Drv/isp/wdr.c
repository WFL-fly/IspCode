#include <stdio.h>
#include "wdr.h"
#include "isp_utils.h"

//dol:digital over line ģʽѡ��1��dolģʽ��0��������ع�֡��2��������ع�֡
void set_dol_model(uint8_t mode)
{
	DOL_MODE_SEL = mode;
}

//���ع�����ֵ,u.5.0   
void set_dol_exp_gain(uint8_t gain)
{
	DOL_Exp_Gain = gain;
}

//������ֵ,u.8.0
void set_dol_thr1(uint8_t thr1)
{
	DOL_Thr1 = thr1;
}

//������ֵ���޲���1, б��1/(th2-th1), u.1.16
void set_dol_resi_thr1(float resi_thr1)
{
	DOL_Resi_Thr1 = FLOTOFIX(unsigned int, 16, resi_thr1);
}

//������ֵ���޲���2, б��1/(256-th1),u.1.16
void set_dol_resi_thr2(float resi_thr2)
{
	DOL_Resi_Thr2 = FLOTOFIX(unsigned int, 16, resi_thr2);
}

void set_HDR305_enable(unsigned char enable)
{
	HDR305_EN = enable;
}

void HDR305_Wdata(unsigned int addr,  unsigned int  data){
	
	HDR305_Config_ADDR  = addr;
	HDR305_Config_Wdata = data;
}

void HDR305_setHfHtr1(unsigned int addr,  unsigned int  data)
{
	HDR305_Config_ADDR  = addr;
	HDR305_Config_Wdata = data;
}

int HDR305_Rdata(unsigned int addr)
{
	
	HDR305_Config_ADDR  = addr;
	
	return HDR305_Config_Rdata;
}

int  set_HDR305_Table(unsigned int* lut)
{
	unsigned char i;
	
	for(i=0;i<25;i++)
	{
		printf("i = %d,lut[%d] = %d\n",i,i,lut[i]);	

		int  tmp;
		
		if (i==24)
			tmp = lut[i]<<12 | ( lut[i] & 0xFFF) ;
		else
			tmp = lut[i+1]<<12 | ( lut[i] & 0xFFF) ;
		HDR305_Wdata(i, tmp);
	}
	
	return 0;	
}
