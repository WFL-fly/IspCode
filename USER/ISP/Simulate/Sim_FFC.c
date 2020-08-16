#include "Sim_FFC.h"

void FFCPickedParamProcess(uint8_t* pData,int b_h_num,int b_v_num,uint32_t* paramData)
{
    int i = 0, j =0;
    int index =0;
    unsigned char lowValue  = 0;
    unsigned char midValue  = 0;
    unsigned char highValue = 0;
    unsigned int  ptrValue  = 0;
    unsigned int  left_k = 0,right_k = 0,temp_k =0;
    int left_b = 0,right_b = 0,temp_b=0;
    unsigned int  left_val = 0,right_val = 0;
    int h_picked_block_num = (b_h_num+1)/2;
    
    for (i = 0; i < b_v_num; i++)
    {
        for (j = 0; j < h_picked_block_num-1; j++)
        {
            /*****得到左值 和 右值******/
            index = h_picked_block_num * i +j;
            
            highValue = *(pData + 3 * index + 0);
    		midValue  = *(pData + 3 * index + 1);
    		lowValue  = *(pData + 3 * index + 2);
    		ptrValue  = (unsigned int)((highValue<< 16) | (midValue << 8) | lowValue);
            
            left_val = ptrValue;
            left_k = ptrValue >>11;
            
            ptrValue = ptrValue & 0x7ff;
            if(ptrValue & 0x400)
            {
                left_b = ptrValue - 2048;
            }
            else
            {
                left_b = ptrValue;
            }

            index = h_picked_block_num * i + j + 1;
            
            highValue = *(pData + 3 * index + 0);
    		midValue  = *(pData + 3 * index + 1);
    		lowValue  = *(pData + 3 * index + 2);
    		ptrValue  = (unsigned int)((highValue<< 16) | (midValue << 8) | lowValue);

            right_val = ptrValue;
            right_k = ptrValue >>11;
            
            ptrValue = ptrValue & 0x7ff;
            if(ptrValue & 0x400)
            {
                right_b = ptrValue - 2048;
            }
            else
            {
                right_b = ptrValue;
            }
            /***补全 ***/
            index = b_h_num * i + j*2;
    		*(paramData + index) = left_val;

            temp_k = (left_k + right_k)>>1;
            temp_b = (left_b + right_b)/2;

            ptrValue = 0;
            ptrValue = (temp_k<<11) | (temp_b&0x7ff);
            
            index = b_h_num * i + j*2 +1;
            *(paramData + index) = ptrValue;
            
        }

        index = h_picked_block_num * i +j;
            
        highValue = *(pData + 3 * index + 0);
		midValue  = *(pData + 3 * index + 1);
		lowValue  = *(pData + 3 * index + 2);
		ptrValue  = (unsigned int)((highValue<< 16) | (midValue << 8) | lowValue);
            
        if(b_h_num %2)
        {
            index = b_h_num * i + j*2;
            *(paramData + index) = ptrValue;
        }
        else
        {
            index = b_h_num * i + j*2;
            *(paramData + index) = ptrValue;
            index = b_h_num * i + j*2+1;
            *(paramData + index) = ptrValue;
        }
    }
}

void FFCAllParamProcess(uint8_t* pData,int len,uint32_t* paramData)
{
    int i;
    unsigned char lowValue = 0;
    unsigned char midValue = 0;
    unsigned char highValue = 0;
    unsigned int  ptrValue = 0;
	for(i = 0; i < len; i++)
	{
		highValue = *(pData + 3 * i + 0);
		midValue = *(pData + 3 * i + 1);
		lowValue = *(pData + 3 * i + 2);
		ptrValue = (unsigned int)((highValue<< 16) | (midValue << 8) | lowValue);
		*(paramData + i) = (ptrValue);
	} 
}
void FFCParamParse(uint32_t* paramData, int len, float* kTable,int* bTable)
{
    uint32_t temp = 0;
    uint32_t temp_k = 0;
    int i = 0;
    float k =0 , b=0;
    int temp_b =0;
    for( i =0;i<len;i++)
    {
        temp = paramData[i];
        temp_k = temp>>11;
        k    = temp_k /4096.0;

        temp_b = temp&0x7ff;
        if(temp_b&0x400)
        {
            temp_b = temp_b - 2048;
        }
        kTable[i] = k;
        bTable[i] = temp_b;
    }
}
void FFCProcess(uint16_t* pRData ,uint16_t* pGData,uint16_t* pBData, int pixelNum)
{

}
/***
int sim_ffc_main(int argc,char* argv[])
{
    char* file1_path="ffc_pick.bin";
	char* file2_path="ffc_all.bin";


    char* save="res.raw";
    int width = 400 , height = 300;
    int b_h_num = width/16;
    int b_v_num = height/16;
    int regionCnt = b_h_num * b_v_num;

    uint64_t pixelNum = width * height;
    
    uint64_t i=0;
    uint64_t size = pixelNum *sizeof(uint8_t);

    uint8_t* buf_ptr1 = NULL;
    uint8_t* buf_ptr2 = NULL;
    uint32_t* ffc_all_data = NULL;
    float*  k_table = NULL;
    int *   b_table = NULL:
    buf_ptr1 = (uint8_t*)malloc(size);
    buf_ptr2 = (uint8_t*)malloc(size);
    ffc_all_data = (uint32_t*)malloc( regionCnt*sizeof(uint32_t) );
    k_table = (float*)malloc( regionCnt*sizeof(float) );
    b_table = (int*)malloc( regionCnt*sizeof(int) );

    size = readBinaryFileData(file1_path,(uint8_t*)buf_ptr1,0);
    size = readBinaryFileData(file2_path,(uint8_t*)buf_ptr2,0);


    FFCPickedParamProcess(buf_ptr1,b_h_num,b_v_num,ffc_all_data);

    FFCParamParse(ffc_all_data,regionCnt, k_table,b_table);



    for( i =0; i<pixelNum ;i++)
    {
        pRData[i] = buf_ptr1[i]<<6;
        pGData[i] = buf_ptr2[i]<<6;
        pBData[i] = buf_ptr3[i]<<6;
    }
    
    free(buf_ptr1);
    free(buf_ptr2);
    free(ffc_all_data);
    free(k_table);
    free(b_table);

    system("pause");
	return 0;
}
***/