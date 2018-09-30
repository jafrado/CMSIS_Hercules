/*-----------------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:        arm_lms_init_q31.c      
*      
* Description:  Q31 LMS filter initialization function.      
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
* ---------------------------------------------------------------------------*/     
#include "arm_math.h"     
     
/**      
 * @ingroup groupFilters      
 */     
     
/**      
 * @addtogroup LMS      
 * @{      
 */     
     
  /**      
   * @brief Initialization function for Q31 LMS filter.      
   * @param[in] *S points to an instance of the Q31 LMS filter structure.      
   * @param[in] numTaps  number of filter coefficients.      
   * @param[in] *pCoeffs points to coefficient buffer.      
   * @param[in] *pState points to state buffer.      
   * @param[in] mu step size that controls filter coefficient updates.      
   * @param[in] blockSize number of samples to process.      
   * @param[in] postShift bit shift applied to coefficients.      
   * @return none.      
 *      
 * \par Description:      
 * <code>pCoeffs</code> points to the array of filter coefficients stored in time reversed order:      
 * <pre>      
 *    {b[numTaps-1], b[numTaps-2], b[N-2], ..., b[1], b[0]}      
 * </pre>      
 * The initial filter coefficients serve as a starting point for the adaptive filter.      
 * <code>pState</code> points to an array of length <code>numTaps+blockSize-1</code>samples,      
 * where <code>blockSize</code> is the number of input samples processed by each call to      
 * <code>arm_lms_q31()</code>.      
 */     
     
void arm_lms_init_q31(     
  arm_lms_instance_q31 * S,     
  uint16_t numTaps,     
  q31_t * pCoeffs,     
  q31_t * pState,     
  q31_t mu,     
  uint32_t blockSize,     
  uint32_t postShift)     
{     
  /* Assign filter taps */     
  S->numTaps = numTaps;     
     
  /* Assign coefficient pointer */     
  S->pCoeffs = pCoeffs;     
     
  /* Clear state buffer and size is always blockSize + numTaps - 1 */     
  memset(pState, 0, ((uint32_t) numTaps + (blockSize - 1u)) * sizeof(q31_t));     
     
  /* Assign state pointer */     
  S->pState = pState;     
     
  /* Assign Step size value */     
  S->mu = mu;     
     
  /* Assign postShift value to be applied */     
  S->postShift = postShift;     
     
}     
     
/**      
 * @} end of LMS group      
 */     
