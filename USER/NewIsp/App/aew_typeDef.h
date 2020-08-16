/*******************************************************************************
* aew_macro.h
*
* Copyright (C) 2019-2021 ZheJiang Dahua Technology CO.,LTD.
*
* Author : Yan Hongsheng  <yan_hongsheng@dahuatech.com>
* Version: V1.0.0  2019-9-1 Create
*
* Desc: ISP�궨�����ģ���ͳһ����������
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

/* ���������� */
#ifndef DEFINED_Bool
#define DEFINED_Bool
typedef unsigned char      Bool;        /* ͨ�ò������� */
#endif

/* �з������Ͷ��� */
#ifndef DEFINED_Int32
#define DEFINED_Int32
typedef int                Int32;       /* �з���32λ���������� */   
#endif

#ifndef DEFINED_Int16
#define DEFINED_Int16
typedef short              Int16;       /* �з���16λ���������� */   
#endif

#ifndef DEFINED_Int8
#define DEFINED_Int8
typedef char               Int8;        /* �з���8λ���������� */    
#endif

/* ָ�����Ͷ��� */
#ifndef DEFINED_Ptr
#define DEFINED_Ptr
typedef void *             Ptr;         /* ָ������ */
#endif

/* �ַ����Ͷ��� */
#ifndef DEFINED_String
#define DEFINED_String
typedef char *             String;      /* �ַ������ͣ���NUL��β��*/
#endif

#ifndef DEFINED_Char
#define DEFINED_Char
typedef char               Char;        /* �ַ����� */
#endif

/* �޷������Ͷ��� */ 
#ifndef DEFINED_Uint32
#define DEFINED_Uint32
typedef unsigned int       Uint32;      /* �޷���32λ���������� */ 
#endif

#ifndef DEFINED_Uint16
#define DEFINED_Uint16
typedef unsigned short     Uint16;      /* �޷���16λ���������� */ 
#endif

#ifndef DEFINED_Uint8
#define DEFINED_Uint8
typedef unsigned char      Uint8;       /* �޷���8λ���������� */ 
#endif

#ifndef DEFINED_Int64
#define DEFINED_Int64
typedef long long          Int64;       /* �з���64λ���������� */
#endif

#ifndef DEFINED_Bool16
#define DEFINED_Bool16
typedef unsigned short     Bool16;      /* 16λ�������� */
#endif

#ifndef DEFINED_Bool32
#define DEFINED_Bool32
typedef unsigned int       Bool32;      /* 32λ�������� */
#endif

#ifndef DEFINED_Int32L
#define DEFINED_Int32L
typedef long               Int32L;      /* �з���32λ������������ */ 
#endif

#ifndef DEFINED_Uint32L
#define DEFINED_Uint32L
typedef unsigned long      Uint32L;     /* �޷���32λ������������ */   
#endif

#ifndef DEFINED_Uint64
#define DEFINED_Uint64
typedef unsigned long long Uint64;      /* �޷���64λ���������� */
#endif


/* �������Ͷ��� */
#ifndef DEFINED_Float32
#define DEFINED_Float32
typedef float              Float32;		/* 32λ���������� */
#endif

#ifndef DEFINED_Float64
#define DEFINED_Float64
typedef double             Float64;		/* 64λ���������� */
#endif

/* ������� */
#ifndef DEFINED_Handle
#define DEFINED_Handle
typedef void *             Handle;      /* ͳ�þ������ */
#endif

/* �����Ͷ��� */
#ifndef DEFINED_Empty
#define DEFINED_Empty
typedef void               Empty;        /* ������ */
#endif

#endif
