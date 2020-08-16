#include "file.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int endianCon(uint8_t* src_buf,uint8_t* dst_buf,uint64_t dataLen,uint8_t step)
{
    uint64_t i = 0,j=0;
    if( (dataLen%step) != 0 )
    {
        return -1;
    }
    if(step==1)
    {
        memcpy(dst_buf,src_buf,dataLen);
        return 0;
    }
    for(i = 0;i<dataLen;i+=step)
    {
        
        for(j=0;j<step;j++)
        {
            dst_buf[i+j]=src_buf[i+step-1-j];
        }
    }
    return 0;
}
