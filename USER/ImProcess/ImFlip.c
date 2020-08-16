#include "BmpTypeDef.h"
#include "TypeDef.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define R 0
#define G 1
#define B 2

int  ImFlipY_8(int w,int h,uint8_t* src,uint8_t* dst)
{
   int i=0,j=0;
   if( src==NULL ||  dst==NULL)
   {
       printf("[func:%s-line:%d]-[error:pBmp ptr is null!]\r\n",__FUNCTION__,__LINE__);
       return -1;
   }
   if(w<=0||h<=0)
   {
        printf("[func:%s-line:%d]-[error:malloc fail!]\r\n",__FUNCTION__,__LINE__);
        return -1;
   }
   for(j=0;j<w;j++)
   {
        for(i=0;i<h;i++)
        {
            dst[i*w+j] = src[(h-i-1)*w+j];
        }
   }
   return 0;
}
int  ImFlipY_24(int w,int h,uint8_t* src,uint8_t* dst)
{
   int i=0,j=0;
   if( src==NULL ||  dst==NULL)
   {
       printf("[func:%s-line:%d]-[error:pBmp ptr is null!]\r\n",__FUNCTION__,__LINE__);
       return -1;
   }
   if(w<=0||h<=0)
   {
        printf("[func:%s-line:%d]-[error:malloc fail!]\r\n",__FUNCTION__,__LINE__);
        return -1;
   }
   for(j=0;j<w;j++)
   {
        for(i=0;i<h;i++)
        {
            dst[(i*w+j)*3+R] = src[((h-i-1)*w+j)*3+R];
            dst[(i*w+j)*3+G] = src[((h-i-1)*w+j)*3+G];
            dst[(i*w+j)*3+B] = src[((h-i-1)*w+j)*3+B];
        }
   }
   return 0;
}
int  ImFlipX_8(int w,int h,uint8_t* src,uint8_t* dst)
{
   int i=0,j=0;
   if( src==NULL ||  dst==NULL)
   {
       printf("[func:%s-line:%d]-[error:pBmp ptr is null!]\r\n",__FUNCTION__,__LINE__);
       return -1;
   }
   if(w<=0||h<=0)
   {
        printf("[func:%s-line:%d]-[error:malloc fail!]\r\n",__FUNCTION__,__LINE__);
        return -1;
   }
   for(i=0;i<h;i++)
   {
        for(j=0;j<w;j++)
        {
            dst[i*w+j] = src[i*w+(w-j-1)];
        }
   }
   return 0;
}
int  ImFlipX_24(int w,int h,uint8_t* src,uint8_t* dst)
{
   int i=0,j=0;
   if( src==NULL ||  dst==NULL)
   {
       printf("[func:%s-line:%d]-[error:pBmp ptr is null!]\r\n",__FUNCTION__,__LINE__);
       return -1;
   }
   if(w<=0||h<=0)
   {
        printf("[func:%s-line:%d]-[error:malloc fail!]\r\n",__FUNCTION__,__LINE__);
        return -1;
   }
   for(j=0;j<w;j++)
   {
        for(i=0;i<h;i++)
        {
            dst[(i*w+j)*3+R] = src[((h-i-1)*w+j)*3+R];
            dst[(i*w+j)*3+G] = src[((h-i-1)*w+j)*3+G];
            dst[(i*w+j)*3+B] = src[((h-i-1)*w+j)*3+B];
        }
   }
   for(i=0;i<h;i++)
   {
        for(j=0;j<w;j++)
        {
            dst[(i*w+j)*3+R] = src[(i*w+(w-j-1)*3+R)];
            dst[(i*w+j)*3+G] = src[(i*w+(w-j-1)*3+G)];
            dst[(i*w+j)*3+B] = src[(i*w+(w-j-1)*3+B)];
        }
   }
   return 0;
}

Bmp*  ImFlipX(Bmp* pBmp)
{
   int res=0;
   int i=0,j=0;
   Bmp* pBmpFlipXRes = NULL;
   if( pBmp==NULL )
   {
       printf("[func:%s-line:%d]-[error:pBmp ptr is null!]\r\n",__FUNCTION__,__LINE__);
       return NULL;
   }
   pBmpFlipXRes = (Bmp*)malloc(sizeof(Bmp));
   if(pBmpFlipXRes==NULL)
   {
        printf("[func:%s-line:%d]-[error:malloc fail!]\r\n",__FUNCTION__,__LINE__);
        return NULL;
   }
   memset(pBmpFlipXRes,0,sizeof(Bmp));
   memcpy(pBmpFlipXRes,pBmp,sizeof(Bmp));
   pBmpFlipXRes->pImageData=NULL;
   pBmpFlipXRes->pImageData=(uint8_t*)malloc(pBmp->mBitMapInfo.biSizeImage);
   if(pBmpFlipXRes->pImageData==NULL)
   {
        printf("[func:%s-line:%d]-[error:malloc fail!]\r\n",__FUNCTION__,__LINE__);
        if(pBmpFlipXRes!=NULL)
        {
            free(pBmpFlipXRes);
        }
        return NULL;
   }
   
   if(pBmp->mBitMapInfo.biBitCount==8)
    {
        if(ImFlipX_8(pBmp->mBitMapInfo.biWidth,pBmp->mBitMapInfo.biHeight,pBmp->pImageData,pBmpFlipXRes->pImageData)==0)
        {
            res=1;
        }
    }
    else if(pBmp->mBitMapInfo.biBitCount==24)
    {

       if(ImFlipX_24(pBmp->mBitMapInfo.biWidth,pBmp->mBitMapInfo.biHeight,pBmp->pImageData,pBmpFlipXRes->pImageData)==0)
        {
            res=1;
        }
    }
    else
    {
        printf("[func:%s-line:%d]-[error:bmp bit error!]\r\n",__FUNCTION__,__LINE__);
        res =0;
    }
    if(res)
    {
        return pBmpFlipXRes;
    }
    else
    {
        if(pBmpFlipXRes->pImageData!=NULL)
        {
            free(pBmpFlipXRes->pImageData);
        }
        if(pBmpFlipXRes!=NULL)
        {
            free(pBmpFlipXRes);
        }
        return NULL;
    }
}

Bmp*  ImFlipY(Bmp* pBmp)
{
   int res=0;
   int i=0,j=0;
   Bmp* pBmpFlipYRes = NULL;
   if( pBmp==NULL )
   {
       printf("[func:%s-line:%d]-[error:pBmp ptr is null!]\r\n",__FUNCTION__,__LINE__);
       return NULL;
   }
   pBmpFlipYRes = (Bmp*)malloc(sizeof(Bmp));
   if(pBmpFlipYRes==NULL)
   {
        printf("[func:%s-line:%d]-[error:malloc fail!]\r\n",__FUNCTION__,__LINE__);
        return NULL;
   }
   memset(pBmpFlipYRes,0,sizeof(Bmp));
   memcpy(pBmpFlipYRes,pBmp,sizeof(Bmp));
   pBmpFlipYRes->pImageData=NULL;
   pBmpFlipYRes->pImageData=(uint8_t*)malloc(pBmp->mBitMapInfo.biSizeImage);
   if(pBmpFlipYRes->pImageData==NULL)
   {
        printf("[func:%s-line:%d]-[error:malloc fail!]\r\n",__FUNCTION__,__LINE__);
        if(pBmpFlipYRes!=NULL)
        {
            free(pBmpFlipYRes);
        }
        return NULL;
   }
   
   if(pBmp->mBitMapInfo.biBitCount==8)
    {
        if(ImFlipY_8(pBmp->mBitMapInfo.biWidth,pBmp->mBitMapInfo.biHeight,pBmp->pImageData,pBmpFlipYRes->pImageData)==0)
        {
            res=1;
        }
    }
    else if(pBmp->mBitMapInfo.biBitCount==24)
    {

       if(ImFlipY_24(pBmp->mBitMapInfo.biWidth,pBmp->mBitMapInfo.biHeight,pBmp->pImageData,pBmpFlipYRes->pImageData)==0)
        {
            res=1;
        }
    }
    else
    {
        printf("[func:%s-line:%d]-[error:bmp bit error!]\r\n",__FUNCTION__,__LINE__);
        res =0;
    }
    if(res)
    {
        return pBmpFlipYRes;
    }
    else
    {
        if(pBmpFlipYRes->pImageData!=NULL)
        {
            free(pBmpFlipYRes->pImageData);
        }
        if(pBmpFlipYRes!=NULL)
        {
            free(pBmpFlipYRes);
        }
        return NULL;
    }
   
}


