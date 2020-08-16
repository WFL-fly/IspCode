#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "alg_spcTool.h"
#include "alg_spcLog.h"
int spc_main(int argc,char* argv[])
{
     char* file1_path=NULL;
	char* file2_path=NULL;
    int i=0;
    struct SPC_BADPOINTINFOS spcInfo;
    struct SPC_BADPOINT_RESOUCE imageBuffer;
    detectBadPointInit();
   
     
    memset(&spcInfo,0,sizeof(struct SPC_BADPOINTINFOS));
    memset(&imageBuffer,0,sizeof(struct SPC_BADPOINT_RESOUCE));
   
    spcInfo.imageNumber = 1;					
	spcInfo.width =14192;						
	spcInfo.height = 10640;						
	spcInfo.rawType = SPC_RAW_TYPE_BW;					
	spcInfo.version = SPC_VERSION_101;					
	spcInfo.needBadColumnCorrect = 0;			
	spcInfo.flag_CXP = 0;
    spcInfo.canRepairInfo_CL[0] = NULL;
    spcInfo.canRepairCoordinate = NULL;
    spcInfo.canRepairBadColumnCoordinate = NULL;
	spcInfo.canRepairPointCooratBadCol = NULL;

    imageBuffer.imageNumber = 1;
    for(i=0;i<16;i++)
    {
        imageBuffer.Thr[i] = 8;
        imageBuffer.badColumnThr[i] = 16;
        imageBuffer.badLineThr[i] = 16;
        imageBuffer.pBuffer[i] = NULL;
    }
    for(i=0;i<17;i++)
    {
       spcInfo.badRaw[i]= NULL;
       spcInfo.raw[i]= NULL;
    }
    //OK
    detectBadPointInfo(&imageBuffer,&spcInfo);

    detectBadPointInfo_CL(&spcInfo);

    alg_spcLogf(Log_Neet,"bad point info :\n");
    alg_spcLogf(Log_Neet,"all bad point num :%d\n",spcInfo.badPointSum);
    
    alg_spcLogf(Log_Neet,"can repair bad point num :%d\n",spcInfo.canRepairSum);
    alg_spcLogf(Log_Neet,"bad point position info:(type,x,y)\n");
    for(i=0;i<spcInfo.canRepairSum;i++)
    {
        alg_spcLogf(Log_Neet,"%d,%d,%d\n",spcInfo.canRepairCoordinate[i].type,spcInfo.canRepairCoordinate[i].x,spcInfo.canRepairCoordinate[i].y);
    }
    alg_spcLogf(Log_Neet,"not can repair bad point num :%d\n",spcInfo.canNotRepairSum);
    alg_spcLogf(Log_Neet,"not can repair point position info:(type,x,y)\n");
    for(i=0;i<spcInfo.canNotRepairSum;i++)
    {
        alg_spcLogf(Log_Neet,"%d,%d,%d\n",spcInfo.canNotRepairCoordinate[i].type,spcInfo.canNotRepairCoordinate[i].x,spcInfo.canNotRepairCoordinate[i].y);
    }
    deleteBadPointInfo(&spcInfo);

    deleteBadPointInfo_CL(&spcInfo);
    
    detectBadPointDestroy();
    system("pause");
	return 0;
}