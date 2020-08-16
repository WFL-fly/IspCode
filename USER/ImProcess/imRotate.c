#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "imRotate.h"
tagResStatus imRotate(tagImParam* pIm,tagRotateParam* rotateParam )
{
    int i=0,j=0;
    int imW=0,imH=0;
    int imByteSize =0;
    unsigned char* pTempBuf = NULL;
    if(pIm==NULL)
    {
        return ParamErr;
    }
    if(rotateParam==NULL)
    {
        return ParamErr;
    }
    if( rotateParam->rotateDir !=CLOCK_WISE &&  rotateParam->rotateDir !=ANTI_CLOCK_WISE )
    {
        return ParamErr;
    }
    if( rotateParam->rotateAngle !=ANGLE_90 && rotateParam->rotateAngle !=ANGLE_180  && rotateParam->rotateAngle !=ANGLE_270 )
    {
        return ParamErr;
    }
    imByteSize = pIm->imWidth * pIm->imHeight;
    pTempBuf = (unsigned char*) malloc(imByteSize);
    if(pTempBuf == NULL)
    {
        return MemApplyErr;
    }
    switch(rotateParam->rotateDir)
    {
        case CLOCK_WISE :
            switch(rotateParam->rotateAngle)
            {
                case ANGLE_90 :
                    imW = pIm->imHeight;
                    imH = pIm->imWidth;
                    for(i=0;i<imH;i++)
                    {
                        for(j=0;j<imW;j++)
                        {
                           pTempBuf[i*imW+j] = pIm->pImBuf[(pIm->imHeight-j-1)*pIm->imWidth+i];
                        }
                    }
                    break;
                case ANGLE_180 :
                    imW = pIm->imWidth;
                    imH = pIm->imHeight;
                    for(i=0;i<imH;i++)
                    {
                        for(j=0;j<imW;j++)
                        {
                            pTempBuf[i*imW+j] = pIm->pImBuf[(pIm->imHeight-i-1)*pIm->imWidth+(pIm->imWidth-j-1)];
                        }
                    }
                    break;
                case ANGLE_270 :
                    imW = pIm->imHeight;
                    imH = pIm->imWidth;
                    for(i=0;i<imH;i++)
                    {
                        for(j=0;j<imW;j++)
                        {
                           
                           pTempBuf[i*imW+j] = pIm->pImBuf[j*pIm->imWidth+(pIm->imWidth-i-1)];
                        }
                    }
                    break;
                default :
                   free(pTempBuf);
                   return  ParamErr;
            }
            break;
        case ANTI_CLOCK_WISE :
             switch(rotateParam->rotateAngle)
            {
                case ANGLE_90 :
                    imW = pIm->imHeight;
                    imH = pIm->imWidth;
                    for(i=0;i<imH;i++)
                    {
                        for(j=0;j<imW;j++)
                        {
                            pTempBuf[i*imW+j] = pIm->pImBuf[j*pIm->imWidth+(pIm->imWidth-i-1)];
                        }
                    }
                    break;
                case ANGLE_180 :
                    imW = pIm->imWidth;
                    imH = pIm->imHeight;
                    for(i=0;i<imH;i++)
                    {
                        for(j=0;j<imW;j++)
                        {
                            pTempBuf[i*imW+j] = pIm->pImBuf[(pIm->imHeight-i-1)*pIm->imWidth+(pIm->imWidth-j-1)];
                        }
                    }
                    break;
                case ANGLE_270 :
                    imW = pIm->imHeight;
                    imH = pIm->imWidth;
                    for(i=0;i<imH;i++)
                    {
                        for(j=0;j<imW;j++)
                        {
                           pTempBuf[i*imW+j] = pIm->pImBuf[(pIm->imHeight-j-1)*pIm->imWidth+i];
                        }
                    }
                    break;
                default :
                   free(pTempBuf);
                   return  ParamErr;
            }
            break;

        default :
            free(pTempBuf);
            
            return  ParamErr;

    }
    memcpy(pIm->pImBuf,pTempBuf,imByteSize);
    pIm->imHeight = imH;
    pIm->imWidth  = imW;
    free(pTempBuf);
    return OK;

}
