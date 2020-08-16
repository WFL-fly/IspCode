#pragma once
#ifndef ERROR_TYPE_DEF_H
#define ERROR_TYPE_DEF_H
typedef enum {
  OK       = 0, /**< OK */
  Err_Ptr_Null , /**< 指针为空 */
  Err_Len_Zero , /**< 数据长度为0 */
  Err_ImBitErr , /**< 两幅图bit不同 */
  Err_ImxImy_InfoNotEqual , /**< 两幅图bit不同 */
  Err_CaclBmpXAvgFail , /**< 两幅图宽高不同 */
  Err_CaclBmpYAvgFail , /**< 两幅图宽高不同 */
  Err_CaclBmpXVarianceFail,
  Err_CaclBmpYVarianceFail,
  Err_CaclSSImResFail
} ErrorInfoType;
#endif