/*******************************************************************************
* image_file.c
* Copyright (C) 2011-2018 ZheJiang Dahua Technology CO.,LTD.
* Author : wang fulai <wang_fulai@dahuatech.com>
* Version: V1.0.0  2018-12-28 Create
* Desc: 操作图像数据文件，包括裸数据和图数据
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
#include "file.h"

/****************************************************************
                            函数定义区
*****************************************************************/
/*******************************************************************************
* 函数名   : readBinaryFileData
* 描  述   : 读取图像裸数据
* 输  入   : 
			 file_path ：文件路径和名称
		     buf	   ：存储数据的缓存区
			 size	   ：读取数据的大小(单位字节)
* 输  出   : 无
* 返回值   : 计算结果，0：成功；1:失败。
*******************************************************************************/
uint64_t readBinaryFileData(char *file_path,unsigned char *buf,uint64_t size)
{
	uint64_t file_size=0;
	FILE *fp=NULL;
	if(file_path==NULL||buf==NULL)
	{
		return OSA_EFAIL;
	}
    
	printf("file name:%s\r\n",file_path);
	fp=fopen(file_path,"rb");
	if(fp==NULL)
	{
		return OSA_EFAIL;
	}

	fseek(fp,0,SEEK_END);
	file_size=ftell(fp);
	fseek(fp,0,SEEK_SET);
	if(file_size<size)
	{
		size=file_size;
		printf("file size:%d\r\n",size);
	}
    if(size == 0)
    {
        size = file_size;
    }
	fread(buf,1,size,fp);
	fclose(fp);
	return size;
}
/*******************************************************************************
* 函数名   : writeBinaryFileData
* 描  述   : 写图像裸数据到文件
* 输  入   : 
			 file_path ：文件路径和名称
		     buf	   ：存储数据的缓存区
			 size	   ：写数据的大小(单位字节)
* 输  出   : 无
* 返回值   : 计算结果，0：成功；1:失败。
*******************************************************************************/
uint64_t writeBinaryFileData(char *file_path,unsigned char *buf,uint64_t size)
{
	FILE *fp=NULL;
	if(file_path==NULL||buf==NULL||size<=0)
	{
		return OSA_EFAIL;
	}
	fp=fopen(file_path,"wb");
	if(fp==NULL)
	{
		return OSA_EFAIL;
	}
	fseek(fp,0,SEEK_END);
	fwrite(buf,1,size,fp);
	fclose(fp);
	return size;
}



