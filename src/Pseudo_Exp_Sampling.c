/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Pseudo_Exp_Sampling.c
 *
 * Code generation for function 'Pseudo_Exp_Sampling'
 *
 */

/* Include files */
#include "Pseudo_Exp_Sampling.h"
#include "Pseudo_Exp_Sampling_emxutil.h"
#include "Pseudo_Exp_Sampling_types.h"
#include "colon.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>

/* Function Declarations */
static double rt_roundd_snf(double u);

/* Function Definitions */
static double rt_roundd_snf(double u)
{
  double y;
  if (fabs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = floor(u + 0.5);
    } else if (u > -0.5) {
      y = u * 0.0;
    } else {
      y = ceil(u - 0.5);
    }
  } else {
    y = u;
  }
  return y;
}

void Pseudo_Exp_Sampling(double Start, double End, double Step_Size,
                         double Sparseness, double Num_Exp,
                         emxArray_real_T *New_Data_Array)
{
  emxArray_boolean_T *x;
  emxArray_int32_T *ii;
  emxArray_real_T *BreakPoint;
  emxArray_real_T *Full_trace;
  emxArray_real_T *Index_trace;
  emxArray_real_T *Log_mat;
  emxArray_real_T *Time_Bkp;
  double Sampled_Num_Point;
  double b;
  double j;
  double *Full_trace_data;
  double *Index_trace_data;
  double *Log_mat_data;
  double *Time_Bkp_data;
  int b_i;
  int b_loop_ub;
  int i;
  int i1;
  int idx;
  int loop_ub;
  int nx;
  int *ii_data;
  boolean_T *x_data;
  /* codegen */
  /*  Start=0; End=2000; Step_Size=5;    % in fs */
  /*  Sparseness=0.2; */
  emxInit_real_T(&Full_trace, 2);
  Full_trace_data = Full_trace->data;
  if (rtIsNaN(Start) || rtIsNaN(Step_Size) || rtIsNaN(End)) {
    i = Full_trace->size[0] * Full_trace->size[1];
    Full_trace->size[0] = 1;
    Full_trace->size[1] = 1;
    emxEnsureCapacity_real_T(Full_trace, i);
    Full_trace_data = Full_trace->data;
    Full_trace_data[0] = rtNaN;
  } else if ((Step_Size == 0.0) || ((Start < End) && (Step_Size < 0.0)) ||
             ((End < Start) && (Step_Size > 0.0))) {
    Full_trace->size[0] = 1;
    Full_trace->size[1] = 0;
  } else if ((rtIsInf(Start) || rtIsInf(End)) &&
             (rtIsInf(Step_Size) || (Start == End))) {
    i = Full_trace->size[0] * Full_trace->size[1];
    Full_trace->size[0] = 1;
    Full_trace->size[1] = 1;
    emxEnsureCapacity_real_T(Full_trace, i);
    Full_trace_data = Full_trace->data;
    Full_trace_data[0] = rtNaN;
  } else if (rtIsInf(Step_Size)) {
    i = Full_trace->size[0] * Full_trace->size[1];
    Full_trace->size[0] = 1;
    Full_trace->size[1] = 1;
    emxEnsureCapacity_real_T(Full_trace, i);
    Full_trace_data = Full_trace->data;
    Full_trace_data[0] = Start;
  } else if ((floor(Start) == Start) && (floor(Step_Size) == Step_Size)) {
    i = Full_trace->size[0] * Full_trace->size[1];
    Full_trace->size[0] = 1;
    loop_ub = (int)((End - Start) / Step_Size);
    Full_trace->size[1] = loop_ub + 1;
    emxEnsureCapacity_real_T(Full_trace, i);
    Full_trace_data = Full_trace->data;
    for (i = 0; i <= loop_ub; i++) {
      Full_trace_data[i] = Start + Step_Size * (double)i;
    }
  } else {
    eml_float_colon(Start, Step_Size, End, Full_trace);
    Full_trace_data = Full_trace->data;
  }
  emxInit_real_T(&Index_trace, 2);
  Index_trace_data = Index_trace->data;
  if (Full_trace->size[1] < 1) {
    Index_trace->size[0] = 1;
    Index_trace->size[1] = 0;
  } else {
    i = Index_trace->size[0] * Index_trace->size[1];
    Index_trace->size[0] = 1;
    Index_trace->size[1] = Full_trace->size[1];
    emxEnsureCapacity_real_T(Index_trace, i);
    Index_trace_data = Index_trace->data;
    loop_ub = Full_trace->size[1] - 1;
    for (i = 0; i <= loop_ub; i++) {
      Index_trace_data[i] = (double)i + 1.0;
    }
  }
  nx = Index_trace->size[1];
  for (loop_ub = 0; loop_ub < nx; loop_ub++) {
    Index_trace_data[loop_ub] = log(Index_trace_data[loop_ub]);
  }
  emxInit_real_T(&Log_mat, 2);
  i = Log_mat->size[0] * Log_mat->size[1];
  Log_mat->size[0] = Index_trace->size[1];
  Log_mat->size[1] = 2;
  emxEnsureCapacity_real_T(Log_mat, i);
  Log_mat_data = Log_mat->data;
  loop_ub = Index_trace->size[1];
  for (i = 0; i < loop_ub; i++) {
    Log_mat_data[i] = Index_trace_data[i];
  }
  loop_ub = Full_trace->size[1];
  for (i = 0; i < loop_ub; i++) {
    Log_mat_data[i + Log_mat->size[0]] = Full_trace_data[i];
  }
  /* figure;plot (Log_mat(:,1),Log_mat(:,2),'.'); */
  if (rtIsNaN(Num_Exp)) {
    i = Index_trace->size[0] * Index_trace->size[1];
    Index_trace->size[0] = 1;
    Index_trace->size[1] = 1;
    emxEnsureCapacity_real_T(Index_trace, i);
    Index_trace_data = Index_trace->data;
    Index_trace_data[0] = rtNaN;
  } else if (Num_Exp < 1.0) {
    Index_trace->size[1] = 0;
  } else {
    i = Index_trace->size[0] * Index_trace->size[1];
    Index_trace->size[0] = 1;
    Index_trace->size[1] = (int)(Num_Exp - 1.0) + 1;
    emxEnsureCapacity_real_T(Index_trace, i);
    Index_trace_data = Index_trace->data;
    loop_ub = (int)(Num_Exp - 1.0);
    for (i = 0; i <= loop_ub; i++) {
      Index_trace_data[i] = (double)i + 1.0;
    }
  }
  b = Log_mat_data[Log_mat->size[0] - 1];
  i = Index_trace->size[0] * Index_trace->size[1];
  Index_trace->size[0] = 1;
  emxEnsureCapacity_real_T(Index_trace, i);
  Index_trace_data = Index_trace->data;
  loop_ub = Index_trace->size[1] - 1;
  for (i = 0; i <= loop_ub; i++) {
    Index_trace_data[i] = Index_trace_data[i] * b / Num_Exp;
  }
  nx = Index_trace->size[1];
  for (loop_ub = 0; loop_ub < nx; loop_ub++) {
    Index_trace_data[loop_ub] = rt_roundd_snf(Index_trace_data[loop_ub]);
  }
  i = (int)Num_Exp;
  emxInit_real_T(&Time_Bkp, 1);
  i1 = Time_Bkp->size[0];
  Time_Bkp->size[0] = (int)Num_Exp;
  emxEnsureCapacity_real_T(Time_Bkp, i1);
  Time_Bkp_data = Time_Bkp->data;
  if ((int)Num_Exp - 1 >= 0) {
    b_loop_ub = Log_mat->size[0];
  }
  emxInit_boolean_T(&x);
  emxInit_int32_T(&ii);
  for (b_i = 0; b_i < i; b_i++) {
    boolean_T exitg1;
    b = Index_trace_data[b_i];
    i1 = x->size[0];
    x->size[0] = Log_mat->size[0];
    emxEnsureCapacity_boolean_T(x, i1);
    x_data = x->data;
    for (i1 = 0; i1 < b_loop_ub; i1++) {
      x_data[i1] = (Log_mat_data[i1] < b);
    }
    nx = x->size[0];
    idx = 0;
    i1 = ii->size[0];
    ii->size[0] = x->size[0];
    emxEnsureCapacity_int32_T(ii, i1);
    ii_data = ii->data;
    loop_ub = 0;
    exitg1 = false;
    while ((!exitg1) && (loop_ub <= nx - 1)) {
      if (x_data[loop_ub]) {
        idx++;
        ii_data[idx - 1] = loop_ub + 1;
        if (idx >= nx) {
          exitg1 = true;
        } else {
          loop_ub++;
        }
      } else {
        loop_ub++;
      }
    }
    if (x->size[0] == 1) {
      if (idx == 0) {
        ii->size[0] = 0;
      }
    } else {
      i1 = ii->size[0];
      if (idx < 1) {
        ii->size[0] = 0;
      } else {
        ii->size[0] = idx;
      }
      emxEnsureCapacity_int32_T(ii, i1);
    }
    Time_Bkp_data[b_i] = Log_mat_data[(ii->size[0] + Log_mat->size[0]) - 1];
  }
  emxFree_int32_T(&ii);
  emxFree_boolean_T(&x);
  emxFree_real_T(&Log_mat);
  b = rt_roundd_snf((double)Full_trace->size[1] * Sparseness);
  emxFree_real_T(&Full_trace);
  Sampled_Num_Point = b / Num_Exp;
  /*  break into Num_Exp segments */
  loop_ub = (int)b;
  i1 = New_Data_Array->size[0];
  New_Data_Array->size[0] = (int)b;
  emxEnsureCapacity_real_T(New_Data_Array, i1);
  Full_trace_data = New_Data_Array->data;
  for (i1 = 0; i1 < loop_ub; i1++) {
    Full_trace_data[i1] = 0.0;
  }
  emxInit_real_T(&BreakPoint, 1);
  i1 = BreakPoint->size[0];
  BreakPoint->size[0] = Time_Bkp->size[0] + 1;
  emxEnsureCapacity_real_T(BreakPoint, i1);
  Log_mat_data = BreakPoint->data;
  loop_ub = Time_Bkp->size[0];
  for (i1 = 0; i1 <= loop_ub; i1++) {
    Log_mat_data[i1] = 0.0;
  }
  Log_mat_data[0] = Start;
  if (Time_Bkp->size[0] + 1 < 2) {
    i1 = -1;
    idx = -1;
  } else {
    i1 = 0;
    idx = Time_Bkp->size[0];
  }
  loop_ub = idx - i1;
  for (idx = 0; idx < loop_ub; idx++) {
    Log_mat_data[(i1 + idx) + 1] = Time_Bkp_data[idx];
  }
  emxFree_real_T(&Time_Bkp);
  j = 1.0;
  for (b_i = 0; b_i < i; b_i++) {
    double d;
    double dt;
    b = Log_mat_data[b_i + 1];
    dt = (b - Log_mat_data[b_i]) / Sampled_Num_Point;
    d = rt_roundd_snf(((double)b_i + 1.0) * Sampled_Num_Point);
    if (j > d) {
      i1 = 0;
      idx = 0;
    } else {
      i1 = (int)j - 1;
      idx = (int)d;
    }
    b -= dt;
    if (rtIsNaN(Log_mat_data[b_i]) || rtIsNaN(dt) || rtIsNaN(b)) {
      nx = Index_trace->size[0] * Index_trace->size[1];
      Index_trace->size[0] = 1;
      Index_trace->size[1] = 1;
      emxEnsureCapacity_real_T(Index_trace, nx);
      Index_trace_data = Index_trace->data;
      Index_trace_data[0] = rtNaN;
    } else if ((dt == 0.0) || ((Log_mat_data[b_i] < b) && (dt < 0.0)) ||
               ((b < Log_mat_data[b_i]) && (dt > 0.0))) {
      Index_trace->size[0] = 1;
      Index_trace->size[1] = 0;
    } else if ((rtIsInf(Log_mat_data[b_i]) || rtIsInf(b)) &&
               (rtIsInf(dt) || (Log_mat_data[b_i] == b))) {
      nx = Index_trace->size[0] * Index_trace->size[1];
      Index_trace->size[0] = 1;
      Index_trace->size[1] = 1;
      emxEnsureCapacity_real_T(Index_trace, nx);
      Index_trace_data = Index_trace->data;
      Index_trace_data[0] = rtNaN;
    } else if (rtIsInf(dt)) {
      nx = Index_trace->size[0] * Index_trace->size[1];
      Index_trace->size[0] = 1;
      Index_trace->size[1] = 1;
      emxEnsureCapacity_real_T(Index_trace, nx);
      Index_trace_data = Index_trace->data;
      Index_trace_data[0] = Log_mat_data[b_i];
    } else if ((floor(Log_mat_data[b_i]) == Log_mat_data[b_i]) &&
               (floor(dt) == dt)) {
      nx = Index_trace->size[0] * Index_trace->size[1];
      Index_trace->size[0] = 1;
      loop_ub = (int)((b - Log_mat_data[b_i]) / dt);
      Index_trace->size[1] = loop_ub + 1;
      emxEnsureCapacity_real_T(Index_trace, nx);
      Index_trace_data = Index_trace->data;
      for (nx = 0; nx <= loop_ub; nx++) {
        Index_trace_data[nx] = Log_mat_data[b_i] + dt * (double)nx;
      }
    } else {
      eml_float_colon(Log_mat_data[b_i], dt, b, Index_trace);
      Index_trace_data = Index_trace->data;
    }
    loop_ub = idx - i1;
    for (idx = 0; idx < loop_ub; idx++) {
      Full_trace_data[i1 + idx] = Index_trace_data[idx];
    }
    j += Sampled_Num_Point;
  }
  emxFree_real_T(&BreakPoint);
  emxFree_real_T(&Index_trace);
}

void Pseudo_Exp_Sampling_wrapper(double Start, double End, double Step_Size,
                                 double Sparseness, double Num_Exp,
                                 double *New_Data_Array, int total_size_)
{
  emxArray_real_T *New_Data_Array_;
  emxInit_real_T(&New_Data_Array_, 1);
  Pseudo_Exp_Sampling(Start, End, Step_Size, Sparseness, Num_Exp,
                      New_Data_Array_);
  // Copy the data from the emxArray to the output pointer
  memcpy(New_Data_Array, New_Data_Array_->data,
         New_Data_Array_->size[0] * sizeof(double));
  emxFree_real_T(&New_Data_Array_);
}

/* End of code generation (Pseudo_Exp_Sampling.c) */
