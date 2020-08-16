/*******************************************************************************
* alg_afix.h
*
* sharp CCD 2900 ��̬����ģ��
*
* Author : Huang Bijuan
* Version: V1.0.0  2017-7-24 Create
*
*******************************************************************************/

#ifndef _ALG_AFIX_
#define _ALG_AFIX_

/* ========================================================================== */
/*                             ͷ�ļ���                                       */
/* ========================================================================== */
#ifdef __cplusplus
extern "C" {
#endif

      
	/* ���Ĳ���������Ŀǰ�ɼ�60����*/
#define MAX_SAMPLE_NUM    60
	/* У�������߶�����һ��63������ */
#define AFIX_TABLE_CURV_NUM  63

	/* У�������������ٽ��������һ��64��*/
#define AFIX_TABLE_POINT_NUM 64

#define AFIX_CH_NUM_4 4
#define AFIX_CH_NUM_3 3

	//����
	//У�����ص�,�ĳɸ��������һ�²�������
	//��������ʱ��ALG_AfixPixel.gr_kbȡgr����ֵ����Ϊ���k,bʱ����Ϊk��bֵ
	typedef struct
	{
		float  gr;
		float   r;
		float   b;
		float  gb;
	}ALG_In_AfixPixel;

	//��ͨ��AD������ֵ AFIX_CH_NUM_4=4
	typedef struct
	{
		ALG_In_AfixPixel    inAfixregion[AFIX_CH_NUM_4];
	}ALG_In_AfixRegion;

	//����ֵMAX_SAMPLE_NUM=60
	typedef struct
	{
		ALG_In_AfixRegion  	inAfixsamp[MAX_SAMPLE_NUM];
	}ALG_In_AfixSample;

	
	typedef struct
	{
		ALG_In_AfixSample  	input;
		int 				inFormat;		//monoΪ0��colorΪ1
		int					inBits;
	}ALG_Input;

	typedef struct
	{
		void*  				Output_Data;
		int 				Output_Size;	//��Ч�ֽ���
	}ALG_Output;

	
	/* ========================================================================== */
	/*                          ����������                                        */
	/* ========================================================================== */
	
#define ALG_HANDLE  void * 

	/*******************************************************************************
	* ������  : ALG_Init
	* ��  ��  : ��ʼ��ģ��
	* ��  ��  : ��

	* ��  ��  : ��
	* ����ֵ  : OSA_SOK: �����ɹ���
	*           OSA_EXX: ����ʧ�ܡ�
	*******************************************************************************/
	int ALG_Init(ALG_Input *Input, ALG_HANDLE *handle);
	/*******************************************************************************
	* ������  : ALG_Run
	* ��  ��  : �����㷨ģ��
	* ��  ��  : ��

	* ��  ��  : ��
	* ����ֵ  : OSA_SOK: �����ɹ���
	*           OSA_EXX: ����ʧ�ܡ�
	*******************************************************************************/
	ALG_Output * ALG_Run(ALG_HANDLE handle, ALG_Input *Input);
	/*******************************************************************************
	* ������  : ALG_Delete
	* ��  ��  : �ڴ��ͷ�
	* ��  ��  : ��

	* ��  ��  : ��
	* ����ֵ  : OSA_SOK: �����ɹ���
	*           OSA_EXX: ����ʧ�ܡ�
	*******************************************************************************/
	void ALG_Delete(ALG_HANDLE handle);
#ifdef __cplusplus
}
#endif

#endif