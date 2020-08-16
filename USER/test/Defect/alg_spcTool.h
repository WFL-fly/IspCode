#ifndef _ALG_SPCTOOL_H_
#define _ALG_SPCTOOL_H_

#ifdef __cplusplus
extern "C" {
#endif 
	/* ========================================================================== */
	/*                             ͷ�ļ���                                       */
	/* ========================================================================== */

#include <stdio.h>
#include <Windows.h>
	//#include <WinDef.h>

	/* ========================================================================== */
	/*                           ������Ͷ�����                                   */
	/* ========================================================================== */

	//�汾��
	typedef enum
	{
		SPC_VERSION_101 = 1,
		SPC_VERSION_102 = 2,
		SPC_VERSION_103 = 3,
		SPC_VERSION_NUM
	}SPC_VERSION;

	//�����㷨�汾��
	typedef enum
	{
		BADCOLUMN_VERSION_101 = 1,
		BADCOLUMN_VERSION_NUM
	}BADCOLUMN_VERSION;

	//raw���ͣ��ڰ׻��ɫ
	typedef enum
	{
		SPC_RAW_TYPE_BW = 1,
		SPC_RAW_TYPE_COLOR,
		SPC_RAW_TYPE_NUM
	}SPC_RAW_TYPE;

	//����������Ϣ
	struct SPC_BADPOINTINFO
	{
		int  	x;         //��������x
		int  	y;         //��������y
		int  	type;      //�����޲�����
		char 	reserve[4];
		/*
		bool operator==(const SPC_BADPOINTINFO& point)const
		{
			return (x==point.x&&y==point.y);
		}*/
	};
	
	//������ͼ����ϰ벿�ֻ����°벿��,�������еı�ʶ
	typedef enum
	{
		BAD_COLUMN_IN_UPPER_IMAGE = 1,
		BAD_COLUMN_IN_LOWER_IMAGE = 2,
		BAD_COLUMN_IN_ALL_IMAGE = 3
	}BAD_COLUMN_POSITION_FLAG;

	//����������Ϣ
	struct SPC_BADCOLUMNINFO
	{
		int				x;					//��������x
		int				y;					//�����ϲ����޲��Ļ����������
		int				type;				//�����޲�����
		unsigned short	positionInImageFlag;//������ͼ����ϰ벿�ֻ����°벿�֣�1���ϰ벿�֣�3���°벿��
		char			reserve[4];
	};


	//����������ͼ������Դ����
	struct SPC_BADPOINT_RESOUCE
	{
		unsigned short 	*pBuffer[16];    				// in, ͼƬ����Դ, ʱ���˲�ͼ�񣬹�һ����12bit
		int 			imageNumber;             		// in, ͼƬ����
		int  			Thr[16];                        // in, ��������ƫ��,��һ����8bit
		int				badColumnThr[16];				// in, ��������ƫ���һ����8bit
		int				badLineThr[16];                 // in, ����������ƫ���һ����8bit
		char			reserve[4];
	};

	//��������Ϣ����
	struct SPC_BADPOINTINFOS
	{
		int 					imageNumber;				// in		ͼƬ����	
		unsigned char 			*raw[17];  					// in/out, 	���ɵĻ���ͼ  ����Ϊ1���õ�Ϊ0
		unsigned int   			width;						// in,     	����ͼ��С
		unsigned int   			height;						// in,     	����ͼ��С
		int 					rawType;					// in, 		�Ƿ��ɫͼƬ, SPC_RAW_TYPE
		int  					version;					// in, 		�㷨�汾��, SPC_VERSION
		unsigned int 			badPointSum;        		// out, 	��⵽�Ļ�������
		struct SPC_BADPOINTINFO *canRepairCoordinate; 		// out, 	����������Ϣ
		unsigned int 			canRepairSum;				// out, 	���޸��Ļ�������
		struct SPC_BADPOINTINFO *canNotRepairCoordinate;	// out, 	����������Ϣ
		unsigned int 			canNotRepairSum;			// out, 	�����޸��Ļ�������

		unsigned int			*canRepairInfo_CL[4];		// out,		���޸��Ļ���,only for cameraLink

		int						 needBadColumnCorrect;				// in,	�Ƿ���Ҫ���н�����0������Ҫ��1����Ҫ
		int						 flag_CXP;							// in,	�Ƿ�cxp�ӿ�,0: ���ǣ�1����
		unsigned char			 *badRaw[17];						//in,	���ɵĻ��㡢����ͼ��0:�õ㣬1:���㣬2:���� 3:����	
		int						 badColumnVersion;					// in,	�����㷨�汾
		unsigned int 			 badColumnSum;        				// out, 	��⵽�Ļ�������
		struct SPC_BADCOLUMNINFO *canRepairBadColumnCoordinate; 	// out, 	����������Ϣ
		unsigned int 			 canRepairBadColumnSum;				// out, 	���޸��Ļ�������
		struct SPC_BADCOLUMNINFO *canNotRepairBadColumnCoordinate;	// out, 	����������Ϣ
		unsigned int 			 canNotRepairBadColumnSum;			// out, 	�����޸��Ļ����ϵĻ�������

		struct SPC_BADCOLUMNINFO *canRepairPointCooratBadCol; 		// out, 	�����Ͽ��޸��ĵ����Ϣ�����ڹ��ߵļ��鲿��
		unsigned int			 canRepairPointsSumatBadCol;		//out,	�����Ͽ��޸���ĸ��������ڹ��ߵļ��鲿��

		char	reserve[4];
	};

	//--------------------------LF�����ṹ��-------------------------------//
	//����������ͼ������Դ����
	struct SPC_Max_BADPOINT_RESOUCE
	{
		int			    needhighBlack;				           // in,  �Ƿ���Ҫ�����ع��ͼ���㣬0������Ҫ��1����Ҫ
		int             maxBadpointNumber;                     // in,  ͼ����󵥸���������LF����
		int             ori_Threshold;                         // in,  ����ͼ���жϻ���ĳ�ʼ��ֵ��8bit,LF����
	    unsigned short 	*pBuffer_highBlack;    				   // in,  ͼƬ����Դ, ʱ���˲�ͼ�񣬹�һ����12bit
        char			reserve[2];
	};

	//��������Ϣ����
	struct SPC_Max_BADPOINTINFOS
	{
		unsigned char 			*highBlack_Badraw;  			// in/out, 	���ɵĻ���ͼ  ����Ϊ1���õ�Ϊ0
		unsigned int   			Max_width;						// in,     	����ͼ��С
		unsigned int   			Max_height;						// in,     	����ͼ��С
		struct SPC_BADPOINTINFO *max_badPointInfo; 		    // out, 	����������Ϣ
		int 			        MaxbadPointSum;        		    // out, 	��⵽�Ļ�������
		int 			        res_Threshold;        		    // out, 	����֮�����ֵ,(12bit)LF����
		char	reserve[4];
	};

	//����������Ϣ
	/*
	struct SPC_Max_BADPOINTINFO
	{
		int  	Max_x;         //��������x
		int  	Max_y;         //��������y
		int  	Max_type;      //�����޲�����
		char 	reserve[4];
	};
	*/

	//----------------------------------------------------------------------------//


	/* ========================================================================== */
	/*                          ����������                                        */
	/* ========================================================================== */
    /*******************************************************************************
	* ������  : detectBadPointInit
	* ��  ��  : �������ʼ������Ҫ����������־�ļ�
	* ��  ��  : ��

	* ��  ��  : ��
	* ����ֵ  : �ޡ�
	*******************************************************************************/
    void detectBadPointInit();
    /*******************************************************************************
	* ������  : detectBadPointDestroy
	* ��  ��  : �������ͷţ���Ҫ�����ر���־�ļ�
	* ��  ��  : ��

	* ��  ��  : ��
	* ����ֵ  : �ޡ�
	*******************************************************************************/
    void detectBadPointDestroy();

	/*******************************************************************************
	* ������  : detectBadPointInfo
	* ��  ��  : ͼƬ����ֵ => ����ͼ���������ꡢ����������Ϣ
	* ��  ��  : ��

	* ��  ��  : ��
	* ����ֵ  : OSA_SOK: �����ɹ���
	*           OSA_EXX: ����ʧ�ܡ�
	*******************************************************************************/
	int detectBadPointInfo(struct SPC_BADPOINT_RESOUCE *pImageBuffer, struct SPC_BADPOINTINFOS *badPonitInfo);

	/*******************************************************************************
	* ������  : detectBadPointInfo_CL
	* ��  ��  : ����ͼ => �������ꡢ����������Ϣ
	* ��  ��  : ��

	* ��  ��  : ��
	* ����ֵ  : OSA_SOK: �����ɹ���
	*           OSA_EXX: ����ʧ�ܡ�
	*******************************************************************************/
	int detectBadPointInfo_CL(struct SPC_BADPOINTINFOS *badPonitInfo);

	/*******************************************************************************
	* ������  : deleteBadPointInfo
	* ��  ��  : �ͷ�BadPointInfo�ṹ����ָ��ָ���ڴ�ռ�
	* ��  ��  : ��

	* ��  ��  : ��
	* ����ֵ  : OSA_SOK: �����ɹ���
	*           OSA_EXX: ����ʧ�ܡ�
	*******************************************************************************/
	int deleteBadPointInfo(struct SPC_BADPOINTINFOS *badPonitInfo);
	/*******************************************************************************
	* ������  : deleteBadPointInfo_CL
	* ��  ��  : �ͷ�BadPointInfo�ṹ����ָ��ָ���ڴ�ռ�,������*raw
	* ��  ��  : ��

	* ��  ��  : ��
	* ����ֵ  : OSA_SOK: �����ɹ���
	*           OSA_EXX: ����ʧ�ܡ�
	*******************************************************************************/
	int deleteBadPointInfo_CL(struct SPC_BADPOINTINFOS *badPonitInfo);

	/***************************************************
	*������ �� detectMaxBadPointInfo
	*��  �� :  LF�����������ع��ͼ������󻵵�
	***************************************************/
	int detectMaxBadPointInfo(struct SPC_Max_BADPOINT_RESOUCE *pImageBufferMax, struct SPC_Max_BADPOINTINFOS *badPonitInfoMax);

	/***************************************************
	*������ �� deleteMaxBadPointInfo
	*��  �� :  LF�����������ع��ͼ������󻵵�
	***************************************************/
	int deleteMaxBadPointInfo(struct SPC_Max_BADPOINT_RESOUCE *pImageBufferMax, struct SPC_Max_BADPOINTINFOS *badPonitInfoMax);

#ifdef __cplusplus
}
#endif

#endif


#if 0


//�汾��
	typedef enum
	{
		SPC_VERSION_101 = 1,
		SPC_VERSION_102,
		SPC_VERSION_NUM
	}SPC_VERSION;

	//�����㷨�汾��
	typedef enum
	{
		BADCOLUMN_VERSION_101 = 1,
		BADCOLUMN_VERSION_NUM
	}BADCOLUMN_VERSION;

	//raw���ͣ��ڰ׻��ɫ
	typedef enum
	{
		SPC_RAW_TYPE_BW = 1,
		SPC_RAW_TYPE_COLOR,
		SPC_RAW_TYPE_NUM
	}SPC_RAW_TYPE;

	//����������Ϣ
	struct SPC_BADPOINTINFO
	{
		int  	x;         //��������x
		int  	y;         //��������y
		int  	type;      //�����޲�����
		char 	reserve[4];
	};

	//������ͼ����ϰ벿�ֻ����°벿�ֵı�ʶ
	typedef enum
	{
		BAD_COLUMN_IN_UPPER_IMAGE = 1,
		BAD_COLUMN_IN_LOWER_IMAGE = 3
	}BAD_COLUMN_POSITION_FLAG;


	//����������Ϣ
	struct SPC_BADCOLUMNINFO
	{
		int				x;					//��������x
		int				y;					//�����ϲ����޲��Ļ����������
		int				type;				//�����޲�����
		unsigned short	positionInImageFlag;//������ͼ����ϰ벿�ֻ����°벿�֣�1���ϰ벿�֣�3���°벿��
		char			reserve[4];
	};

	//����������ͼ������Դ����
	struct SPC_BADPOINT_RESOUCE
	{
		unsigned short 	*pBuffer[16];    				// in, ͼƬ����Դ, ʱ���˲�ͼ�񣬹�һ����12bit
		int 			imageNumber;             		// in, ͼƬ����	
		int  			Thr[16];                        // in, ��������ƫ��,��һ����8bit
		int				badColumnThr[16];				// in, ��������ƫ���һ����8bit
		char			reserve[4];
	};

	//��������Ϣ����
	struct SPC_BADPOINTINFOS
	{
		unsigned char 			*raw;						// in/out, 	���ɵĻ���ͼ  ����Ϊ1���õ�Ϊ0
		unsigned int   			width;						// in,     	����ͼ��С
		unsigned int   			height;						// in,     	����ͼ��С
		int 					rawType;					// in, 		�Ƿ��ɫͼƬ, SPC_RAW_TYPE
		int  					version;					// in, 		�㷨�汾��, SPC_VERSION
		unsigned int 			badPointSum;        		// out, 	��⵽�Ļ�������
		struct SPC_BADPOINTINFO *canRepairCoordinate; 		// out, 	����������Ϣ
		unsigned int 			canRepairSum;				// out, 	���޸��Ļ�������
		struct SPC_BADPOINTINFO *canNotRepairCoordinate;	// out, 	����������Ϣ
		unsigned int 			canNotRepairSum;			// out, 	�����޸��Ļ�������

		unsigned int			*canRepairInfo_CL[4];		// out,		���޸��Ļ���,only for cameraLink
		char	reserve[4];
	};

	//���м����Ϣ����
	struct SPC_BADCOLUMNINFOS
	{
		unsigned char 			 *raw;						// in/out, 	���ɵĻ���ͻ���ͼ  ����Ϊ1���õ�Ϊ0������Ϊ2
		unsigned int   			 width;						// in,     	����ͼ��С
		unsigned int   			 height;					// in,     	����ͼ��С
		int 					 rawType;					// in, 		�Ƿ��ɫͼƬ, SPC_RAW_TYPE
		int						 version;					// in,		�����㷨�汾��
		unsigned int 			 badColumnSum;        		// out, 	��⵽�Ļ�������
		struct SPC_BADCOLUMNINFO *canRepairCoordinate; 		// out, 	����������Ϣ
		unsigned int 			 canRepairSum;				// out, 	���޸��Ļ�������
		struct SPC_BADCOLUMNINFO *canNotRepairCoordinate;	// out, 	����������Ϣ
		unsigned int 			 canNotRepairSum;			// out, 	�����޸��Ļ�������
		char	reserve[4];
	};

	int detectBadPointBadColumnInfo(struct SPC_BADPOINT_RESOUCE *pImageBuffer, struct SPC_BADPOINTINFOS *badPonitInfo, struct SPC_BADCOLUMNINFOS *badColumnInfos);
	int deleteBadPointBadColumnInfo(struct SPC_BADPOINTINFOS *badPonitInfo, struct SPC_BADCOLUMNINFOS *badColumnInfos);
#endif