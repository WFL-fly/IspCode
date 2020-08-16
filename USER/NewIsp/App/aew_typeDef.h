/*******************************************************************************
* aew_macro.h
*
* Copyright (C) 2019-2021 ZheJiang Dahua Technology CO.,LTD.
*
* Author : Yan Hongsheng  <yan_hongsheng@dahuatech.com>
* Version: V1.0.0  2019-9-1 Create
*
* Desc: ISP宏定义管理模块和统一的数据类型
*
* Modification:
*    Date    :
*    Revision:
*    Author  :
*    Contents:
*******************************************************************************/
#ifndef _AEW_TYPE_DEF_H_
#define _AEW_TYPE_DEF_H_

#define OSA_SOK 0
#define OSA_EXX -1

#define ALG_SOK 0
#define ALG_EXX -1

/* 布尔量定义 */
#ifndef DEFINED_Bool
#define DEFINED_Bool
typedef unsigned char      Bool;        /* 通用布尔类型 */
#endif

/* 有符号类型定义 */
#ifndef DEFINED_Int32
#define DEFINED_Int32
typedef int                Int32;       /* 有符号32位整形数类型 */   
#endif

#ifndef DEFINED_Int16
#define DEFINED_Int16
typedef short              Int16;       /* 有符号16位整形数类型 */   
#endif

#ifndef DEFINED_Int8
#define DEFINED_Int8
typedef char               Int8;        /* 有符号8位整形数类型 */    
#endif

/* 指针类型定义 */
#ifndef DEFINED_Ptr
#define DEFINED_Ptr
typedef void *             Ptr;         /* 指针类型 */
#endif

/* 字符类型定义 */
#ifndef DEFINED_String
#define DEFINED_String
typedef char *             String;      /* 字符串类型，以NUL结尾。*/
#endif

#ifndef DEFINED_Char
#define DEFINED_Char
typedef char               Char;        /* 字符类型 */
#endif

/* 无符号类型定义 */ 
#ifndef DEFINED_Uint32
#define DEFINED_Uint32
typedef unsigned int       Uint32;      /* 无符号32位整形数类型 */ 
#endif

#ifndef DEFINED_Uint16
#define DEFINED_Uint16
typedef unsigned short     Uint16;      /* 无符号16位整形数类型 */ 
#endif

#ifndef DEFINED_Uint8
#define DEFINED_Uint8
typedef unsigned char      Uint8;       /* 无符号8位整形数类型 */ 
#endif

#ifndef DEFINED_Int64
#define DEFINED_Int64
typedef long long          Int64;       /* 有符号64位整形数类型 */
#endif

#ifndef DEFINED_Bool16
#define DEFINED_Bool16
typedef unsigned short     Bool16;      /* 16位布尔类型 */
#endif

#ifndef DEFINED_Bool32
#define DEFINED_Bool32
typedef unsigned int       Bool32;      /* 32位布尔类型 */
#endif

#ifndef DEFINED_Int32L
#define DEFINED_Int32L
typedef long               Int32L;      /* 有符号32位长整形数类型 */ 
#endif

#ifndef DEFINED_Uint32L
#define DEFINED_Uint32L
typedef unsigned long      Uint32L;     /* 无符号32位长整形数类型 */   
#endif

#ifndef DEFINED_Uint64
#define DEFINED_Uint64
typedef unsigned long long Uint64;      /* 无符号64位整形数类型 */
#endif


/* 浮点类型定义 */
#ifndef DEFINED_Float32
#define DEFINED_Float32
typedef float              Float32;		/* 32位浮点数类型 */
#endif

#ifndef DEFINED_Float64
#define DEFINED_Float64
typedef double             Float64;		/* 64位浮点数类型 */
#endif

/* 句柄类型 */
#ifndef DEFINED_Handle
#define DEFINED_Handle
typedef void *             Handle;      /* 统用句柄类型 */
#endif

/* 空类型定义 */
#ifndef DEFINED_Empty
#define DEFINED_Empty
typedef void               Empty;        /* 空类型 */
#endif

#endif
