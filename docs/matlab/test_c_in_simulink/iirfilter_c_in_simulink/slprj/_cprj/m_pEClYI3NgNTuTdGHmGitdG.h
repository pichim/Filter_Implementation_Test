#ifndef __pEClYI3NgNTuTdGHmGitdG_h__
#define __pEClYI3NgNTuTdGHmGitdG_h__

/* Include files */
#include "simstruc.h"
#include "rtwtypes.h"
#include "multiword_types.h"
#include "slexec_vm_zc_functions.h"
#include "slexec_vm_simstruct_bridge.h"
#include "sl_sfcn_cov/sl_sfcn_cov_bridge.h"

/* Type Definitions */
#ifndef typedef_InstanceStruct_pEClYI3NgNTuTdGHmGitdG
#define typedef_InstanceStruct_pEClYI3NgNTuTdGHmGitdG

typedef struct {
  SimStruct *S;
  void *emlrtRootTLSGlobal;
  real32_T *u0;
  real32_T *b_y0;
  IIRFilter_t *lowPass1;
} InstanceStruct_pEClYI3NgNTuTdGHmGitdG;

#endif                                 /* typedef_InstanceStruct_pEClYI3NgNTuTdGHmGitdG */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */

/* Function Definitions */
extern void method_dispatcher_pEClYI3NgNTuTdGHmGitdG(SimStruct *S, int_T method,
  void* data);

#endif
