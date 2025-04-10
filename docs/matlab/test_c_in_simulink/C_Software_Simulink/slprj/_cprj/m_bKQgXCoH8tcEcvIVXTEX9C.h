#ifndef __bKQgXCoH8tcEcvIVXTEX9C_h__
#define __bKQgXCoH8tcEcvIVXTEX9C_h__

/* Include files */
#include "simstruc.h"
#include "rtwtypes.h"
#include "multiword_types.h"
#include "slexec_vm_zc_functions.h"
#include "slexec_vm_simstruct_bridge.h"
#include "sl_sfcn_cov/sl_sfcn_cov_bridge.h"

/* Type Definitions */
#ifndef typedef_InstanceStruct_bKQgXCoH8tcEcvIVXTEX9C
#define typedef_InstanceStruct_bKQgXCoH8tcEcvIVXTEX9C

typedef struct {
  SimStruct *S;
  void *emlrtRootTLSGlobal;
  real32_T *u0;
  real32_T *b_y0;
  pt1filter *pt1;
} InstanceStruct_bKQgXCoH8tcEcvIVXTEX9C;

#endif                                 /* typedef_InstanceStruct_bKQgXCoH8tcEcvIVXTEX9C */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */

/* Function Definitions */
extern void method_dispatcher_bKQgXCoH8tcEcvIVXTEX9C(SimStruct *S, int_T method,
  void* data);

#endif
