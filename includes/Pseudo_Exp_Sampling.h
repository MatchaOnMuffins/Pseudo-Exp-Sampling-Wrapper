/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Pseudo_Exp_Sampling.h
 *
 * Code generation for function 'Pseudo_Exp_Sampling'
 *
 */

#ifndef PSEUDO_EXP_SAMPLING_H
#define PSEUDO_EXP_SAMPLING_H

/* Include files */
#include "Pseudo_Exp_Sampling_types.h"
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
extern void Pseudo_Exp_Sampling(double Start, double End, double Step_Size,
                                double Sparseness, double Num_Exp,
                                emxArray_real_T *New_Data_Array);

// wrapper for the function
extern void Pseudo_Exp_Sampling_wrapper(double Start, double End, double Step_Size,
                                double Sparseness, double Num_Exp,
                                double *New_Data_Array, int total_size_);

#ifdef __cplusplus
}
#endif

#endif
/* End of code generation (Pseudo_Exp_Sampling.h) */
