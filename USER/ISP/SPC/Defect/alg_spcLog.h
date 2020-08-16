#ifndef __ALG_SPCLOG__
#define __ALG_SPCLOG__
#include <stdio.h>
#include "file.h"
#include "Log.h"
FILE * alg_spcLogFileCreate(char *file_path);
void alg_spcLogFileClose();
void alg_spcSetLogLevel(uint8_t level);
uint8_t alg_spcGetLogLevel();
void alg_spcLogf(LogLevel_TypeDef level,const char* fmt, ...);
#endif
