/* ----------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:        arm_fir_decimate_init_q31.c      
*      
* Description:  Initialization function for Q31 FIR Decimation filter.      
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
* ------------------------------------------------------------------- */     
#include "arm_math.h"     
     
/**      
 * @ingroup groupFilters      
 */     
     
/**      
 * @addtogroup FIR_decimate      
 * @{      
 */     
     
/**      
 * @brief  Initialization function for the Q31 FIR decimator.      
 * @param[in,out] *S points to an instance of the Q31 FIR decimator structure.      
 * @param[in] numTaps  number of coefficients in the filter.      
 * @param[in] M  decimation factor.      
 * @param[in] *pCoeffs points to the filter coefficients.      
 * @param[in] *pState points to the state buffer.      
 * @param[in] blockSize number of input samples to process per call.      
 * @return    The function returns ARM_MATH_SUCCESS if initialization was successful or ARM_MATH_LENGTH_ERROR if      
 * <code>blockSize</code> is not a multiple of <code>M</code>.      
 *      
 * <b>Description:</b>      
 * \par      
 * <code>pCoeffs</code> points to the array of filter coefficients stored in time reversed order:      
 * <pre>      
 *    {b[numTaps-1], b[numTaps-2], b[N-2], ..., b[1], b[0]}      
 * </pre>      
 * \par      
 * <code>pState</code> points to the array of state variables.      
 * <code>pState</code> is of length <code>numTaps+blockSize-1</code> words where <code>blockSize</code> is the number of input samples passed to <code>arm_fir_decimate_q31()</code>.      
 * <code>M</code> is the decimation factor.      
 */     
     
arm_status arm_fir_decimate_init_q31(     
  arm_fir_decimate_instance_q31 * S,     
  uint16_t numTaps,     
  uint8_t M,     
  q31_t * pCoeffs,     
  q31_t * pState,     
  uint32_t blockSize)     
{     
  arm_status status;     
     
  /* The size of the input block must be a multiple of the decimation factor */     
  if((blockSize % M) != 0u)     
  {     
    /* Set status as ARM_MATH_LENGTH_ERROR */     
    status = ARM_MATH_LENGTH_ERROR;     
  }     
  else     
  {     
    /* Assign filter taps */     
    S->numTaps = numTaps;     
     
    /* Assign coefficient pointer */     
    S->pCoeffs = pCoeffs;     
     
    /* Clear the state buffer.  The size is always (blockSize + numTaps - 1) */     
    memset(pState, 0, (numTaps + (blockSize - 1)) * sizeof(q31_t));     
     
    /* Assign state pointer */     
    S->pState = pState;     
     
    /* Assign Decimation factor */     
    S->M = M;     
     
    status = ARM_MATH_SUCCESS;     
  }     
     
  return (status);     
     
}     
     
/**      
 * @} end of FIR_decimate group      
 */     
