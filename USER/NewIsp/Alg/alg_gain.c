#include "aew.h"
/*******************************************************************************
* ������  : AlgGain_getAGainIndex
* ��  ��  : ���ݵ�ǰ������������ֵ����ȡ��Ӧģ�����浵λ
* ��  ��  : ��
* ��  ��  : �ޡ�
* ����ֵ  : ģ�����浵λ
*******************************************************************************/
static Uint8 AlgGain_getAGainIndex(void)
{
    Uint8 i =0 ;
    APP_GainControl *pAppGainCtr = \
        (APP_GainControl *)AEW_paraGetPtr(PARA_AEW_APP_GAIN_PARAMS);
    for(i=0;i<pAppGainCtr->aGainNum;i++)
    {
        if( pAppGainCtr->gainVal > pAppGainCtr->aGainTable[i]-0.01f)
        {
            break;
        }
    }
    return i;
}
/*******************************************************************************
* ������  : APP_gainCalc
* ��  ��  : ���ݽ�������ֵ����ģ���������������
* ��  ��  : ��
* ��  ��  : aGain��ģ������;dGain���������档
* ����ֵ  : ��
*******************************************************************************/
void  AlgGain_gainValCalc(float *aGain, float *dGain)
{
     int i = 0;
	 Uint8 minAIndex = 0;
     APP_GainControl *pAppGainCtr = \
        (APP_GainControl *)AEW_paraGetPtr(PARA_AEW_APP_GAIN_PARAMS);
     if(pAppGainCtr->aGainNum ==0)
     {
         /**������ģ������***/
        if(pAppGainCtr->gainVal > pAppGainCtr->maxSensorGain)
        {
	        *dGain = pAppGainCtr->gainVal / pAppGainCtr->maxSensorGain;
	        *aGain = pAppGainCtr->maxSensorGain;
        }
        else
        {
            *dGain = 1.0;
            *aGain = pAppGainCtr->gainVal;
        }	
        return ;
     }
     for (i = 0; i < pAppGainCtr->aGainNum; i++)
	{
        if ( FLOAT_IS_ZERO( pAppGainCtr->aGainTable[i] - pAppGainCtr->gainVal ) )
		{
			minAIndex = i;
			break;
		}
		else if (pAppGainCtr->aGainTable[i] > pAppGainCtr->gainVal)
		{
			minAIndex = MAX(0, (i - 1));
			break;
		}
		else
		{
			minAIndex = i;
		}
	}
    pAppGainCtr->aGainIndex = minAIndex;
	
	*aGain = pAppGainCtr->aGainTable[minAIndex];
	*dGain = DIV(pAppGainCtr->gainVal, pAppGainCtr->aGainTable[minAIndex]);
    return ;
}
/*******************************************************************************
* ������  : AlgGain_getBrtCoef
* ��  ��  : ����brightness���������������
* ��  ��  : ��
* ��  ��  : ��
* ����ֵ  : �������
*******************************************************************************/
static float AlgGain_getBrtCoef(void)
{
    
    float dGainBrt = 1.0;
    APP_GainControl *pAppGainCtr = \
        (APP_GainControl *)AEW_paraGetPtr(PARA_AEW_APP_GAIN_PARAMS);
    pAppGainCtr->brightness ;
    if(pAppGainCtr->brightness <= 50)
    {
        dGainBrt = pAppGainCtr->brightness / 50.0f;
    }
    else
    {
        dGainBrt = (pAppGainCtr->brightness-50.0f)*3/50.0f + 1.0f;
    }
    return dGainBrt;
}
/*******************************************************************************
* ������  : AlgGain_getBlcCoef
* ��  ��  : ����blc���������������
* ��  ��  : ��
* ��  ��  : ��
* ����ֵ  : �������
*******************************************************************************/
static float AlgGain_getBlcCoef(void)
{
    float dGainBlc = 1.0;
    APP_GainControl *pAppGainCtr = \
        (APP_GainControl *)AEW_paraGetPtr(PARA_AEW_APP_GAIN_PARAMS);

    dGainBlc = 1023.0f / (1023-pAppGainCtr->blcVal) +0.004f;
    return dGainBlc;

/*******************************************************************************
* ������  : AlgGain_getBlcCoef
* ��  ��  : ����blc���������������
* ��  ��  : ��
* ��  ��  : ��
* ����ֵ  : �������
*******************************************************************************/
}
Int32 AlgGain_Run(void)
{
    float aGain = 1.0,  dGain = 1.0;
    float brtCoef = 1.0, blcCoef = 1.0;
    Uint8 aGainIndex =0;

    APP_GainControl *pAppGainCtr = \
        (APP_GainControl *)AEW_paraGetPtr(PARA_AEW_APP_GAIN_PARAMS);
    ALG_RunModule *pAlgRunModule = \
        (ALG_RunModule *)AEW_paraGetPtr(PARA_AEW_ALG_RUN_MODULE_PARAMS);

    DRV_SenGainParam *pDrvSenGainPara = \
        (DRV_SenGainParam *)DRV_paraGetPtr(DRV_SEN_GAIN);
    DRV_IspGainParam *pDrvIspGainPara = \
        (DRV_IspGainParam *)DRV_paraGetPtr(DRV_ISP_GAIN);
    DRV_Module *pDrvRunModule = \
        (DRV_Module *)DRV_paraGetPtr(DRV_RUN_MODULE_PARAMS);
    
     if(!pAlgRunModule->ispModule[ALG_ISP_SET_GAIN])
     {
         return  OSA_SOK;
     }
     AlgGain_gainValCalc( &aGain,  &dGain);
     brtCoef = AlgGain_getBrtCoef();
     blcCoef = AlgGain_getBlcCoef();
     dGain = dGain * brtCoef * blcCoef *(pAppGainCtr->digitalShift<<1);

     if(aGain !=pDrvSenGainPara->aGain)
     {
         pDrvRunModule->drvModule[DRV_SEN_GAIN] = 1;
     }
     if(dGain !=pDrvIspGainPara->dGain)
     {
         pDrvRunModule->drvModule[DRV_ISP_GAIN] = 1;
     }
     pDrvSenGainPara->aGain = aGain;
     pDrvIspGainPara->dGain = dGain;
     return  OSA_SOK;
}
