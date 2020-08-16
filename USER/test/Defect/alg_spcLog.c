#include "alg_spcLog.h"
#define PRT_BUF_LEN  1024
char buf[PRT_BUF_LEN];
uint8_t log_level=10;

static FILE *fp=NULL;

FILE * alg_spcLogFileCreate(char *file_path)
{
	if(file_path==NULL)
	{
		return NULL;
	}
	fp=fopen(file_path,"w+");
	return fp;
}
void alg_spcLogFileClose()
{
    if(fp!=NULL)
    {
        fclose(fp);
    }
}
void alg_spcLogf(LogLevel_TypeDef level,const char* fmt, ...)
{
     int len=0;
     va_list arg_ptr;
     if(fp == NULL)
     {
         return ;
     }
     if(level>log_level)
     {
        return ;
     } 
     va_start(arg_ptr,fmt);
     len = vsnprintf((char*)buf,PRT_BUF_LEN,fmt,arg_ptr);
     va_end(arg_ptr);
     fprintf(fp,"%s",buf);
     fflush(fp);
     memset(buf,0,PRT_BUF_LEN);    
}
void alg_spcSetLogLevel(uint8_t level)
{
    log_level=level; 
}
uint8_t alg_spcGetLogLevel()
{
   return log_level;
}