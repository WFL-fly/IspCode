/*******************************************************************************
* Bmp.c
* Copyright (C) 2011-2018 ZheJiang Dahua Technology CO.,LTD.
* Author : wang fulai <wang_fulai@dahuatech.com>
* Version: V1.0.0  2019-1-31 Create
* Desc: ����BMPͼ���ļ�
* Modification:
*    Date    :
*    Revision:
*    Author  :
*    Contents:
*******************************************************************************/
/****************************************************************
                            ͷ�ļ���
*****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BmpTypeDef.h"
#include "TypeDef.h"
/****************************************************************
                            ����������
*****************************************************************/

/*******************************************************************************
* ������   : readBmpInfoData
* ��  ��   : ��ȡͼ��������
* ��  ��   : 
			 fp   : bmp�ļ�ָ��
		     pBmp ��Bmp�ṹ�����ָ��
* ��  ��   : 
			 pBmp ��Bmp�ṹ�����ָ�룬���Bmpͼ����Ϣ��������ͼ������
* ����ֵ   : ��������0���ɹ���1:ʧ�ܡ�
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
* ������   : readBmpInfoData
* ��  ��   : ��ȡͼ��������
* ��  ��   : 
			 fp   : bmp�ļ�ָ��
		     pBmp ��Bmp�ṹ�����ָ��
* ��  ��   : 
			 pBmp ��Bmp�ṹ�����ָ�룬���Bmpͼ����Ϣ��������ͼ������
* ����ֵ   : ��������0���ɹ���1:ʧ�ܡ�
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
* ������   : readBmp
* ��  ��   : ��ȡͼ��������
* ��  ��   : 
			 file_path ���ļ�·��������
		     pBmp	   ��Bmp�ṹ�����ָ��
* ��  ��   : 
			 pBmp	   ��Bmp�ṹ�����ָ�룬���Bmpͼ����Ϣ������
* ����ֵ   : ��������0���ɹ���1:ʧ�ܡ�
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
* ������   : saveBmp
* ��  ��   : ��������λbmp�ļ�
* ��  ��   : 
			 file_path ���ļ�·��������
			 pBmp�����ݶ���ָ��
* ��  ��   : ��
* ����ֵ   : ��������0���ɹ���1:ʧ�ܡ�
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
* ������   : initBmp
* ��  ��   : ��ʼ��bmp����
* ��  ��   : 
			 pBmp��bmp����ָ��
* ��  ��   : ��
* ����ֵ   : ��������0���ɹ���1:ʧ�ܡ�
*******************************************************************************/
int initBmp(Bmp* pBmp)
{
	memset( pBmp , 0 , sizeof(Bmp) );
	return OSA_SOK;
}

/*******************************************************************************
* ������   : disposeBmp
* ��  ��   : �ͷ�bmp����ͼ�����ݣ�ֻ�ͷ����ݣ����ͷ�ͼ����Ϣ
* ��  ��   : 
			 pBmp ��bmp����ָ��
* ��  ��   : ��
* ����ֵ   : ��������0���ɹ���1:ʧ�ܡ�
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