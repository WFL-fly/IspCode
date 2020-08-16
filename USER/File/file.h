#ifndef __IMAG_FILE__
#define __IMAG_FILE__
#include "TypeDef.h"
uint64_t readBinaryFileData(char *file_path,unsigned char *buf,uint64_t size);
uint64_t writeBinaryFileData(char *file_path,unsigned char *buf,uint64_t size);
#endif