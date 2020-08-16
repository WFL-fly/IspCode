#include "aew.h"
/*******************************************************************************
* 函数名  : AlgGain_getAGainIndex
* 描  述  : 根据当前界面设置增益值，获取对应模拟增益档位
* 输  入  : 无
* 输  出  : 无。
* 返回值  : 模拟增益档位
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
* 函数名  : APP_gainCalc
* 描  述  : 根据界面增益值计算模拟增益和数字增益
* 输  入  : 无
* 输  出  : aGain：模拟增益;dGain：数字增益。
* 返回值  : 无
*******************************************************************************/
void  AlgGain_gainValCalc(float *aGain, float *dGain)
{
     int i = 0;
	 Uint8 minAIndex = 0;
     APP_GainControl *pAppGainCtr = \
        (APP_GainControl *)AEW_paraGetPtr(PARA_AEW_APP_GAIN_PARAMS);
     if(pAppGainCtr->aGainNum ==0)
     {
         /**连续的模拟增益***/
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
* 函数名  : AlgGain_getBrtCoef
* 描  述  : 根据brightness计算增益折算比率
* 输  入  : 无
* 输  出  : 无
* 返回值  : 折算比率
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
* 函数名  : AlgGain_getBlcCoef
* 描  述  : 根据blc计算增益折算比率
* 输  入  : 无
* 输  出  : 无
* 返回值  : 折算比率
*******************************************************************************/
static float AlgGain_getBlcCoef(void)
{
    float dGainBlc = 1.0;
    APP_GainControl *pAppGainCtr = \
        (APP_GainControl *)AEW_paraGetPtr(PARA_AEW_APP_GAIN_PARAMS);

    dGainBlc = 1023.0f / (1023-pAppGainCtr->blcVal) +0.004f;
    return dGainBlc;

/*******************************************************************************
* 函数名  : AlgGain_getBlcCoef
* 描  述  : 根据blc计算增益折算比率
* 输  入  : 无
* 输  出  : 无
* 返回值  : 折算比率
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
