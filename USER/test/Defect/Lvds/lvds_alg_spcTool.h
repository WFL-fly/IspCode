#ifndef _ALG_SPCTOOL_LVDS_H_
#define _ALG_SPCTOOL_LVDS_H_

#ifdef __cplusplus
extern "C" {
#endif
/* ========================================================================== */
/*                             ͷ�ļ���                                       */
/* ========================================================================== */
#include <stdio.h>
#include <Windows.h>

/* ========================================================================== */
/*                           ������Ͷ�����                                   */
/* ========================================================================== */

//�汾��
typedef enum
{
	LVDS_VERSION_101 = 1,
	LVDS_VERSION_102,
	LVDS_VERSION_NUM
}LVDS_VERSION;

//raw���ͣ��ڰ׻��ɫ
typedef enum
{
	LVDS_RAW_TYPE_BW    = 0,
	LVDS_RAW_TYPE_COLOR,
	LVDS_RAW_TYPE_NUM
}LVDS_RAW_TYPE;

//raw���ͣ��ڰ׻��ɫ
typedef enum
{
	LVDS_RERVESEX_TYPE_NO    = 1,
	LVDS_RERVESEX_TYPE_YES,
	LVDS_RERVESEX_TYPE_NUM
}LVDS_RERVESEX_TYPE;

/*����������Ϣ*/
struct LVDS_BADPOINTINFO
{
	int  x;         //��������x
	int  y;         //��������y
	int  type;      //�����޲�����
	char reserve[4];
};

/* �㷨������� */
struct LVDS_SPCParam
{
	unsigned int   			width;                  // in,     	����ͼ��С
	unsigned int   			height;                 // in,     	����ͼ��С
	int 					rawType;                // in, 		�Ƿ��ɫͼƬ, LVDS_RAW_TYPE  0Ϊmono��1Ϊcolor
	int  					version;                // in, 		�㷨�汾��, LVDS_VERSION
	LVDS_BADPOINTINFO*		spcRawData;				// in, 		���뻵����Ϣ
	int  					defectCount;			// in, 		���뻵���ܸ���
	int  					reverseFlag;			// in, 		���뻵����ʼ��λ��,LVDS_RERVESEX_TYPE 0����ת 1��ת
};

/* �㷨�������������*/
struct LVDS_SPCTable
{
	LVDS_BADPOINTINFO*		canRepairPoint_no;
	int 					canRepairSum_no;
	LVDS_BADPOINTINFO*		canRepairPoint_x;
	int 					canRepairSum_x;
	LVDS_BADPOINTINFO*		canRepairPoint_y;
	int 					canRepairSum_y;
	LVDS_BADPOINTINFO*		canRepairPoint_xy;
	int 					canRepairSum_xy;
	LVDS_BADPOINTINFO*		canNotRepairPoint_no;
	int 					canNotRepairSum_no;
	LVDS_BADPOINTINFO*		canNotRepairPoint_x;
	int 					canNotRepairSum_x;
};



/* ========================================================================== */
/*                          ����������                                        */
/* ========================================================================== */

/*******************************************************************************
* ������  : detectBadPointInfo_lvds
* ��  ��  : ����SPC������
* ��  ��  : - ALG_SPCParam
* ��  ��  ��- ALG_SPCTable
* ��  ��  : ��
* ����ֵ  : OSA_SOK: �ɹ���
*           OSA_EXX: ʧ�ܡ�
*******************************************************************************/
int detectBadPointInfo_lvds(LVDS_SPCParam *SpcParam, LVDS_SPCTable *SpcTable);

/*******************************************************************************
* ������  : deleteBadPointInfo
* ��  ��  : �ͷ�BadPointInfo�ṹ����ָ��ָ���ڴ�ռ�
* ��  ��  : ��

* ��  ��  : ��
* ����ֵ  : OSA_SOK: �����ɹ���
*           OSA_EXX: ����ʧ�ܡ�
*******************************************************************************/

int deleteBadPointInfo_lvds(LVDS_SPCTable *SpcTable);
#ifdef __cplusplus
}
#endif

#endif