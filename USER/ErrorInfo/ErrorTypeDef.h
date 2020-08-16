#pragma once
#ifndef ERROR_TYPE_DEF_H
#define ERROR_TYPE_DEF_H
typedef enum {
  OK       = 0, /**< OK */
  Err_Ptr_Null , /**< ָ��Ϊ�� */
  Err_Len_Zero , /**< ���ݳ���Ϊ0 */
  Err_ImBitErr , /**< ����ͼbit��ͬ */
  Err_ImxImy_InfoNotEqual , /**< ����ͼbit��ͬ */
  Err_CaclBmpXAvgFail , /**< ����ͼ��߲�ͬ */
  Err_CaclBmpYAvgFail , /**< ����ͼ��߲�ͬ */
  Err_CaclBmpXVarianceFail,
  Err_CaclBmpYVarianceFail,
  Err_CaclSSImResFail
} ErrorInfoType;
#endif