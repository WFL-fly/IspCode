/*
 * isp_utils.h
 *
 *  Created on: 2013-12-9
 *      Author: 13255
 */

#ifndef ISP_UTILS_H_
#define ISP_UTILS_H_

//fix_t :formate
//FLOTOFIX  x*(2^FIX_FRACBITS)
#define FLOTOFIX(fix_t,FIX_FRACBITS, x) (fix_t)( (x) * (1 << FIX_FRACBITS) )
//FIXTOFLOAT x/(2^FIX_FRACBITS)
#define FIXTOFLOAT(fix_t,FIX_FRACBITS, x) ( (fix_t)(x) / (1 << FIX_FRACBITS) )

#define COUNTOF(A) (sizeof(A) / sizeof(A[0]))

#endif /* ISP_UTILS_H_ */
