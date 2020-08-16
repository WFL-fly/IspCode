#ifndef __LOG__
#define __LOG__
#include "TypeDef.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>    
typedef enum
{
  Log_Neet       = ((uint8_t)0x01),
  Log_Error      = ((uint8_t)0x02), 
  Log_Warnning   = ((uint8_t)0x03),
  Log_Info_l     = ((uint8_t)0x04),
  Log_Info_2     = ((uint8_t)0x05),
  Log_Info_3     = ((uint8_t)0x06)
}LogLevel_TypeDef;
FILE * alg_spcLogFileCreate(char *file_path);
void alg_spcLogFileClose();

void alg_spcSetLogLevel(uint8_t level);
uint8_t alg_spcGetLogLevel();
void alg_spcLogf(LogLevel_TypeDef level,const char* fmt, ...);
#endif
