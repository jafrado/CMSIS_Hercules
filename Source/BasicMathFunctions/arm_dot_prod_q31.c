/* ----------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:		arm_dot_prod_q31.c      
*      
* Description:	Q31 dot product.      
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
* -------------------------------------------------------------------- */     
#include "arm_math.h"     
     
/**      
 * @ingroup groupMath      
 */     
     
/**      
 * @addtogroup dot_prod      
 * @{      
 */     
     
/**      
 * @brief Dot product of Q31 vectors.      
 * @param[in]       *pSrcA points to the first input vector      
 * @param[in]       *pSrcB points to the second input vector      
 * @param[in]       blockSize number of samples in each vector      
 * @param[out]      *result output result returned here      
 * @return none.      
 *      
 * <b>Scaling and Overflow Behavior:</b>      
 * \par      
 * The intermediate multiplications are in 1.31 x 1.31 = 2.62 format and these      
 * are truncated to 2.48 format by discarding the lower 14 bits.      
 * The 2.48 result is then added without saturation to a 64-bit accumulator in 16.48 format.      
 * There are 15 guard bits in the accumulator and there is no risk of overflow as long as      
 * the length of the vectors is less than 2^16 elements.      
 * The return result is in 16.48 format.      
 */     
     
void arm_dot_prod_q31(     
  q31_t * pSrcA,     
  q31_t * pSrcB,     
  uint32_t blockSize,     
  q63_t * result)     
{     
  q63_t sum = 0, sum1 = 0;                       /* Temporary result storage */     
  uint32_t blkCnt;                               /* loop counter */     
  q31_t inA1, inA2, inB1, inB2;					 /* Temporary variables to store input data */  
    
  /*loop Unrolling */     
  blkCnt = blockSize >> 3u;     
     
  /* First part of the processing with loop unrolling.  Compute 8 outputs at a time.      
   ** a second loop below computes the remaining 1 to 7 samples. */     
  while(blkCnt > 0u)     
  {     
    /* C = A[0]* B[0] + A[1]* B[1] + A[2]* B[2] + .....+ A[blockSize-1]* B[blockSize-1] */     
    /* Calculate dot product and then store the result in a temporary buffer. */   
  
	/* read input from sourceA buffer */  
	inA1 = *pSrcA;  
	/* read input from sourceB buffer */  
	inB1 = *pSrcB;  
	inA2 = *(pSrcA + 1);  
	inB2 = *(pSrcB + 1);  
  
	/* multiply and accumulate in 16.48 format */  
    sum += ((q63_t)inA1 * inB1) >> 14u;     
	sum1 += ((q63_t)inA2 * inB2) >> 14u;   
	    
	inA1 = *(pSrcA + 2);  
	inB1 = *(pSrcB + 2);  
	inA2 = *(pSrcA + 3);  
	inB2 = *(pSrcB + 3);  
	/* multiply and accumulate in 16.48 format */  
    sum += ((q63_t)inA1 * inB1) >> 14u;     
	sum1 += ((q63_t)inA2 * inB2) >> 14u;   
	    
	inA1 = *(pSrcA + 4);  
	inB1 = *(pSrcB + 4);  
	inA2 = *(pSrcA + 5);  
	inB2 = *(pSrcB + 5);  
 	/* multiply and accumulate in 16.48 format */  
    sum += ((q63_t)inA1 * inB1) >> 14u;     
	sum1 += ((q63_t)inA2 * inB2) >> 14u;  
	     
	inA1 = *(pSrcA + 6);  
	inB1 = *(pSrcB + 6);  
	inA2 = *(pSrcA + 7);  
	inB2 = *(pSrcB + 7);  
	/* multiply and accumulate in 16.48 format */  
    sum += ((q63_t)inA1 * inB1) >> 14u;     
	sum1 += ((q63_t)inA2 * inB2) >> 14u;   
	    
	/* increment sourceA pointer by 8 */  
	pSrcA += 8u;  
	/* increment sourceB pointer bhy 8 */  
	pSrcB += 8u;     
    
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
  sum = sum + sum1;  
  /* If the blockSize is not a multiple of 8, compute any remaining output samples here.      
   ** No loop unrolling is used. */     
  blkCnt = blockSize % 0x8u;     
     
  while(blkCnt > 0u)     
  {     
    /* C = A[0]* B[0] + A[1]* B[1] + A[2]* B[2] + .....+ A[blockSize-1]* B[blockSize-1] */     
    /* Calculate dot product and then store the result in a temporary buffer. */     
    sum += ((q63_t) * pSrcA++ * *pSrcB++) >> 14u;     
     
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
     
  /* Store the result in the destination buffer in 16.48 format */     
  *result = sum;     
}     
     
/**      
 * @} end of dot_prod group      
 */     
