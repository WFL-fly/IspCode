/*******************************************************************************
* app_gain.c
*
* Copyright (C) 2019-2021 ZheJiang Dahua Technology CO.,LTD.
*
* Author : Yan Hongsheng  <yan_hongsheng@dahuatech.com>
* Version: V1.0.0  2019-9-1 Create
*
* Desc: ISP能力集管理模块
*
* Modification:
*    Date    :
*    Revision:
*    Author  :
*    Contents:
*******************************************************************************/
/* ========================================================================== */
/*                             头文件区                                       */
/* ========================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aew_typeDef.h"
#include "drv_param.h"
#include "aew_macro.h"
#include "DrvIsp_Dgc.h"
/* ========================================================================== */
/*                            全局变量定义区                                  */
/* ========================================================================== */

/* ========================================================================== */
/*                          函数声明区                                        */
/* ========================================================================== */
/* ========================================================================== */
/*                          函数定义区                                        */
/* ========================================================================== */

void DrvIspGain_paraDefault(void)
{
    DRV_SenGainParam *pDrvSenGainPara = \
        (DRV_SenGainParam *)DRV_paraGetPtr(DRV_SEN_GAIN);
    DRV_IspGainParam *pDrvIspGainPara = \
        (DRV_IspGainParam *)DRV_paraGetPtr(DRV_ISP_GAIN);
    pDrvSenGainPara->aGain = 1.0;
    pDrvIspGainPara->dGain = 1.0;
}
void DrvIspGain_Run(void)
{
     DRV_SenGainParam *pDrvSenGainPara = \
        (DRV_SenGainParam *)DRV_paraGetPtr(DRV_SEN_GAIN);
    DRV_IspGainParam *pDrvIspGainPara = \
        (DRV_IspGainParam *)DRV_paraGetPtr(DRV_ISP_GAIN);
    DRV_Module *pDrvRunModule = \
        (DRV_Module *)DRV_paraGetPtr(DRV_RUN_MODULE_PARAMS);
    float dGain = 0;

     if(pDrvRunModule->drvModule[DRV_SEN_GAIN])
     {
         //DrvSenGain_setVal(pDrvSenGainPara->aGain);
     }
     if(pDrvRunModule->drvModule[DRV_ISP_GAIN])
     {
         dGain = pDrvIspGainPara->dGain;
         DrvIspDgc_setVal( dGain,  dGain,  dGain,  dGain);
     }
     pDrvRunModule->drvModule[DRV_SEN_GAIN] = 0;
     pDrvRunModule->drvModule[DRV_ISP_GAIN] = 0;
    //todo set isp dGain
}
/*
void DrvIspSen_Run(void)
{
    float dGain = 0;
    DRV_GainParam* pDrvIspGainPara = \
        (DRV_GainParam*)DRV_paraGetPtr(DRV_GAIN_PARAMS );
    DRV_RunMode *pDrvRunModePara = \
        (DRV_RunMode *)DRV_paraGetPtr(DRV_RUN_MODE_PARAMS);
    
     if(!pDrvRunModePara->ispDrvRunMode[DRV_RUN_MODE_PARAMS])
     {
         return  ;
     }
     dGain = pDrvIspGainPara->dGain;
     Dgc_setVal( dGain,  dGain,  dGain,  dGain);
     
     pDrvRunModePara->ispDrvRunMode[DRV_ISP_SET_GAIN] = 0;
    //todo set isp dGain
}
*/