

/****
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"
#include "Alg_GetParameter.h"
#include "file.h"

int main(int argc,char* argv[])
{
    char* file1_path="Black1.bin";
	char* file2_path="Grey1.bin";

    char* save="res.bin";
    int width = 4096 , height = 512;
    uint64_t pixelNum = width * height;
    
    uint64_t i=1;
    uint64_t size = pixelNum *sizeof(uint16_t);

    uint8_t* buf_ptr1 = NULL;
    uint8_t* buf_ptr2 = NULL;

    uint16_t* res = NULL;

    ALG_FFCTable ffcRes;
    ALG_FFCParam ffcParam;
    uint16_t* pU16_Black = NULL;
    uint16_t* pU16_Grey = NULL;
    double sum_black = 0;
    double sum_grey = 0;

     
    buf_ptr1 = (uint8_t*)malloc(size);
    buf_ptr2 = (uint8_t*)malloc(size);


    size = readBinaryFileData(file1_path,(uint8_t*)buf_ptr1,size);
    size = readBinaryFileData(file2_path,(uint8_t*)buf_ptr2,size);
    pU16_Black = (uint16_t*)buf_ptr1;
    pU16_Grey  = (uint16_t*)buf_ptr2;
    for(i=0;i<pixelNum;i++)
    {
        sum_grey += pU16_Grey[i];
        sum_black += pU16_Black[i];
    }
    ffcParam.greyDst = (uint16_t)(sum_grey/pixelNum);
    ffcParam.blackDst  = (uint16_t)(sum_black/pixelNum);

    ffcParam.blackData = (void*)buf_ptr1;
    ffcParam.greyData  = (void*)buf_ptr2;
    ffcParam.nWidth    = width;  		
	ffcParam.nHeight   = height;		
	ffcParam.nBits     = 12;				
	ffcParam.nFormat   = ALG_IMG_FORMAT_MONO;		
	ffcParam.nType     = ALG_TYPE_FFC_REGION;			
	ffcParam.region_height_scale = 16;
	ffcParam.region_width_scale  = 16;
	ffcParam.kb_byte = 3;
    ffcParam.paramIsPick = 1;
                             

    ffcRes.nSize = ALG_GetParameterMemoryLen(&ffcParam);
    ffcRes.pFFCTable = (uint8_t*)malloc(ffcRes.nSize);


    ALG_GetParameterRun(&ffcParam, &ffcRes);
    printf("ffc res size:%d\n",ffcRes.nSize);

    free(buf_ptr1);
    free(buf_ptr2);
    buf_ptr1 = NULL;
    buf_ptr2 = NULL;

    size =  writeBinaryFileData("ffc_res_pick.raw",ffcRes.pFFCTable,ffcRes.nSize);
    free(ffcRes.pFFCTable);
    system("pause");
	return 0;
}
***/