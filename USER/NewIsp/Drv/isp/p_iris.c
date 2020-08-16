#include "p_iris.h"
#include "utils.h"
#include "logmodule.h"

#define CLK_SYS            100000000

uint8_t GetIrisType(void)
{
	return (uint8_t)(P_IRIS_DET);
}

void EnableIrisType(uint8_t type)
{
	IRIS_en = type;
}

void EnablePirisMode(uint32_t freq, uint32_t step)
{
	uint32_t freq_cov ;		
		
	if(step > 0xfff)
		P_IRIS_step = 0xfff;
	else 		
		P_IRIS_step = step;

	if(freq==0)
		freq_cov = 0;
	else
		freq_cov = (uint32_t)(4*CLK_SYS/freq);

	if(freq_cov > 0xffffff)
		P_IRIS_freq = 0xffffff;	
	else 		
		P_IRIS_freq = freq_cov;
	
	P_IRIS_test   = 0;
}

void TrigPirisGo(void)
{
	uint8_t lastGo;
	lastGo    = P_IRIS_go;
	P_IRIS_go = ~lastGo; 
}

void TrigPirisBack(void)
{
	uint8_t lastBack;
	lastBack    = P_IRIS_back;
	P_IRIS_back = ~lastBack;
}
