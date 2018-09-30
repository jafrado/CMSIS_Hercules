/* ----------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:		arm_offset_f32.c      
*      
* Description:	Floating-point vector offset.      
*      
* Target Processor:          Cortex-R4/R5
*
* Version 1.0.0 2011/03/08
*     Alpha release.
*
* Version 1.0.1 2011/09/30
*     Beta release.
*
* Version 2.0.0 2011/12/15
*     Final release. 
* 
* ---------------------------------------------------------------------------- */     
#include "arm_math.h"     
     
/**      
 * @ingroup groupMath      
 */     
     
/**      
 * @defgroup offset Vector Offset      
 *      
 * Adds a constant offset to each element of a vector.      
 *      
 * <pre>      
 *     pDst[n] = pSrc[n] + offset,   0 <= n < blockSize.      
 * </pre>      
 *      
 * There are separate functions for floating-point, Q7, Q15, and Q31 data types.      
 */     
     
/**      
 * @addtogroup offset      
 * @{      
 */     
     
/**      
 * @brief  Adds a constant offset to a floating-point vector.      
 * @param[in]  *pSrc points to the input vector      
 * @param[in]  offset is the offset to be added      
 * @param[out]  *pDst points to the output vector      
 * @param[in]  blockSize number of samples in the vector      
 * @return none.      
 */     
     
     
void arm_offset_f32(     
  float32_t * pSrc,     
  float32_t offset,     
  float32_t * pDst,     
  uint32_t blockSize)     
{     
  uint32_t blkCnt;                               /* loop counter */     
  float32_t in1, in2, in3 ,in4;		 			 /* temporary variables */  
     
  /*loop Unrolling */     
  blkCnt = blockSize >> 3u;     
     
  /* First part of the processing with loop unrolling.  Compute 8 outputs at a time.      
   ** a second loop below computes the remaining 1 to 7 samples. */     
  while(blkCnt > 0u)     
  {     
    /* C = A + offset */     
    /* Add offset and then store the results in the destination buffer. */     
	/* read samples from source */  
	in1 = *pSrc;  
	in2 = *(pSrc + 1);  
  
	/* add offset to input */  
    in1 = in1 + offset;     
  
	/* read samples from source */  
	in3 = *(pSrc + 2);  
  
	/* add offset to input */  
    in2 = in2 + offset;     
  
	/* read samples from source */  
	in4 = *(pSrc + 3);  
  
	/* add offset to input */  
    in3 = in3 + offset;     
  
	/* store result to destination */  
	*pDst = in1;  
  
	/* add offset to input */  
    in4 = in4 + offset;     
  
	/* store result to destination */  
	*(pDst + 1) = in2;  
  
	/* read samples from source */  
	in1 = *(pSrc + 4);  
  
	/* store result to destination */  
	*(pDst + 2) = in3;  
  
	/* read samples from source */  
	in2 = *(pSrc + 5);  
  
	/* store result to destination */  
	*(pDst + 3) = in4;  
     
	/* add offset to input */  
    in1 = in1 + offset;     
  
	/* read samples from source */  
	in3 = *(pSrc + 6);  
  
	/* add offset to input */  
    in2 = in2 + offset;     
  
	/* read samples from source */  
	in4 = *(pSrc + 7);  
  
	/* add offset to input */  
    in3 = in3 + offset;     
  
	/* store result to destination */  
 	*(pDst + 4) = in1;  
 	*(pDst + 5) = in2;  
  
	/* add offset to input */  
  	in4 = in4 + offset;     
  
	*(pDst + 6) = in3;  
	  
	/* increment source by 8 to process next samples */  
	pSrc += 8u;  
	  
	/* store result to destination */  
	*(pDst + 7) = in4;  
  
	/* increment destination by 8 */  
	pDst += 8u;  
     
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
     
  /* If the blockSize is not a multiple of 8, compute any remaining output samples here.      
   ** No loop unrolling is used. */     
  blkCnt = blockSize % 0x8u;     
     
  while(blkCnt > 0u)     
  {     
    /* C = A + offset */     
    /* Add offset and then store the result in the destination buffer. */     
	in1 = *pSrc++;  
    *pDst++ = in1 + offset;     
     
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
}     
     
/**      
 * @} end of offset group      
 */     
