#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "TypeDef.h"
#include "ErrorTypeDef.h"
#include "SSIM.h"
#include "BmpTypeDef.h"

static Data_Prama bmp_x,bmp_y;
static SSIM_Prama ssim;
/*******************************************************************************
* 函数名   : SSIM_getAvg
* 描  述   : 获取图像均值；每执行一次，智能获取图像中一个通道的均值
* 输  入   : 
			 pData   : 图像结构体指针
		     skipLen ：跳跃长度；取决于图像位数：8bit：1；24bit：3；
             offset  ：偏移长度；取决于图像位数和要求的通道；
             8bit数据，只有一个灰度通道：0；
             24bit数据，R G B 通道：对应偏移分辨为 0 ，1, 2
* 输  出   : 
			 avgVal ：均值结果指针
* 返回值   : ErrorInfoType，OK：成功；其他失败。
*******************************************************************************/
ErrorInfoType SSIM_getAvg(Data_Prama* pData,double* avgVal,int skipLen,int offset )
{
    uint16_t  i = 0,j=0;
    double  Sum=0;
    if( pData==NULL || avgVal==NULL )
    {
       return Err_Ptr_Null;
    }
    if( pData->w<=0 || pData->h<=0 )
    {
       return Err_Len_Zero;
    }
    
    for (i=0;i<pData->h;i++)
    {
        for (j=0;j<pData->w;j++)
        {
            Sum+=pData->p_data[(i*pData->w+j)*skipLen+offset];
        }
    }
    *avgVal = Sum/(pData->w*pData->h);
    return OK;
}
/*******************************************************************************
* 函数名   : SSIM_getVariance
* 描  述   : 获取图像方差；每执行一次，智能获取图像中一个通道的方差
* 输  入   : 
			 pData   : 图像结构体指针
		     skipLen ：跳跃长度；取决于图像位数：8bit：1；24bit：3；
             offset  ：偏移长度；取决于图像位数和要求的通道；
                       8bit数据，只有一个灰度通道：0；
                       24bit数据，R G B 通道：对应偏移分辨为 0 ，1, 2
             avgVal  : 图像均值
* 输  出   : 
			 varianceVal ：方差结果指针
* 返回值   : ErrorInfoType，OK：成功；其他失败。
*******************************************************************************/
ErrorInfoType SSIM_getVariance(Data_Prama* pData,double avgVal,double* varianceVal,int skipLen,int offset )
{
    uint16_t  i = 0,j=0;
    double  Sum=0;
    if( pData==NULL || varianceVal==NULL )
    {
       return Err_Ptr_Null;
    }
    if( pData->w<=0 || pData->h<=0 )
    {
       return Err_Len_Zero;
    }
   
    for (i=0;i<pData->h;i++)
    {
        for (j=0;j<pData->w;j++)
        {
            Sum+=(avgVal-pData->p_data[(i*pData->w+j)*skipLen+offset])*(avgVal-pData->p_data[(i*pData->w+j)*skipLen+offset]);
        }
    }
    *varianceVal = sqrt( Sum/(pData->w*pData->h-1) );
    return OK;
}
/*******************************************************************************
* 函数名   : SSIM_getCovariance
* 描  述   : 获取2副图像协方差；每执行一次，智能获取图像中一个通道的协方差
* 输  入   : 
			 pSSIM   : pSSIM结构体指针
		     skipLen ：跳跃长度；取决于图像位数：8bit：1；24bit：3；
             offset  ：偏移长度；取决于图像位数和要求的通道；
                       8bit数据，只有一个灰度通道：0；
                       24bit数据，R G B 通道：对应偏移分辨为 0 ，1, 2
             pData_x : 图像1数据结构体
             pData_y : 图像2数据结构体
* 输  出   : 
			 covarVal ：协方差结果指针
* 返回值   : ErrorInfoType，OK：成功；其他失败。
*******************************************************************************/
ErrorInfoType SSIM_getCovariance(SSIM_Prama* pSSIM,Data_Prama* pData_x,Data_Prama* pData_y,double* covarVal,int skipLen,int offset )
{
    uint16_t  i = 0,j=0;
    double  Sum=0;
    if( pSSIM==NULL || pData_x==NULL || pData_y==NULL ||covarVal==NULL )
    {
       return Err_Ptr_Null;
    }
    if( pData_x->w<=0 || pData_x->h<=0 || pData_y->w<=0 || pData_y->h<=0 )
    {
       return Err_Len_Zero;
    }
   
    for (i=0;i<pData_x->h;i++)
    {
        for (j=0;j<pData_x->w;j++)
        {
            Sum+=(pData_x->p_data[(i*pData_x->w+j)*skipLen+offset]-pSSIM->avg_x ) * (pData_y->p_data[(i*pData_y->w+j)*skipLen+offset]-pSSIM->avg_y );
        }
    }
    *covarVal = Sum/(pData_x->w*pData_x->h-1);
    return OK;
}
/*******************************************************************************
* 函数名   : SSIM_caclRes
* 描  述   : 计算SSIM结果
* 输  入   : 
			 pSSIM   : pSSIM结构体指针
* 返回值   : ErrorInfoType，OK：成功；其他失败。
*******************************************************************************/
ErrorInfoType SSIM_caclRes(SSIM_Prama* pSSIM )
{
    if( pSSIM==NULL )
    {
       return Err_Ptr_Null;
    }
    pSSIM->c1=(0.01*255)*(0.01*255);
    pSSIM->c2=(0.03*255)*(0.03*255);
    pSSIM->c3=pSSIM->c2/2;
    pSSIM->l=(2* pSSIM->avg_x* pSSIM->avg_y+ pSSIM->c1) / ( pSSIM->avg_x* pSSIM->avg_x+ pSSIM->avg_y* pSSIM->avg_y+ pSSIM->c1);
    pSSIM->c=(2* pSSIM->variance_x* pSSIM->variance_y+ pSSIM->c2) / ( pSSIM->variance_x* pSSIM->variance_x+ pSSIM->variance_y* pSSIM->variance_y+ pSSIM->c2);
    pSSIM->s=(pSSIM->covariance+pSSIM->c3) / (pSSIM->variance_x*pSSIM->variance_y+pSSIM->c3); 
    //printf("l:%lf-c:%lf-s:%lf\n",pSSIM->l,pSSIM->c,pSSIM->s);
    pSSIM->res = pSSIM->l*pSSIM->c*pSSIM->s;
    return OK;
}
/*******************************************************************************
* 函数名   : SSIM_Process
* 描  述   : SSIM处理
* 输  入   : 
			 pSSIM   : pSSIM结构体指针
		     skipLen ：跳跃长度；取决于图像位数：8bit：1；24bit：3；
             offset  ：偏移长度；取决于图像位数和要求的通道；
                       8bit数据，只有一个灰度通道：0；
                       24bit数据，R G B 通道：对应偏移分辨为 0 ，1, 2
             pData_x : 图像1数据结构体
             pData_y : 图像2数据结构体

* 返回值   : ErrorInfoType，OK：成功；其他失败。
*******************************************************************************/
ErrorInfoType SSIM_Process(SSIM_Prama* pSSIM,Data_Prama* pData_x,Data_Prama* pData_y,int skipLen,int offset )
{
    double temp=0;
    if( pSSIM==NULL || pData_x==NULL || pData_y==NULL )
    {
       printf("[func:%s-lins:%d]:ptr is null\n",__FUNCTION__,__LINE__);
       return Err_Ptr_Null;
    }
    if(SSIM_getAvg(pData_x,&temp,skipLen,offset )!=OK)
    {
         printf("[func:%s-lins:%d]:clca bmpx avg fail\n",__FUNCTION__,__LINE__);
         return  Err_CaclBmpXAvgFail;
    }
    //printf("[func:%s-lins:%d]:x avg:%lf \n",__FUNCTION__,__LINE__,temp);
    pSSIM->avg_x= temp;
    if(SSIM_getAvg(pData_y,&temp,skipLen,offset )!=OK)
    {
         printf("[func:%s-lins:%d]:clca bmpy avg fail\n",__FUNCTION__,__LINE__);
         return  Err_CaclBmpYAvgFail;
    }
    pSSIM->avg_y= temp;
    //printf("[func:%s-lins:%d]:y avg:%lf \n",__FUNCTION__,__LINE__,temp);
    if( SSIM_getVariance(pData_x,pSSIM->avg_x, &temp,skipLen,offset)!=OK)
    {
         printf("[func:%s-lins:%d]:clca bmpx Variance fail\n",__FUNCTION__,__LINE__);
         return  Err_CaclBmpXVarianceFail;
    }
    pSSIM->variance_x= temp;
    //printf("[func:%s-lins:%d]:x var:%lf \n",__FUNCTION__,__LINE__,temp);
    if( SSIM_getVariance(pData_y,pSSIM->avg_y, &temp,skipLen,offset)!=OK)
    {
         printf("[func:%s-lins:%d]:clca bmpy Variance fail\n",__FUNCTION__,__LINE__);
         return  Err_CaclBmpYVarianceFail;
    }
    pSSIM->variance_y= temp;
    //printf("[func:%s-lins:%d]:y var:%lf \n",__FUNCTION__,__LINE__,temp);
    if(SSIM_getCovariance(pSSIM,pData_x,pData_y, &temp,skipLen,offset)!=OK)
    {
         printf("[func:%s-lins:%d]:clca bmpy Variance fail\n",__FUNCTION__,__LINE__);
         return  Err_CaclBmpYVarianceFail;
    }
    pSSIM->covariance= temp;
    //printf("[func:%s-lins:%d]:covar:%lf \n",__FUNCTION__,__LINE__,pSSIM->covariance);
    if(SSIM_caclRes(pSSIM)!=OK)
    {
        printf("[func:%s-lins:%d]:clca ssim res fail\n",__FUNCTION__,__LINE__);
        return  Err_CaclSSImResFail;
    }
    return OK;
}

/*******************************************************************************
* 函数名   : getSsimRes
* 描  述   : SSIM处理
* 输  入   : 
			 pBmp_x   : 图像1BMP指针
		     pBmp_y ：图像1BMP指针
* 输  出   : 
			 res ：SSIM结果
* 返回值   : ErrorInfoType，OK：成功；其他失败。
*******************************************************************************/
ErrorInfoType getSsimRes(Bmp* pBmp_x,Bmp* pBmp_y,SSIM_FinalRes* res )
{
    int i=0;
    double temp=0;
    if( pBmp_x==NULL || pBmp_y==NULL ||res==NULL )
    {
       return Err_Ptr_Null;
    }
    if( (pBmp_x->mBitMapInfo.biBitCount!=pBmp_y->mBitMapInfo.biBitCount) ||
        (pBmp_x->mBitMapInfo.biWidth!=pBmp_y->mBitMapInfo.biWidth) ||
        (pBmp_x->mBitMapInfo.biHeight!=pBmp_y->mBitMapInfo.biHeight)
      )
    {
        return Err_ImxImy_InfoNotEqual;
    }
    
    memset(&bmp_x,0,sizeof(Data_Prama));
    memset(&bmp_y,0,sizeof(Data_Prama));
    
   
    bmp_x.w   = pBmp_x->mBitMapInfo.biWidth;
    bmp_x.h   = pBmp_x->mBitMapInfo.biHeight;
    bmp_x.p_data = (unsigned char*)pBmp_x->pImageData;

    bmp_y.w   = pBmp_y->mBitMapInfo.biWidth;
    bmp_y.h   = pBmp_y->mBitMapInfo.biHeight;
    bmp_y.p_data = (unsigned char*)pBmp_y->pImageData;

    if(pBmp_x->mBitMapInfo.biBitCount==8)
    {
        memset(&ssim,0, sizeof(SSIM_Prama));
        if(SSIM_Process(&ssim,&bmp_x,&bmp_y,1,0)!=OK)
        {
             printf("[func:%s-lins:%d]:clca ssim res fail\n",__FUNCTION__,__LINE__);
             return  Err_CaclSSImResFail;
        }
        res->ssimRes[0]=ssim.res;
        res->count=1;
    }
    else if(pBmp_x->mBitMapInfo.biBitCount==24)
    {
        for(i=0;i<pBmp_x->mBitMapInfo.biBitCount/8;i++)
        {
            memset(&ssim,0, sizeof(SSIM_Prama));
            if(SSIM_Process(&ssim,&bmp_x,&bmp_y,3,i)!=OK)
            {
                 printf("[func:%s-lins:%d]:clca ssim res fail\n",__FUNCTION__,__LINE__);
                 return  Err_CaclSSImResFail;
            }
           res->ssimRes[i]=ssim.res;
           res->count=i+1;
        }
        
    }
    else
    {
        return Err_ImBitErr;
    }
    return OK;
}

