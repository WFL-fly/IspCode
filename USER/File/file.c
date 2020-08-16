/*******************************************************************************
* image_file.c
* Copyright (C) 2011-2018 ZheJiang Dahua Technology CO.,LTD.
* Author : wang fulai <wang_fulai@dahuatech.com>
* Version: V1.0.0  2018-12-28 Create
* Desc: ����ͼ�������ļ������������ݺ�ͼ����
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
#include "file.h"

/****************************************************************
                            ����������
*****************************************************************/
/*******************************************************************************
* ������   : readBinaryFileData
* ��  ��   : ��ȡͼ��������
* ��  ��   : 
			 file_path ���ļ�·��������
		     buf	   ���洢���ݵĻ�����
			 size	   ����ȡ���ݵĴ�С(��λ�ֽ�)
* ��  ��   : ��
* ����ֵ   : ��������0���ɹ���1:ʧ�ܡ�
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
* ������   : writeBinaryFileData
* ��  ��   : дͼ�������ݵ��ļ�
* ��  ��   : 
			 file_path ���ļ�·��������
		     buf	   ���洢���ݵĻ�����
			 size	   ��д���ݵĴ�С(��λ�ֽ�)
* ��  ��   : ��
* ����ֵ   : ��������0���ɹ���1:ʧ�ܡ�
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



