#include "isp_utils.h"
#include "avg.h"
#include "gvsp_conf.h"

uint8_t avg_Select = 0;

void AVG_Set_num(uint8_t nAVG_num)
{
    avg_Select = AVG_version;
    
    if (avg_Select == 1)
    {
        AVG_num = nAVG_num;
    }
    else if (avg_Select == 2)
    {
        AVG_num = ((AVG_num & 0xFFFFFF0F) | (nAVG_num<<4));
    }
	
}

void AVG_Get_num(uint8_t *nAVG_num)
{
    if (avg_Select == 1)
    {
        *nAVG_num = AVG_num;
    }
	else if (avg_Select == 2)
    {
        *nAVG_num = (AVG_num & 0x0F)>>4;
    }
}

void AVG_Set_enable(uint8_t nAVG_enable)
{
    avg_Select = AVG_version;

    if (avg_Select == 1)
    {
        AVG_enable = nAVG_enable;

    	if(nAVG_enable>0)
    	{
    		GVSPStreamPayloadPara payloadParam;
    		Gvsp_Get_Stream_Payload_Param(&payloadParam);
    		MMU_Buf1_Rd_base = 0x680;
    		MMU_Buf1_Rd_len = payloadParam.nSize_x*payloadParam.nSize_y*2;
    	}
    }
    else if (avg_Select == 2)
    {
        AVG_enable = ((AVG_enable & 0xFFFFFFFE) | nAVG_enable);
    }
	
}

void AVG_Get_enable(uint8_t *nAVG_enable)
{

    if (avg_Select == 1)
    {
        *nAVG_enable = AVG_enable;
    }
    else if (avg_Select == 2)
    {
        *nAVG_enable = (AVG_enable & 0x1);
    }
	
}

