/* ----------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:		arm_rms_q31.c      
*      
* Description:	Root Mean Square of the elements of a Q31 vector.      
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
 * @addtogroup RMS      
 * @{      
 */     
     
     
/**      
 * @brief Root Mean Square of the elements of a Q31 vector.      
 * @param[in]       *pSrc points to the input vector      
 * @param[in]       blockSize length of the input vector      
 * @param[out]      *pResult rms value returned here      
 * @return none.      
 *      
 * @details      
 * <b>Scaling and Overflow Behavior:</b>      
 *      
 *\par      
 * The function is implemented using an internal 64-bit accumulator.      
 * The input is represented in 1.31 format, and intermediate multiplication      
 * yields a 2.62 format.      
 * The accumulator maintains full precision of the intermediate multiplication results,       
 * but provides only a single guard bit.      
 * There is no saturation on intermediate additions.      
 * If the accumulator overflows, it wraps around and distorts the result.       
 * In order to avoid overflows completely, the input signal must be scaled down by       
 * log2(blockSize) bits, as a total of blockSize additions are performed internally.       
 * Finally, the 2.62 accumulator is right shifted by 31 bits to yield a 1.31 format value.      
 *      
 */     
     
void arm_rms_q31(     
  q31_t * pSrc,     
  uint32_t blockSize,     
  q31_t * pResult)     
{     
  q31_t *pIn1 = pSrc;                            /* SrcA pointer */     
  q63_t sum = 0;                                 /* accumulator */     
  q31_t in;                                      /* Temporary variable to store the input */     
  uint32_t blkCnt;                               /* loop counter */     
  q31_t in1, in2, in3, in4;						 /* Temporary input variables */  
     
  /*loop Unrolling */     
  blkCnt = blockSize >> 3u;     
     
  /* First part of the processing with loop unrolling.  Compute 8 outputs at a time.      
   ** a second loop below computes the remaining 1 to 7 samples. */     
  while(blkCnt > 0u)     
  {     
    /* C = A[0] * A[0] + A[1] * A[1] + A[2] * A[2] + ... + A[blockSize-1] * A[blockSize-1] */     
    /* Compute sum of the squares and then store the result in a temporary variable, sum */     
	/* read two samples from source buffer */  
	in1 = pIn1[0];  
	in2 = pIn1[1];  
  
	/* calculate power and accumulate to accumulator */  
	sum += (q63_t)in1 * in1;  
	sum += (q63_t)in2 * in2;  
  
	/* read two samples from source buffer */  
	in3 = pIn1[2];  
	in4 = pIn1[3];  
  
	/* calculate power and accumulate to accumulator */  
	sum += (q63_t)in3 * in3;  
	sum += (q63_t)in4 * in4;  
  
	/* read two samples from source buffer */  
	in1 = pIn1[4];  
	in2 = pIn1[5];  
  
	/* calculate power and accumulate to accumulator */  
	sum += (q63_t)in1 * in1;  
	sum += (q63_t)in2 * in2;  
  
	/* read two samples from source buffer */  
	in3 = pIn1[6];  
	in4 = pIn1[7];  
  
	/* calculate power and accumulate to accumulator */  
	sum += (q63_t)in3 * in3;  
	sum += (q63_t)in4 * in4;  
  
	/* update source buffer to process next samples */  
	pIn1 += 8u;  
   
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
    
  /* If the blockSize is not a multiple of 8, compute any remaining output samples here.      
   ** No loop unrolling is used. */     
  blkCnt = blockSize % 0x8u;     
     
  while(blkCnt > 0u)     
  {     
    /* C = A[0] * A[0] + A[1] * A[1] + A[2] * A[2] + ... + A[blockSize-1] * A[blockSize-1] */     
    /* Compute sum of the squares and then store the results in a temporary variable, sum */     
    in = *pIn1++;     
    sum += (q63_t) in *in;     
     
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
     
  /* Convert data in 2.62 to 1.31 by 31 right shifts and saturate */     
#ifdef CCS  
  
  sum = __SSATA(sum, 31, 31);  
     
#else  
  
  sum = __SSAT(sum >> 31, 31);  
  
#endif  
  
  /* Compute Rms and store the result in the destination vector */     
  arm_sqrt_q31((q31_t) ((q31_t)sum / (int32_t) blockSize), pResult);     
}     
     
/**      
 * @} end of RMS group      
 */     
