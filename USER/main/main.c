#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Log.h"
#include "alg_spcTool.h"
int main(int argc,char* argv[])
{
    char* file1_path=NULL;
	char* file2_path=NULL;
    int i=0;
    struct SPC_BADPOINTINFOS spcInfo;
    struct SPC_BADPOINT_RESOUCE imageBuffer;
    createLogFileObj("spc_log.txt");
    spcInfo.imageNumber = 4;					
	spcInfo.width =6576;						
	spcInfo.height = 4384;						
	spcInfo.rawType = 0;					
	spcInfo.version = 0;					
	spcInfo.needBadColumnCorrect = 0;			
	spcInfo.flag_CXP = 0;
    
    
    imageBuffer.imageNumber = 4;
    for(i=0;i<16;i++)
    {
        imageBuffer.Thr[i] = 16;
        imageBuffer.badColumnThr[i] = 16;
        imageBuffer.badLineThr[i] = 16;
        imageBuffer.pBuffer[i] = NULL;
    }
    detectBadPointInfo(&imageBuffer,&spcInfo);

    //detectMaxBadPointInfo(pImageBufferMax,badPonitInfoMax);

    detectBadPointInfo_CL(&spcInfo);

    deleteBadPointInfo(&spcInfo);

    //deleteMaxBadPointInfo(pImageBufferMax,badPonitInfoMax);

    deleteBadPointInfo_CL(&spcInfo);

    closeLogFileObj();
    system("pause");
	return 0;
}