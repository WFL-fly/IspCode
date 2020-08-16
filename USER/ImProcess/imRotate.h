#ifndef IM_ROTATE_H
#define IM_ROTATE_H

/*
tagImFmt:���ݸ�ʽ
Ŀǰֻ֧��mono8
*/
typedef enum {
  MONO8       = 0, /**< mono8 */
} tagImFmt;
/*
tagRotateDir:��ת����
*/
typedef enum {
  CLOCK_WISE       = 0, /**< ˳ʱ�� */
  ANTI_CLOCK_WISE       /**< ��ʱ�� */
} tagRotateDir;
/*
tagRotateAngle:��ת�Ƕ�
*/
typedef enum {
  ANGLE_90       = 0, /**< ��ת90�� */
  ANGLE_180 ,         /**< ��ת180�� */
  ANGLE_270           /**< ��ת270�� */
} tagRotateAngle;
/*
tagRotateParam:��ת����
*/
typedef struct {
	tagRotateDir         rotateDir;
    tagRotateAngle       rotateAngle;
}tagRotateParam;

/*
tagResStatus:����ִ�н��״̬
*/
typedef enum {

  OK = 0,           /**< ��ת�ɹ� */
  ParamErr     ,    /**< ����������� */
  MemApplyErr       /**< �����ڴ�ʧ�� */
} tagResStatus;
/*
tagImIuput:����ͼ�������Ϣ
*/
typedef struct {
	unsigned char* pImBuf;
	unsigned short imWidth;
	unsigned short imHeight;
    tagImFmt       imFmt;
}tagImParam;
/******
�������ƣ�imRotate
�������ܣ�ͼ����ת
���������
          pIm��ͼ�����ݲ�����Ϣ
          rotateParam����ת������Ϣ
�����    tagResStatus������ִ�н��
*******/
tagResStatus imRotate(tagImParam* pIm,tagRotateParam* rotateParam );

#endif