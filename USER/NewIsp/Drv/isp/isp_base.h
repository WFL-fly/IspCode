#ifndef ISP_BASE_H_
#define ISP_BASE_H_

#include "sys.h"

#define BIG_ENDIAN_SYSTEM

#ifdef BIG_ENDIAN_SYSTEM

#define COV_CHAR(addr)  ((addr) ^ 0x03)
#define COV_SHORT(addr) ((addr) ^ 0x02)

#else

#define COV_CHAR(addr) (addr)
#define COV_SHORT(addr) (addr)

#endif

#define BIG_CONV_LITTER(data) (((data&0xff)<<24)|((data&0xff00)<<8)|((data&0xff0000)>>8)|((data&0xff000000)>>24))

#if defined(A3600XG000_001) || defined(A3600XG004_001) || defined(A3A20XG000_001) || defined(A3A20XG004_001) || defined(A3B00XG000_001) || defined(A3B00XG004_001) || defined(A3B00XG000GRS_001) || defined(A3600XG000GRS_001) || defined(A3A20XG000GRS_001) || defined(A3A20XG8_032)
// 物流型号使用特殊基地址

#define IRIS_DC_PWM0_BASE 	  (0x9A0E8000)
#define IRIS_DC_PWM1_BASE 	  (0x9A0EC000)
#define IRIS_DC_PWM2_BASE 	  (0x9A0EA000)

#define ISP_VER_BASE          (VISP_BASE + 0x00000)
#define ISP_IIF_BASE          (VISP_BASE + 0x00500)
#define ISP_BOC_BASE          (VISP_BASE + 0x00100)
#define ISP_DPC_BASE          (VISP_BASE + 0x18000)
#define ISP_SPC_BASE          (VISP_BASE + 0x40000)
#define ISP_DGC_BASE          (VISP_BASE + 0x00140)
#define ISP_NR3D_BASE 		  (VISP_BASE + 0x2c000)
#define ISP_WB_BASE           (VISP_BASE + 0x00180)
#define ISP_2RGB_BASE         (VISP_BASE + 0x40000)
#define ISP_CCM_BASE          (VISP_BASE + 0x00800)
#define ISP_GAM_BASE          (VISP_BASE + 0x50000)
#define ISP_GUT_BASE          (VISP_BASE + 0x58000)
#define ISP_CDS_BASE          (VISP_BASE + 0x68000)
#define ISP_CDSLUT_BASE       (VISP_BASE + 0x70000)
#define ISP_EE_BASE           (VISP_BASE + 0x78000)
#define ISP_NR2D_BASE		  (VISP_BASE + 0x00480)
#define ISP_OMODE_BASE        (VISP_BASE + 0x00400)
#define ISP_AWE_BASE          (VISP_BASE + 0x00200)
#define ISP_AWEMEM_BASE       (VISP_BASE + 0x18000)
#define ISP_TRIG_CTRL_BASE    (VISP_BASE + 0xA0000)
#define ISP_BINNING_BASE	  (VISP_BASE + 0x00600)
#define ISP_STA_BASE		  (VISP_BASE + 0x00440)
#define ISP_STAMEM_BASE		  (VISP_BASE + 0x12000)
#define ISP_FPN_BASE		  (VISP_BASE + 0x20000)
#define ISP_LUT2D_BASE        (VISP_BASE + 0x30000)
#define ISP_GIC_BASE          (VISP_BASE + 0x00a00)
#define ISP_FFC_BASE		  (VISP_BASE + 0XD0000)
#define ISP_2RAW_BASE	      (VISP_BASE + 0xD8000)
#define ISP_AVG_BASE		  (VISP_BASE + 0x0C000)
#define DOL_BASE 			  (VISP_BASE + 0xF8000)
#define DRC_V305_BASE 		  (VISP_BASE + 0x38000)


#elif defined(XILINX_FPGA)
// xilinx PLATFORM

#define IRIS_DC_PWM0_BASE 	  (0x9A300000)
#define IRIS_DC_PWM1_BASE 	  (0x9A300100)

#define ISP_AVG_BASE		  (INVALID_BASE)
#define ISP_VER_BASE	      (VISP_BASE + 0x00000)
#define ISP_IIF_BASE          (VISP_BASE + 0x00500)
#define ISP_BOC_BASE          (VISP_BASE + 0x00100)
#define ISP_DPC_BASE	      (VISP_BASE + 0x18000)
#define ISP_SPC_BASE	      (VISP_BASE + 0x40000)
#define ISP_DGC_BASE          (VISP_BASE + 0x00140)
#define ISP_NR3D_BASE 		  (INVALID_BASE)
#define ISP_WB_BASE           (VISP_BASE + 0x00180)
#define ISP_2RGB_BASE         (VISP_BASE + 0x00700)
#define ISP_CCM_BASE          (VISP_BASE + 0x00800)
#define ISP_GAM_BASE          (VISP_BASE + 0x50000)
#define ISP_GUT_BASE          (VISP_BASE + 0x58000)
#define ISP_LUT2D_BASE        (VISP_BASE + 0x30000)
#define ISP_CDS_BASE	      (VISP_BASE + 0x68000)
#define ISP_CDSLUT_BASE       (VISP_BASE + 0x70000)
#define ISP_EE_BASE           (VISP_BASE + 0x78000)
#define ISP_NR2D_BASE         (VISP_BASE + 0x00480)
#define ISP_OMODE_BASE        (VISP_BASE + 0x00400)
#define ISP_AWE_BASE          (VISP_BASE + 0x00200)
#define ISP_AWEMEM_BASE       (VISP_BASE + 0x18000)
#define ISP_TRIG_CTRL_BASE    (VISP_BASE + 0xA0000)
#define ISP_BINNING_BASE	  (VISP_BASE + 0x00600)
#define ISP_STA_BASE          (VISP_BASE + 0x00440)
#define ISP_STAMEM_BASE	      (VISP_BASE + 0x12000)
#define ISP_FPN_BASE          (VISP_BASE + 0x20000)
#define ISP_GIC_BASE	      (VISP_BASE + 0x00a00)
#define ISP_FFC_BASE	      (VISP_BASE + 0XD0000)
#define ISP_2RAW_BASE         (VISP_BASE + 0x00900)
#define DOL_BASE 			  (INVALID_BASE)
#define DRC_V305_BASE 		  (INVALID_BASE)


#else
// altera PLATFORM
#define IRIS_DC_PWM0_BASE 	(0x9A0E8000)
#define IRIS_DC_PWM1_BASE 	(0x9A0EC000)
#define IRIS_DC_PWM2_BASE 	(0x9A0EA000)

#define ISP_AVG_BASE		(VISP_BASE + 0x0C000)
#define ISP_VER_BASE		(VISP_BASE + 0x00000)
#define ISP_IIF_BASE		(VISP_BASE + 0x08000)
#define ISP_BOC_BASE		(VISP_BASE + 0x10000)
#define ISP_DPC_BASE		(VISP_BASE + 0x18000)
#define ISP_SPC_BASE		(VISP_BASE + 0x20000)
#define ISP_DGC_BASE		(VISP_BASE + 0x28000)
#define ISP_NR3D_BASE 		(VISP_BASE + 0x2c000)
#define ISP_WB_BASE			(VISP_BASE + 0x30000)
#define ISP_2RGB_BASE		(VISP_BASE + 0x40000)
#define ISP_CCM_BASE		(VISP_BASE + 0x48000)
#define ISP_GAM_BASE		(VISP_BASE + 0x50000)
#define ISP_GUT_BASE		(VISP_BASE + 0x58000)
#define ISP_LUT2D_BASE		(VISP_BASE + 0x60000)
#define ISP_CDS_BASE		(VISP_BASE + 0x68000)
#define ISP_CDSLUT_BASE		(VISP_BASE + 0x70000)
#define ISP_EE_BASE			(VISP_BASE + 0x78000)
#define ISP_NR2D_BASE		(VISP_BASE + 0x80000)
#define ISP_OMODE_BASE		(VISP_BASE + 0x88000)
#define ISP_AWE_BASE		(VISP_BASE + 0x90000)
#define ISP_AWEMEM_BASE		(VISP_BASE + 0x98000)
#define ISP_TRIG_CTRL_BASE	(VISP_BASE + 0xA0000)
#define ISP_BINNING_BASE	(VISP_BASE + 0xB8000)
#define ISP_STA_BASE		(VISP_BASE + 0xC0000)
#define ISP_STAMEM_BASE		(VISP_BASE + 0xC8000)
#define ISP_FPN_BASE		(VISP_BASE + 0XD0000)
#define ISP_GIC_BASE		(VISP_BASE + 0XE0000)
#define ISP_FFC_BASE		(VISP_BASE + 0XD0000)
#define ISP_2RAW_BASE	    (VISP_BASE + 0xD8000)
#define DOL_BASE 			(VISP_BASE + 0xF8000)
#define DRC_V305_BASE 		(VISP_BASE + 0x38000)

#endif


#endif /* ISP_BASE_H_ */
