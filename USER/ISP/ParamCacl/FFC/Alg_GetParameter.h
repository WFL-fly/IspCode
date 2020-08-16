#ifndef _ALG_GET_PARAMETER_H_
#define _ALG_GET_PARAMETER_H_
/* ========================================================================== */
/*                             ͷ�ļ���                                       */
/* ========================================================================== */
#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <Windows.h>

/* ========================================================================== */
/*                           ������Ͷ�����                                   */
/* ========================================================================== */

#define OSA_SOK	 0	 		//���سɹ�
#define OSA_EXX -1			//����ʧ��

//�㷨����
typedef enum{
	ALG_TYPE_FFC_REGION = 0,
	ALG_TYPE_FFC_ROW,
    ALG_TYPE_FFC_REGION_PICK,
	ALG_TYPE_FFC_NUM
} ALG_TYPE_FFC;

//ͼ���ʽ����
typedef enum{
	ALG_IMG_FORMAT_MONO = 0,
	ALG_IMG_FORMAT_RG,
	ALG_IMG_FORMAT_GB,
	ALG_IMG_FORMAT_GR,
	ALG_IMG_FORMAT_BG,
	ALG_IMG_FORMAT_NUM
} ALG_IMG_FORMAT;

/* �㷨������� */
typedef struct
{
	int 			nWidth;  		//����ͼ����
	int 			nHeight;		//����ͼ��߶�
	int 			nBits;			//����ͼ������λ��
	void 			*greyData;		//������ͼ����
	void			*blackData;		//�����ͼ����
	int				greyDst;		//��ͼ����Ŀ��ֵ
	int				blackDst;		//��ͼ����Ŀ��ֵ
	ALG_IMG_FORMAT 	nFormat;		//����ͼ�����ݸ�ʽ
	ALG_TYPE_FFC	nType;			//��ѡ�㷨���
	int 			region_height_scale;	//FFC_Region�㷨ѹ��scale,--USB:16;GIGE:16
	int 			region_width_scale;	//FFC_Region�㷨ѹ��scale,--USB:32;GIGE:16
	unsigned char	kb_byte;		//FFC_Region�㷨��KBռ�ֽ���Ŀ
    unsigned char	paramIsPick;	//KB�����Ƿ������ѡ 0������ѡ������KB�����洢�������
                                    //1��������ѡ�����ֲ����洢�������ȱʧ�Ĳ��������ͨ����ֵ��ȡ
	int 			reserved[8];
}ALG_FFCParam;

/* �㷨�������������*/
typedef struct
{	
	float			nDiff;			//������Ȳ����ȳ̶�
	
	int				nSize;			//���FFC���ݴ�С���ֽ���
	unsigned char	*pFFCTable;		//�����������
	int				nCRC32;			//����������ݵ�crc32У����
	
	int 			reserved[8];
}ALG_FFCTable;

/* ========================================================================== */
/*                          ����������                                        */
/* ========================================================================== */

/*******************************************************************************
* ������  : ALG_Nonuniformity_calc
* ��  ��  : ��ȡ��ͼ�Ĳ�������nDiff
* ��  ��  : - ALG_FFCParam
            - ALG_FFCTable
* ��  ��  : ��
* ����ֵ  : OSA_SOK: �ɹ���
*           OSA_EXX: ʧ�ܡ�
*******************************************************************************/
//int ALG_Nonuniformity_calc(ALG_FFCParam *pFFCParam, ALG_FFCTable *pFFCTable);

/*******************************************************************************
* ������  : ALG_GetParameterInit
* ��  ��  : ��ȡFFC�������ڴ�ռ��С
* ��  ��  : - ALG_FFCParam
- ALG_FFCTable
* ��  ��  : ��
* ����ֵ  : >0 : �ɹ���
*           OSA_EXX: ʧ�ܡ�
*******************************************************************************/
int ALG_GetParameterMemoryLen(ALG_FFCParam *pFFCParam);

/*******************************************************************************
* ������  : ALG_GetParameterRun
* ��  ��  : ����FFC������
* ��  ��  : - ALG_FFCParam
            - ALG_FFCTable
* ��  ��  : ��
* ����ֵ  : OSA_SOK: �ɹ���
*           OSA_EXX: ʧ�ܡ�
*******************************************************************************/
int ALG_GetParameterRun(ALG_FFCParam *pFFCParam, ALG_FFCTable *pFFCTable);

#ifdef __cplusplus
}
#endif


#endif