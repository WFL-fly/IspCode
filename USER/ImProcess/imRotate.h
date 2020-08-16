#ifndef IM_ROTATE_H
#define IM_ROTATE_H

/*
tagImFmt:数据格式
目前只支持mono8
*/
typedef enum {
  MONO8       = 0, /**< mono8 */
} tagImFmt;
/*
tagRotateDir:旋转方向
*/
typedef enum {
  CLOCK_WISE       = 0, /**< 顺时针 */
  ANTI_CLOCK_WISE       /**< 逆时针 */
} tagRotateDir;
/*
tagRotateAngle:旋转角度
*/
typedef enum {
  ANGLE_90       = 0, /**< 旋转90度 */
  ANGLE_180 ,         /**< 旋转180度 */
  ANGLE_270           /**< 旋转270度 */
} tagRotateAngle;
/*
tagRotateParam:旋转参数
*/
typedef struct {
	tagRotateDir         rotateDir;
    tagRotateAngle       rotateAngle;
}tagRotateParam;

/*
tagResStatus:函数执行结果状态
*/
typedef enum {

  OK = 0,           /**< 旋转成功 */
  ParamErr     ,    /**< 输入参数错误 */
  MemApplyErr       /**< 申请内存失败 */
} tagResStatus;
/*
tagImIuput:输入图像参数信息
*/
typedef struct {
	unsigned char* pImBuf;
	unsigned short imWidth;
	unsigned short imHeight;
    tagImFmt       imFmt;
}tagImParam;
/******
函数名称：imRotate
函数功能：图像旋转
输入参数：
          pIm：图像数据参数信息
          rotateParam：旋转参数信息
输出：    tagResStatus：函数执行结果
*******/
tagResStatus imRotate(tagImParam* pIm,tagRotateParam* rotateParam );

#endif