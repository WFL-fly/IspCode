#ifndef P_IRIS_H_
#define P_IRIS_H_

#include "system.h"
#include "commonDefine.h"
 
#define CLK_OF_US 100
#define P_IRIS_BASE 0x9A0E8000

#define IRIS_en        *(volatile uint8_t *) ((P_IRIS_BASE+0x0B)|(1U<<31))
#define P_IRIS_go      *(volatile uint8_t *) ((P_IRIS_BASE+0x0A)|(1U<<31))
#define P_IRIS_back    *(volatile uint8_t *) ((P_IRIS_BASE+0x09)|(1U<<31))
#define P_IRIS_test    *(volatile uint8_t *) ((P_IRIS_BASE+0x08)|(1U<<31))

#define P_IRIS_step   *(volatile uint32_t *) ((P_IRIS_BASE+0x0C)|(1U<<31))
#define P_IRIS_freq   *(volatile uint32_t *) ((P_IRIS_BASE+0x10)|(1U<<31))
#define P_IRIS_DET    *(volatile uint32_t *) ((P_IRIS_BASE+0x14)|(1U<<31))


void EnablePirisMode(uint32_t freq, uint32_t step);
void TrigPirisGo(void);
void TrigPirisBack(void);
uint8_t GetIrisType(void);
void EnableIrisType(uint8_t type);
#endif /* P_IRIS_H_ */
