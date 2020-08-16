/******************************************************************************** aew_param.h** Copyright (C) 2019-2021 ZheJiang Dahua Technology CO.,LTD.** Author : Yan Hongsheng  <yan_hongsheng@dahuatech.com>* Version: V1.0.0  2019-9-1 Create** Desc: ISP宏定义管理模块** Modification:*    Date    :*    Revision:*    Author  :*    Contents:*******************************************************************************/#ifndef _DRV_MAIN_H_#define _DRV_MAIN_H_/* ========================================================================== *//*                             头文件区                                       *//* ========================================================================== */#ifdef __cplusplusextern "C" {#endif/* ========================================================================== *//*                           宏和类型定义区                                   *//* ========================================================================== *//* ========================================================================== *//*                          数据结构定义区                                    *//* ========================================================================== *//* ========================================================================== *//*                          函数声明区                                        *//******************************************************************************** 函数名  : DRV_IspInit* 描  述  : ISP驱动初始化,用于驱动参数初始配置* 输  入  : 无* 输  出  : 无* 返回值  : 无*******************************************************************************/Int32 DRV_IspInit(void);/******************************************************************************** 函数名  : DRV_IspRun* 描  述  : 运行各ISP驱动模块* 输  入  : 无* 输  出  : 无* 返回值  : 无*******************************************************************************/Int32 DRV_IspRun(void);#ifdef __cplusplus}#endif#endif