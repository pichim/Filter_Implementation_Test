/* Include files */

#include "modelInterface.h"
#include "m_pEClYI3NgNTuTdGHmGitdG.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
static void cgxe_mdl_start(InstanceStruct_pEClYI3NgNTuTdGHmGitdG *moduleInstance);
static void cgxe_mdl_initialize(InstanceStruct_pEClYI3NgNTuTdGHmGitdG
  *moduleInstance);
static void cgxe_mdl_outputs(InstanceStruct_pEClYI3NgNTuTdGHmGitdG
  *moduleInstance);
static void cgxe_mdl_update(InstanceStruct_pEClYI3NgNTuTdGHmGitdG
  *moduleInstance);
static void cgxe_mdl_derivative(InstanceStruct_pEClYI3NgNTuTdGHmGitdG
  *moduleInstance);
static void cgxe_mdl_enable(InstanceStruct_pEClYI3NgNTuTdGHmGitdG
  *moduleInstance);
static void cgxe_mdl_disable(InstanceStruct_pEClYI3NgNTuTdGHmGitdG
  *moduleInstance);
static void cgxe_mdl_terminate(InstanceStruct_pEClYI3NgNTuTdGHmGitdG
  *moduleInstance);
static const mxArray *emlrt_marshallOut(InstanceStruct_pEClYI3NgNTuTdGHmGitdG
  *moduleInstance);
static const mxArray *b_emlrt_marshallOut(const real32_T u[2]);
static const mxArray *cgxe_mdl_get_sim_state
  (InstanceStruct_pEClYI3NgNTuTdGHmGitdG *moduleInstance);
static void emlrt_marshallIn(InstanceStruct_pEClYI3NgNTuTdGHmGitdG
  *moduleInstance, const mxArray *u);
static real32_T b_emlrt_marshallIn(InstanceStruct_pEClYI3NgNTuTdGHmGitdG
  *moduleInstance, const mxArray *nullptr, const char_T *identifier);
static real32_T c_emlrt_marshallIn(InstanceStruct_pEClYI3NgNTuTdGHmGitdG
  *moduleInstance, const mxArray *u, const emlrtMsgIdentifier *parentId);
static IIRFilter_t d_emlrt_marshallIn(InstanceStruct_pEClYI3NgNTuTdGHmGitdG
  *moduleInstance, const mxArray *nullptr, const char_T *identifier);
static IIRFilter_t e_emlrt_marshallIn(InstanceStruct_pEClYI3NgNTuTdGHmGitdG
  *moduleInstance, const mxArray *u, const emlrtMsgIdentifier *parentId);
static uint32_T f_emlrt_marshallIn(InstanceStruct_pEClYI3NgNTuTdGHmGitdG
  *moduleInstance, const mxArray *u, const emlrtMsgIdentifier *parentId);
static void g_emlrt_marshallIn(InstanceStruct_pEClYI3NgNTuTdGHmGitdG
  *moduleInstance, const mxArray *u, const emlrtMsgIdentifier *parentId,
  real32_T y[2]);
static void h_emlrt_marshallIn(InstanceStruct_pEClYI3NgNTuTdGHmGitdG
  *moduleInstance, const mxArray *u, const emlrtMsgIdentifier *parentId,
  real32_T y[3]);
static void cgxe_mdl_set_sim_state(InstanceStruct_pEClYI3NgNTuTdGHmGitdG
  *moduleInstance, const mxArray *st);
static real32_T i_emlrt_marshallIn(InstanceStruct_pEClYI3NgNTuTdGHmGitdG
  *moduleInstance, const mxArray *src, const emlrtMsgIdentifier *msgId);
static uint32_T j_emlrt_marshallIn(InstanceStruct_pEClYI3NgNTuTdGHmGitdG
  *moduleInstance, const mxArray *src, const emlrtMsgIdentifier *msgId);
static void k_emlrt_marshallIn(InstanceStruct_pEClYI3NgNTuTdGHmGitdG
  *moduleInstance, const mxArray *src, const emlrtMsgIdentifier *msgId, real32_T
  ret[2]);
static void l_emlrt_marshallIn(InstanceStruct_pEClYI3NgNTuTdGHmGitdG
  *moduleInstance, const mxArray *src, const emlrtMsgIdentifier *msgId, real32_T
  ret[3]);
static void init_simulink_io_address(InstanceStruct_pEClYI3NgNTuTdGHmGitdG
  *moduleInstance);

/* Function Definitions */
static void cgxe_mdl_start(InstanceStruct_pEClYI3NgNTuTdGHmGitdG *moduleInstance)
{
  int32_T i;
  init_simulink_io_address(moduleInstance);
  *(uint32_T *)&((char_T *)moduleInstance->lowPass1)[0] = 0U;
  for (i = 0; i < 2; i++) {
    (*(real32_T (*)[2])&((char_T *)moduleInstance->lowPass1)[4])[i] = 0.0F;
  }

  for (i = 0; i < 3; i++) {
    (*(real32_T (*)[3])&((char_T *)moduleInstance->lowPass1)[12])[i] = 0.0F;
  }

  for (i = 0; i < 2; i++) {
    (*(real32_T (*)[2])&((char_T *)moduleInstance->lowPass1)[24])[i] = 0.0F;
  }

  *moduleInstance->b_y0 = 0.0F;
}

static void cgxe_mdl_initialize(InstanceStruct_pEClYI3NgNTuTdGHmGitdG
  *moduleInstance)
{
  IIRFilter_t r;
  IIRFilter_t r1;
  int32_T i;
  real32_T *Ts;
  real32_T *fcut;
  Ts = (real32_T *)cgxertGetRunTimeParamInfoData(moduleInstance->S, 0);
  fcut = (real32_T *)cgxertGetRunTimeParamInfoData(moduleInstance->S, 1);
  r.order = *(uint32_T *)&((char_T *)moduleInstance->lowPass1)[0];
  for (i = 0; i < 2; i++) {
    r.A[i] = (*(real32_T (*)[2])&((char_T *)moduleInstance->lowPass1)[4])[i];
  }

  for (i = 0; i < 3; i++) {
    r.B[i] = (*(real32_T (*)[3])&((char_T *)moduleInstance->lowPass1)[12])[i];
  }

  for (i = 0; i < 2; i++) {
    r.w[i] = (*(real32_T (*)[2])&((char_T *)moduleInstance->lowPass1)[24])[i];
  }

  lowPass1Init_usV23h6UlpYViYoInLiPJG(&r, *fcut, *Ts);
  *(uint32_T *)&((char_T *)moduleInstance->lowPass1)[0] = r.order;
  for (i = 0; i < 2; i++) {
    (*(real32_T (*)[2])&((char_T *)moduleInstance->lowPass1)[4])[i] = r.A[i];
  }

  for (i = 0; i < 3; i++) {
    (*(real32_T (*)[3])&((char_T *)moduleInstance->lowPass1)[12])[i] = r.B[i];
  }

  for (i = 0; i < 2; i++) {
    (*(real32_T (*)[2])&((char_T *)moduleInstance->lowPass1)[24])[i] = r.w[i];
  }

  r1.order = *(uint32_T *)&((char_T *)moduleInstance->lowPass1)[0];
  for (i = 0; i < 2; i++) {
    r1.A[i] = (*(real32_T (*)[2])&((char_T *)moduleInstance->lowPass1)[4])[i];
  }

  for (i = 0; i < 3; i++) {
    r1.B[i] = (*(real32_T (*)[3])&((char_T *)moduleInstance->lowPass1)[12])[i];
  }

  for (i = 0; i < 2; i++) {
    r1.w[i] = (*(real32_T (*)[2])&((char_T *)moduleInstance->lowPass1)[24])[i];
  }

  iirFilterReset_usV23h6UlpYViYoInLiPJG(&r1, 0.0F);
  *(uint32_T *)&((char_T *)moduleInstance->lowPass1)[0] = r1.order;
  for (i = 0; i < 2; i++) {
    (*(real32_T (*)[2])&((char_T *)moduleInstance->lowPass1)[4])[i] = r1.A[i];
  }

  for (i = 0; i < 3; i++) {
    (*(real32_T (*)[3])&((char_T *)moduleInstance->lowPass1)[12])[i] = r1.B[i];
  }

  for (i = 0; i < 2; i++) {
    (*(real32_T (*)[2])&((char_T *)moduleInstance->lowPass1)[24])[i] = r1.w[i];
  }
}

static void cgxe_mdl_outputs(InstanceStruct_pEClYI3NgNTuTdGHmGitdG
  *moduleInstance)
{
  IIRFilter_t r;
  int32_T i;
  r.order = *(uint32_T *)&((char_T *)moduleInstance->lowPass1)[0];
  for (i = 0; i < 2; i++) {
    r.A[i] = (*(real32_T (*)[2])&((char_T *)moduleInstance->lowPass1)[4])[i];
  }

  for (i = 0; i < 3; i++) {
    r.B[i] = (*(real32_T (*)[3])&((char_T *)moduleInstance->lowPass1)[12])[i];
  }

  for (i = 0; i < 2; i++) {
    r.w[i] = (*(real32_T (*)[2])&((char_T *)moduleInstance->lowPass1)[24])[i];
  }

  *moduleInstance->b_y0 = iirFilterApply_usV23h6UlpYViYoInLiPJG(&r,
    *moduleInstance->u0);
  *(uint32_T *)&((char_T *)moduleInstance->lowPass1)[0] = r.order;
  for (i = 0; i < 2; i++) {
    (*(real32_T (*)[2])&((char_T *)moduleInstance->lowPass1)[4])[i] = r.A[i];
  }

  for (i = 0; i < 3; i++) {
    (*(real32_T (*)[3])&((char_T *)moduleInstance->lowPass1)[12])[i] = r.B[i];
  }

  for (i = 0; i < 2; i++) {
    (*(real32_T (*)[2])&((char_T *)moduleInstance->lowPass1)[24])[i] = r.w[i];
  }
}

static void cgxe_mdl_update(InstanceStruct_pEClYI3NgNTuTdGHmGitdG
  *moduleInstance)
{
  (void)moduleInstance;
}

static void cgxe_mdl_derivative(InstanceStruct_pEClYI3NgNTuTdGHmGitdG
  *moduleInstance)
{
  (void)moduleInstance;
}

static void cgxe_mdl_enable(InstanceStruct_pEClYI3NgNTuTdGHmGitdG
  *moduleInstance)
{
  (void)moduleInstance;
}

static void cgxe_mdl_disable(InstanceStruct_pEClYI3NgNTuTdGHmGitdG
  *moduleInstance)
{
  (void)moduleInstance;
}

static void cgxe_mdl_terminate(InstanceStruct_pEClYI3NgNTuTdGHmGitdG
  *moduleInstance)
{
  (void)moduleInstance;
}

static const mxArray *emlrt_marshallOut(InstanceStruct_pEClYI3NgNTuTdGHmGitdG
  *moduleInstance)
{
  static const int32_T iv[1] = { 3 };

  static const char_T *sv[4] = { "order", "A", "B", "w" };

  const mxArray *b_y;
  const mxArray *c_y;
  const mxArray *d_y;
  const mxArray *e_y;
  const mxArray *m;
  const mxArray *y;
  int32_T b_i;
  int32_T i;
  real32_T u[3];
  real32_T *pData;
  y = NULL;
  emlrtAssign(&y, emlrtCreateCellMatrix(2, 1));
  b_y = NULL;
  m = emlrtCreateNumericMatrix(1, 1, mxSINGLE_CLASS, mxREAL);
  *(real32_T *)emlrtMxGetData(m) = *moduleInstance->b_y0;
  emlrtAssign(&b_y, m);
  emlrtSetCell(y, 0, b_y);
  c_y = NULL;
  emlrtAssign(&c_y, emlrtCreateStructMatrix(1, 1, 4, (const char_T **)&sv[0]));
  d_y = NULL;
  m = emlrtCreateNumericMatrix(1, 1, mxUINT32_CLASS, mxREAL);
  *(uint32_T *)emlrtMxGetData(m) = *(uint32_T *)&((char_T *)
    moduleInstance->lowPass1)[0];
  emlrtAssign(&d_y, m);
  emlrtSetFieldR2017b(c_y, 0, "order", d_y, 0);
  emlrtSetFieldR2017b(c_y, 0, "A", b_emlrt_marshallOut(*(real32_T (*)[2])&
    ((char_T *)moduleInstance->lowPass1)[4]), 1);
  for (i = 0; i < 3; i++) {
    u[i] = (*(real32_T (*)[3])&((char_T *)moduleInstance->lowPass1)[12])[i];
  }

  e_y = NULL;
  m = emlrtCreateNumericArray(1, (const void *)&iv[0], mxSINGLE_CLASS, mxREAL);
  pData = (real32_T *)emlrtMxGetData(m);
  b_i = 0;
  for (i = 0; i < 3; i++) {
    pData[b_i] = u[i];
    b_i++;
  }

  emlrtAssign(&e_y, m);
  emlrtSetFieldR2017b(c_y, 0, "B", e_y, 2);
  emlrtSetFieldR2017b(c_y, 0, "w", b_emlrt_marshallOut(*(real32_T (*)[2])&
    ((char_T *)moduleInstance->lowPass1)[24]), 3);
  emlrtSetCell(y, 1, c_y);
  return y;
}

static const mxArray *b_emlrt_marshallOut(const real32_T u[2])
{
  static const int32_T iv[1] = { 2 };

  const mxArray *m;
  const mxArray *y;
  int32_T b_i;
  int32_T i;
  real32_T *pData;
  y = NULL;
  m = emlrtCreateNumericArray(1, (const void *)&iv[0], mxSINGLE_CLASS, mxREAL);
  pData = (real32_T *)emlrtMxGetData(m);
  i = 0;
  for (b_i = 0; b_i < 2; b_i++) {
    pData[i] = u[b_i];
    i++;
  }

  emlrtAssign(&y, m);
  return y;
}

static const mxArray *cgxe_mdl_get_sim_state
  (InstanceStruct_pEClYI3NgNTuTdGHmGitdG *moduleInstance)
{
  const mxArray *st;
  st = NULL;
  emlrtAssign(&st, emlrt_marshallOut(moduleInstance));
  return st;
}

static void emlrt_marshallIn(InstanceStruct_pEClYI3NgNTuTdGHmGitdG
  *moduleInstance, const mxArray *u)
{
  IIRFilter_t r;
  emlrtMsgIdentifier thisId;
  int32_T i;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  thisId.fIdentifier = "y0";
  *moduleInstance->b_y0 = b_emlrt_marshallIn(moduleInstance, emlrtAlias
    (emlrtGetCell(moduleInstance->emlrtRootTLSGlobal, &thisId, u, 0)), "y0");
  thisId.fIdentifier = "lowPass1";
  r = d_emlrt_marshallIn(moduleInstance, emlrtAlias(emlrtGetCell
    (moduleInstance->emlrtRootTLSGlobal, &thisId, u, 1)), "lowPass1");
  *(uint32_T *)&((char_T *)moduleInstance->lowPass1)[0] = r.order;
  for (i = 0; i < 2; i++) {
    (*(real32_T (*)[2])&((char_T *)moduleInstance->lowPass1)[4])[i] = r.A[i];
  }

  for (i = 0; i < 3; i++) {
    (*(real32_T (*)[3])&((char_T *)moduleInstance->lowPass1)[12])[i] = r.B[i];
  }

  for (i = 0; i < 2; i++) {
    (*(real32_T (*)[2])&((char_T *)moduleInstance->lowPass1)[24])[i] = r.w[i];
  }

  emlrtDestroyArray(&u);
}

static real32_T b_emlrt_marshallIn(InstanceStruct_pEClYI3NgNTuTdGHmGitdG
  *moduleInstance, const mxArray *nullptr, const char_T *identifier)
{
  emlrtMsgIdentifier thisId;
  real32_T y;
  thisId.fIdentifier = (const char_T *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = c_emlrt_marshallIn(moduleInstance, emlrtAlias(nullptr), &thisId);
  emlrtDestroyArray(&nullptr);
  return y;
}

static real32_T c_emlrt_marshallIn(InstanceStruct_pEClYI3NgNTuTdGHmGitdG
  *moduleInstance, const mxArray *u, const emlrtMsgIdentifier *parentId)
{
  real32_T y;
  y = i_emlrt_marshallIn(moduleInstance, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static IIRFilter_t d_emlrt_marshallIn(InstanceStruct_pEClYI3NgNTuTdGHmGitdG
  *moduleInstance, const mxArray *nullptr, const char_T *identifier)
{
  IIRFilter_t y;
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char_T *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = e_emlrt_marshallIn(moduleInstance, emlrtAlias(nullptr), &thisId);
  emlrtDestroyArray(&nullptr);
  return y;
}

static IIRFilter_t e_emlrt_marshallIn(InstanceStruct_pEClYI3NgNTuTdGHmGitdG
  *moduleInstance, const mxArray *u, const emlrtMsgIdentifier *parentId)
{
  static const int32_T dims = 0;
  static const char_T *fieldNames[4] = { "order", "A", "B", "w" };

  IIRFilter_t y;
  emlrtMsgIdentifier thisId;
  thisId.fParent = parentId;
  thisId.bParentIsCell = false;
  emlrtCheckStructR2012b(moduleInstance->emlrtRootTLSGlobal, parentId, u, 4, (
    const char_T **)&fieldNames[0], 0U, (const void *)&dims);
  thisId.fIdentifier = "order";
  y.order = f_emlrt_marshallIn(moduleInstance, emlrtAlias(emlrtGetFieldR2017b
    (moduleInstance->emlrtRootTLSGlobal, u, 0, 0, "order")), &thisId);
  thisId.fIdentifier = "A";
  g_emlrt_marshallIn(moduleInstance, emlrtAlias(emlrtGetFieldR2017b
    (moduleInstance->emlrtRootTLSGlobal, u, 0, 1, "A")), &thisId, y.A);
  thisId.fIdentifier = "B";
  h_emlrt_marshallIn(moduleInstance, emlrtAlias(emlrtGetFieldR2017b
    (moduleInstance->emlrtRootTLSGlobal, u, 0, 2, "B")), &thisId, y.B);
  thisId.fIdentifier = "w";
  g_emlrt_marshallIn(moduleInstance, emlrtAlias(emlrtGetFieldR2017b
    (moduleInstance->emlrtRootTLSGlobal, u, 0, 3, "w")), &thisId, y.w);
  emlrtDestroyArray(&u);
  return y;
}

static uint32_T f_emlrt_marshallIn(InstanceStruct_pEClYI3NgNTuTdGHmGitdG
  *moduleInstance, const mxArray *u, const emlrtMsgIdentifier *parentId)
{
  uint32_T y;
  y = j_emlrt_marshallIn(moduleInstance, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static void g_emlrt_marshallIn(InstanceStruct_pEClYI3NgNTuTdGHmGitdG
  *moduleInstance, const mxArray *u, const emlrtMsgIdentifier *parentId,
  real32_T y[2])
{
  k_emlrt_marshallIn(moduleInstance, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static void h_emlrt_marshallIn(InstanceStruct_pEClYI3NgNTuTdGHmGitdG
  *moduleInstance, const mxArray *u, const emlrtMsgIdentifier *parentId,
  real32_T y[3])
{
  l_emlrt_marshallIn(moduleInstance, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static void cgxe_mdl_set_sim_state(InstanceStruct_pEClYI3NgNTuTdGHmGitdG
  *moduleInstance, const mxArray *st)
{
  emlrt_marshallIn(moduleInstance, emlrtAlias(st));
  emlrtDestroyArray(&st);
}

static real32_T i_emlrt_marshallIn(InstanceStruct_pEClYI3NgNTuTdGHmGitdG
  *moduleInstance, const mxArray *src, const emlrtMsgIdentifier *msgId)
{
  static const int32_T dims = 0;
  real32_T ret;
  emlrtCheckBuiltInR2012b(moduleInstance->emlrtRootTLSGlobal, msgId, src,
    "single|double", false, 0U, (const void *)&dims);
  emlrtImportArrayR2015b(moduleInstance->emlrtRootTLSGlobal, src, &ret, 4, false);
  emlrtDestroyArray(&src);
  return ret;
}

static uint32_T j_emlrt_marshallIn(InstanceStruct_pEClYI3NgNTuTdGHmGitdG
  *moduleInstance, const mxArray *src, const emlrtMsgIdentifier *msgId)
{
  static const int32_T dims = 0;
  uint32_T ret;
  emlrtCheckBuiltInR2012b(moduleInstance->emlrtRootTLSGlobal, msgId, src,
    "uint32", false, 0U, (const void *)&dims);
  ret = *(uint32_T *)emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

static void k_emlrt_marshallIn(InstanceStruct_pEClYI3NgNTuTdGHmGitdG
  *moduleInstance, const mxArray *src, const emlrtMsgIdentifier *msgId, real32_T
  ret[2])
{
  static const int32_T dims[1] = { 2 };

  emlrtCheckBuiltInR2012b(moduleInstance->emlrtRootTLSGlobal, msgId, src,
    "single|double", false, 1U, (const void *)&dims[0]);
  emlrtImportArrayR2015b(moduleInstance->emlrtRootTLSGlobal, src, &ret[0], 4,
    false);
  emlrtDestroyArray(&src);
}

static void l_emlrt_marshallIn(InstanceStruct_pEClYI3NgNTuTdGHmGitdG
  *moduleInstance, const mxArray *src, const emlrtMsgIdentifier *msgId, real32_T
  ret[3])
{
  static const int32_T dims[1] = { 3 };

  emlrtCheckBuiltInR2012b(moduleInstance->emlrtRootTLSGlobal, msgId, src,
    "single|double", false, 1U, (const void *)&dims[0]);
  emlrtImportArrayR2015b(moduleInstance->emlrtRootTLSGlobal, src, &ret[0], 4,
    false);
  emlrtDestroyArray(&src);
}

static void init_simulink_io_address(InstanceStruct_pEClYI3NgNTuTdGHmGitdG
  *moduleInstance)
{
  moduleInstance->emlrtRootTLSGlobal = (void *)cgxertGetEMLRTCtx
    (moduleInstance->S);
  moduleInstance->u0 = (real32_T *)cgxertGetInputPortSignal(moduleInstance->S, 0);
  moduleInstance->b_y0 = (real32_T *)cgxertGetOutputPortSignal(moduleInstance->S,
    0);
  moduleInstance->lowPass1 = (IIRFilter_t *)cgxertGetDWork(moduleInstance->S, 0);
}

/* CGXE Glue Code */
static void mdlOutputs_pEClYI3NgNTuTdGHmGitdG(SimStruct *S, int_T tid)
{
  InstanceStruct_pEClYI3NgNTuTdGHmGitdG *moduleInstance =
    (InstanceStruct_pEClYI3NgNTuTdGHmGitdG *)cgxertGetRuntimeInstance(S);
  cgxe_mdl_outputs(moduleInstance);
}

static void mdlInitialize_pEClYI3NgNTuTdGHmGitdG(SimStruct *S)
{
  InstanceStruct_pEClYI3NgNTuTdGHmGitdG *moduleInstance =
    (InstanceStruct_pEClYI3NgNTuTdGHmGitdG *)cgxertGetRuntimeInstance(S);
  cgxe_mdl_initialize(moduleInstance);
}

static void mdlUpdate_pEClYI3NgNTuTdGHmGitdG(SimStruct *S, int_T tid)
{
  InstanceStruct_pEClYI3NgNTuTdGHmGitdG *moduleInstance =
    (InstanceStruct_pEClYI3NgNTuTdGHmGitdG *)cgxertGetRuntimeInstance(S);
  cgxe_mdl_update(moduleInstance);
}

static void mdlDerivatives_pEClYI3NgNTuTdGHmGitdG(SimStruct *S)
{
  InstanceStruct_pEClYI3NgNTuTdGHmGitdG *moduleInstance =
    (InstanceStruct_pEClYI3NgNTuTdGHmGitdG *)cgxertGetRuntimeInstance(S);
  cgxe_mdl_derivative(moduleInstance);
}

static mxArray* getSimState_pEClYI3NgNTuTdGHmGitdG(SimStruct *S)
{
  mxArray* mxSS;
  InstanceStruct_pEClYI3NgNTuTdGHmGitdG *moduleInstance =
    (InstanceStruct_pEClYI3NgNTuTdGHmGitdG *)cgxertGetRuntimeInstance(S);
  mxSS = (mxArray *) cgxe_mdl_get_sim_state(moduleInstance);
  return mxSS;
}

static void setSimState_pEClYI3NgNTuTdGHmGitdG(SimStruct *S, const mxArray *ss)
{
  InstanceStruct_pEClYI3NgNTuTdGHmGitdG *moduleInstance =
    (InstanceStruct_pEClYI3NgNTuTdGHmGitdG *)cgxertGetRuntimeInstance(S);
  cgxe_mdl_set_sim_state(moduleInstance, emlrtAlias(ss));
}

static void mdlTerminate_pEClYI3NgNTuTdGHmGitdG(SimStruct *S)
{
  InstanceStruct_pEClYI3NgNTuTdGHmGitdG *moduleInstance =
    (InstanceStruct_pEClYI3NgNTuTdGHmGitdG *)cgxertGetRuntimeInstance(S);
  cgxe_mdl_terminate(moduleInstance);
  free((void *)moduleInstance);
}

static void mdlEnable_pEClYI3NgNTuTdGHmGitdG(SimStruct *S)
{
  InstanceStruct_pEClYI3NgNTuTdGHmGitdG *moduleInstance =
    (InstanceStruct_pEClYI3NgNTuTdGHmGitdG *)cgxertGetRuntimeInstance(S);
  cgxe_mdl_enable(moduleInstance);
}

static void mdlDisable_pEClYI3NgNTuTdGHmGitdG(SimStruct *S)
{
  InstanceStruct_pEClYI3NgNTuTdGHmGitdG *moduleInstance =
    (InstanceStruct_pEClYI3NgNTuTdGHmGitdG *)cgxertGetRuntimeInstance(S);
  cgxe_mdl_disable(moduleInstance);
}

static void mdlStart_pEClYI3NgNTuTdGHmGitdG(SimStruct *S)
{
  InstanceStruct_pEClYI3NgNTuTdGHmGitdG *moduleInstance =
    (InstanceStruct_pEClYI3NgNTuTdGHmGitdG *)calloc(1, sizeof
    (InstanceStruct_pEClYI3NgNTuTdGHmGitdG));
  moduleInstance->S = S;
  cgxertSetRuntimeInstance(S, (void *)moduleInstance);
  ssSetmdlOutputs(S, mdlOutputs_pEClYI3NgNTuTdGHmGitdG);
  ssSetmdlInitializeConditions(S, mdlInitialize_pEClYI3NgNTuTdGHmGitdG);
  ssSetmdlUpdate(S, mdlUpdate_pEClYI3NgNTuTdGHmGitdG);
  ssSetmdlDerivatives(S, mdlDerivatives_pEClYI3NgNTuTdGHmGitdG);
  ssSetmdlTerminate(S, mdlTerminate_pEClYI3NgNTuTdGHmGitdG);
  ssSetmdlEnable(S, mdlEnable_pEClYI3NgNTuTdGHmGitdG);
  ssSetmdlDisable(S, mdlDisable_pEClYI3NgNTuTdGHmGitdG);
  cgxe_mdl_start(moduleInstance);

  {
    uint_T options = ssGetOptions(S);
    options |= SS_OPTION_RUNTIME_EXCEPTION_FREE_CODE;
    ssSetOptions(S, options);
  }
}

static void mdlProcessParameters_pEClYI3NgNTuTdGHmGitdG(SimStruct *S)
{
}

void method_dispatcher_pEClYI3NgNTuTdGHmGitdG(SimStruct *S, int_T method, void
  *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_pEClYI3NgNTuTdGHmGitdG(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_pEClYI3NgNTuTdGHmGitdG(S);
    break;

   case SS_CALL_MDL_GET_SIM_STATE:
    *((mxArray**) data) = getSimState_pEClYI3NgNTuTdGHmGitdG(S);
    break;

   case SS_CALL_MDL_SET_SIM_STATE:
    setSimState_pEClYI3NgNTuTdGHmGitdG(S, (const mxArray *) data);
    break;

   default:
    /* Unhandled method */
    /*
       sf_mex_error_message("Stateflow Internal Error:\n"
       "Error calling method dispatcher for module: pEClYI3NgNTuTdGHmGitdG.\n"
       "Can't handle method %d.\n", method);
     */
    break;
  }
}

mxArray *cgxe_pEClYI3NgNTuTdGHmGitdG_BuildInfoUpdate(void)
{
  mxArray * mxBIArgs;
  mxArray * elem_1;
  mxArray * elem_2;
  mxArray * elem_3;
  double * pointer;
  mxBIArgs = mxCreateCellMatrix(1,3);
  elem_1 = mxCreateDoubleMatrix(0,0, mxREAL);
  pointer = mxGetPr(elem_1);
  mxSetCell(mxBIArgs,0,elem_1);
  elem_2 = mxCreateDoubleMatrix(0,0, mxREAL);
  pointer = mxGetPr(elem_2);
  mxSetCell(mxBIArgs,1,elem_2);
  elem_3 = mxCreateCellMatrix(1,0);
  mxSetCell(mxBIArgs,2,elem_3);
  return mxBIArgs;
}

mxArray *cgxe_pEClYI3NgNTuTdGHmGitdG_fallback_info(void)
{
  const char* fallbackInfoFields[] = { "fallbackType", "incompatiableSymbol" };

  mxArray* fallbackInfoStruct = mxCreateStructMatrix(1, 1, 2, fallbackInfoFields);
  mxArray* fallbackType = mxCreateString("incompatibleFunction");
  mxArray* incompatibleSymbol = mxCreateString("lowPass1Init");
  mxSetFieldByNumber(fallbackInfoStruct, 0, 0, fallbackType);
  mxSetFieldByNumber(fallbackInfoStruct, 0, 1, incompatibleSymbol);
  return fallbackInfoStruct;
}
