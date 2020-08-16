#ifndef __ALG_LOG__
#define __ALG_LOG__
#include "file.h"
#include "Log.h"
FILE * alg_LogFileCreate(char *file_path);
void alg_LogFileClose();
void alg_SetLogLevel(uint8_t level);
uint8_t alg_GetLogLevel();
void alg_Logf(LogLevel_TypeDef level,const char* fmt, ...);
#endif
