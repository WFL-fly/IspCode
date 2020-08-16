/*******************************************************************************
* Bmp.c
* Copyright (C) 2011-2018 ZheJiang Dahua Technology CO.,LTD.
* Author : wang fulai <wang_fulai@dahuatech.com>
* Version: V1.0.0  2019-1-31 Create
* Desc: 操作BMP图像文件
* Modification:
*    Date    :
*    Revision:
*    Author  :
*    Contents:
*******************************************************************************/
/****************************************************************
                            头文件区
*****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BmpTypeDef.h"
#include "TypeDef.h"
/****************************************************************
                            函数定义区
*****************************************************************/

/*******************************************************************************
* 函数名   : readBmpInfoData
* 描  述   : 读取图像裸数据
* 输  入   : 
			 fp   : bmp文件指针
		     pBmp ：Bmp结构体对象指针
* 输  出   : 
			 pBmp ：Bmp结构体对象指针，输出Bmp图像信息，不包含图像数据
* 返回值   : 计算结果，0：成功；1:失败。
*******************************************************************************/
uint64_t readBmpInfoData(FILE *fp,Bmp* pBmp)
{
	uint64_t file_size=0;
	size_t   read_size=0;
	uint64_t colorPaletteNum=0;
	unsigned char buf[50];
	if( (fp==NULL)  || (pBmp==NULL) )
	{
		return OSA_EFAIL;
	}
	
	fseek(fp,0,SEEK_END);
	file_size=ftell(fp);
	fseek(fp,0,SEEK_SET);
	read_size += sizeof(pBmp->mBmpFileHeader);
	read_size += sizeof(pBmp->mBitMapInfo);
	if( file_size < read_size )
	{
		printf("bmp format error!\r\n");
		return OSA_EFAIL;
	}
	fseek(fp,0,SEEK_SET);
	read_size += fread( buf , 1 , 14 , fp);
	pBmp->mBmpFileHeader.bfType[0]=buf[0];
	pBmp->mBmpFileHeader.bfType[1]=buf[1];
	pBmp->mBmpFileHeader.bfSize=*(unsigned int*)(&buf[2]);
	pBmp->mBmpFileHeader.bfReserved1=0;
	pBmp->mBmpFileHeader.bfReserved2=0;
	pBmp->mBmpFileHeader.bfOffBits=*(unsigned int*)(&buf[10]);
	fseek(fp,14,SEEK_SET);
	read_size += fread( &pBmp->mBitMapInfo , 1 , sizeof(pBmp->mBitMapInfo) , fp);
	
	switch( pBmp->mBitMapInfo.biBitCount )
	{
		case 1:
			colorPaletteNum = 2;
			break;
		case 4:
			colorPaletteNum = 16;
			break;
		case 8:
			colorPaletteNum = 256;
			break;
		default:
			break;
	}
	if( colorPaletteNum > 0 )
	{
		fseek(fp,54,SEEK_SET);
		read_size += fread( pBmp->mColorPalette , 1 , sizeof(pBmp->mColorPalette[0])*colorPaletteNum , fp);
	}
	fseek(fp,0,SEEK_SET);
	return read_size;
}
/*******************************************************************************
* 函数名   : readBmpInfoData
* 描  述   : 读取图像裸数据
* 输  入   : 
			 fp   : bmp文件指针
		     pBmp ：Bmp结构体对象指针
* 输  出   : 
			 pBmp ：Bmp结构体对象指针，输出Bmp图像信息，不包含图像数据
* 返回值   : 计算结果，0：成功；1:失败。
*******************************************************************************/
uint64_t readBmpImageData( FILE *fp , Bmp* pBmp)
{
	uint64_t dataStartIndex=0;
	uint64_t dataEndIndex=0;
	size_t   read_size=0;

	if( (fp==NULL)  || (pBmp==NULL) )
	{
		return OSA_EFAIL;
	}
	
	fseek(fp,pBmp->mBmpFileHeader.bfOffBits,SEEK_SET);
	dataStartIndex=ftell(fp);
	fseek(fp,0,SEEK_END);
	dataEndIndex=ftell(fp);
	fseek(fp,pBmp->mBmpFileHeader.bfOffBits,SEEK_SET);

	read_size = pBmp->mBitMapInfo.biSizeImage;
	if( dataEndIndex-dataStartIndex < read_size )
	{
		printf("bmp data lost!\r\n");
		return OSA_EFAIL;
	}
	read_size = 0;
	read_size += fread( pBmp->pImageData , 1 , pBmp->mBitMapInfo.biSizeImage , fp);
    if(read_size!=(dataEndIndex-dataStartIndex))
    {
        printf("read bmp data Fail!\r\n");
		return OSA_EFAIL;
    }
	fseek(fp,0,SEEK_SET);
	return read_size;
}
/*******************************************************************************
* 函数名   : readBmp
* 描  述   : 读取图像裸数据
* 输  入   : 
			 file_path ：文件路径和名称
		     pBmp	   ：Bmp结构体对象指针
* 输  出   : 
			 pBmp	   ：Bmp结构体对象指针，输出Bmp图像信息和数据
* 返回值   : 计算结果，0：成功；1:失败。
*******************************************************************************/
int readBmp( char *file_path , Bmp* pBmp)
{
	uint64_t res = OSA_EFAIL;
	FILE	 *fp = NULL;
	if( (file_path==NULL)  || (pBmp==NULL) )
	{
		printf("[func:%s-line:%d]-[error:file path cannot empat!]\r\n",__FUNCTION__,__LINE__);
		return OSA_EFAIL;
	}
	fp = fopen(file_path,"rb");
	if(fp==NULL)
	{
		printf("[func:%s-line:%d]-[error:open bmp file fail!]\r\n",__FUNCTION__,__LINE__);
		return OSA_EFAIL;
	}
	res = readBmpInfoData(fp, pBmp);
	if(res==OSA_EFAIL)
	{
		return OSA_EFAIL;
	}
	if(pBmp->pImageData==NULL)
	{
		pBmp->pImageData=(unsigned char*)malloc(pBmp->mBitMapInfo.biSizeImage);
	}
	res = readBmpImageData( fp , pBmp);
	if(res==OSA_EFAIL)
	{
		return OSA_EFAIL;
	}
	return OSA_SOK;
}
/*******************************************************************************
* 函数名   : saveBmp
* 描  述   : 保存数据位bmp文件
* 输  入   : 
			 file_path ：文件路径和名称
			 pBmp：数据对象指针
* 输  出   : 无
* 返回值   : 计算结果，0：成功；1:失败。
*******************************************************************************/
int saveBmp( char *file_path , Bmp* pBmp)
{
	uint64_t res = OSA_EFAIL;
	FILE *fp = NULL;
	int colorPaletteNum=0;
	if( (file_path==NULL)  || (pBmp==NULL) )
	{
		return OSA_EFAIL;
	}
	fp = fopen(file_path,"wb");
	if(fp==NULL)
	{
		return OSA_EFAIL;
	}

	fwrite(pBmp->mBmpFileHeader.bfType,1 ,2 ,fp);
	fwrite(&pBmp->mBmpFileHeader.bfSize,1 , sizeof(pBmp->mBmpFileHeader.bfSize) , fp );
	fwrite(&pBmp->mBmpFileHeader.bfReserved1,1 , sizeof(pBmp->mBmpFileHeader.bfReserved1) , fp );
	fwrite(&pBmp->mBmpFileHeader.bfReserved2,1 , sizeof(pBmp->mBmpFileHeader.bfReserved2) , fp );
	fwrite(&pBmp->mBmpFileHeader.bfOffBits,1 , sizeof(pBmp->mBmpFileHeader.bfOffBits) , fp );
	
	fwrite(&pBmp->mBitMapInfo,1 , sizeof(pBmp->mBitMapInfo) , fp );

	switch( pBmp->mBitMapInfo.biBitCount )
	{
		case 1:
			colorPaletteNum = 2;
			break;
		case 4:
			colorPaletteNum = 16;
			break;
		case 8:
			colorPaletteNum = 256;
			break;
		default:
			break;
	}
	if( colorPaletteNum > 0 )
	{
		fwrite( pBmp->mColorPalette , 1 , sizeof(pBmp->mColorPalette[0])*colorPaletteNum , fp);
	}
	fwrite(pBmp->pImageData,1 , pBmp->mBitMapInfo.biSizeImage , fp );
	fclose(fp);
	return OSA_SOK;
}

/*******************************************************************************
* 函数名   : initBmp
* 描  述   : 初始化bmp对象
* 输  入   : 
			 pBmp：bmp对象指针
* 输  出   : 无
* 返回值   : 计算结果，0：成功；1:失败。
*******************************************************************************/
int initBmp(Bmp* pBmp)
{
	memset( pBmp , 0 , sizeof(Bmp) );
	return OSA_SOK;
}

/*******************************************************************************
* 函数名   : disposeBmp
* 描  述   : 释放bmp对象图像数据，只释放数据，不释放图像信息
* 输  入   : 
			 pBmp ：bmp对象指针
* 输  出   : 无
* 返回值   : 计算结果，0：成功；1:失败。
*******************************************************************************/
int disposeBmp(Bmp* pBmp)
{
	if(pBmp->pImageData!=NULL)
	{
		free(pBmp->pImageData);
		pBmp->pImageData=NULL;
	}
	return OSA_SOK;
}