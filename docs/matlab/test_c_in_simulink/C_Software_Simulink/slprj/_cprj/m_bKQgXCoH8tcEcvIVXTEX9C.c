/* Include files */

#include "modelInterface.h"
#include "m_bKQgXCoH8tcEcvIVXTEX9C.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
static void cgxe_mdl_start(InstanceStruct_bKQgXCoH8tcEcvIVXTEX9C *moduleInstance);
static void cgxe_mdl_initialize(InstanceStruct_bKQgXCoH8tcEcvIVXTEX9C
  *moduleInstance);
static void cgxe_mdl_outputs(InstanceStruct_bKQgXCoH8tcEcvIVXTEX9C
  *moduleInstance);
static void cgxe_mdl_update(InstanceStruct_bKQgXCoH8tcEcvIVXTEX9C
  *moduleInstance);
static void cgxe_mdl_derivative(InstanceStruct_bKQgXCoH8tcEcvIVXTEX9C
  *moduleInstance);
static void cgxe_mdl_enable(InstanceStruct_bKQgXCoH8tcEcvIVXTEX9C
  *moduleInstance);
static void cgxe_mdl_disable(InstanceStruct_bKQgXCoH8tcEcvIVXTEX9C
  *moduleInstance);
static void cgxe_mdl_terminate(InstanceStruct_bKQgXCoH8tcEcvIVXTEX9C
  *moduleInstance);
static const mxArray *emlrt_marshallOut(InstanceStruct_bKQgXCoH8tcEcvIVXTEX9C
  *moduleInstance);
static const mxArray *cgxe_mdl_get_sim_state
  (InstanceStruct_bKQgXCoH8tcEcvIVXTEX9C *moduleInstance);
static void emlrt_marshallIn(InstanceStruct_bKQgXCoH8tcEcvIVXTEX9C
  *moduleInstance, const mxArray *u);
static real32_T b_emlrt_marshallIn(InstanceStruct_bKQgXCoH8tcEcvIVXTEX9C
  *moduleInstance, const mxArray *nullptr, const char_T *identifier);
static real32_T c_emlrt_marshallIn(InstanceStruct_bKQgXCoH8tcEcvIVXTEX9C
  *moduleInstance, const mxArray *u, const emlrtMsgIdentifier *parentId);
static pt1filter d_emlrt_marshallIn(InstanceStruct_bKQgXCoH8tcEcvIVXTEX9C
  *moduleInstance, const mxArray *nullptr, const char_T *identifier);
static pt1filter e_emlrt_marshallIn(InstanceStruct_bKQgXCoH8tcEcvIVXTEX9C
  *moduleInstance, const mxArray *u, const emlrtMsgIdentifier *parentId);
static void cgxe_mdl_set_sim_state(InstanceStruct_bKQgXCoH8tcEcvIVXTEX9C
  *moduleInstance, const mxArray *st);
static real32_T f_emlrt_marshallIn(InstanceStruct_bKQgXCoH8tcEcvIVXTEX9C
  *moduleInstance, const mxArray *src, const emlrtMsgIdentifier *msgId);
static void init_simulink_io_address(InstanceStruct_bKQgXCoH8tcEcvIVXTEX9C
  *moduleInstance);

/* Function Definitions */
static void cgxe_mdl_start(InstanceStruct_bKQgXCoH8tcEcvIVXTEX9C *moduleInstance)
{
  init_simulink_io_address(moduleInstance);
  *(real32_T *)&((char_T *)moduleInstance->pt1)[0] = 0.0F;
  *(real32_T *)&((char_T *)moduleInstance->pt1)[4] = 0.0F;
  *(real32_T *)&((char_T *)moduleInstance->pt1)[8] = 0.0F;
  *(real32_T *)&((char_T *)moduleInstance->pt1)[12] = 0.0F;
  *(real32_T *)&((char_T *)moduleInstance->pt1)[16] = 0.0F;
  *(real32_T *)&((char_T *)moduleInstance->pt1)[20] = 0.0F;
  *moduleInstance->b_y0 = 0.0F;
}

static void cgxe_mdl_initialize(InstanceStruct_bKQgXCoH8tcEcvIVXTEX9C
  *moduleInstance)
{
  pt1filter r;
  real32_T *Tf;
  real32_T *Ts;
  Ts = (real32_T *)cgxertGetRunTimeParamInfoData(moduleInstance->S, 0);
  Tf = (real32_T *)cgxertGetRunTimeParamInfoData(moduleInstance->S, 1);
  r.a0 = *(real32_T *)&((char_T *)moduleInstance->pt1)[0];
  r.b0 = *(real32_T *)&((char_T *)moduleInstance->pt1)[4];
  r.b1 = *(real32_T *)&((char_T *)moduleInstance->pt1)[8];
  r.fPrevSample = *(real32_T *)&((char_T *)moduleInstance->pt1)[12];
  r.fPrevFilterOut = *(real32_T *)&((char_T *)moduleInstance->pt1)[16];
  r.fOut = *(real32_T *)&((char_T *)moduleInstance->pt1)[20];
  pt1filter_calcCoeff_A6bZI04XuKWXQ21NYmir3D(&r, 1.0F / *Tf, *Ts);
  *(real32_T *)&((char_T *)moduleInstance->pt1)[0] = r.a0;
  *(real32_T *)&((char_T *)moduleInstance->pt1)[4] = r.b0;
  *(real32_T *)&((char_T *)moduleInstance->pt1)[8] = r.b1;
  *(real32_T *)&((char_T *)moduleInstance->pt1)[12] = r.fPrevSample;
  *(real32_T *)&((char_T *)moduleInstance->pt1)[16] = r.fPrevFilterOut;
  *(real32_T *)&((char_T *)moduleInstance->pt1)[20] = r.fOut;
}

static void cgxe_mdl_outputs(InstanceStruct_bKQgXCoH8tcEcvIVXTEX9C
  *moduleInstance)
{
  pt1filter r;
  r.a0 = *(real32_T *)&((char_T *)moduleInstance->pt1)[0];
  r.b0 = *(real32_T *)&((char_T *)moduleInstance->pt1)[4];
  r.b1 = *(real32_T *)&((char_T *)moduleInstance->pt1)[8];
  r.fPrevSample = *(real32_T *)&((char_T *)moduleInstance->pt1)[12];
  r.fPrevFilterOut = *(real32_T *)&((char_T *)moduleInstance->pt1)[16];
  r.fOut = *(real32_T *)&((char_T *)moduleInstance->pt1)[20];
  *moduleInstance->b_y0 = pt1filter_calc_A6bZI04XuKWXQ21NYmir3D(&r,
    *moduleInstance->u0);
  *(real32_T *)&((char_T *)moduleInstance->pt1)[0] = r.a0;
  *(real32_T *)&((char_T *)moduleInstance->pt1)[4] = r.b0;
  *(real32_T *)&((char_T *)moduleInstance->pt1)[8] = r.b1;
  *(real32_T *)&((char_T *)moduleInstance->pt1)[12] = r.fPrevSample;
  *(real32_T *)&((char_T *)moduleInstance->pt1)[16] = r.fPrevFilterOut;
  *(real32_T *)&((char_T *)moduleInstance->pt1)[20] = r.fOut;
}

static void cgxe_mdl_update(InstanceStruct_bKQgXCoH8tcEcvIVXTEX9C
  *moduleInstance)
{
  (void)moduleInstance;
}

static void cgxe_mdl_derivative(InstanceStruct_bKQgXCoH8tcEcvIVXTEX9C
  *moduleInstance)
{
  (void)moduleInstance;
}

static void cgxe_mdl_enable(InstanceStruct_bKQgXCoH8tcEcvIVXTEX9C
  *moduleInstance)
{
  (void)moduleInstance;
}

static void cgxe_mdl_disable(InstanceStruct_bKQgXCoH8tcEcvIVXTEX9C
  *moduleInstance)
{
  (void)moduleInstance;
}

static void cgxe_mdl_terminate(InstanceStruct_bKQgXCoH8tcEcvIVXTEX9C
  *moduleInstance)
{
  (void)moduleInstance;
}

static const mxArray *emlrt_marshallOut(InstanceStruct_bKQgXCoH8tcEcvIVXTEX9C
  *moduleInstance)
{
  static const char_T *sv[6] = { "a0", "b0", "b1", "fPrevSample",
    "fPrevFilterOut", "fOut" };

  const mxArray *b_y;
  const mxArray *c_y;
  const mxArray *d_y;
  const mxArray *e_y;
  const mxArray *f_y;
  const mxArray *g_y;
  const mxArray *h_y;
  const mxArray *i_y;
  const mxArray *m;
  const mxArray *y;
  y = NULL;
  emlrtAssign(&y, emlrtCreateCellMatrix(2, 1));
  b_y = NULL;
  m = emlrtCreateNumericMatrix(1, 1, mxSINGLE_CLASS, mxREAL);
  *(real32_T *)emlrtMxGetData(m) = *moduleInstance->b_y0;
  emlrtAssign(&b_y, m);
  emlrtSetCell(y, 0, b_y);
  c_y = NULL;
  emlrtAssign(&c_y, emlrtCreateStructMatrix(1, 1, 6, (const char_T **)&sv[0]));
  d_y = NULL;
  m = emlrtCreateNumericMatrix(1, 1, mxSINGLE_CLASS, mxREAL);
  *(real32_T *)emlrtMxGetData(m) = *(real32_T *)&((char_T *)moduleInstance->pt1)
    [0];
  emlrtAssign(&d_y, m);
  emlrtSetFieldR2017b(c_y, 0, "a0", d_y, 0);
  e_y = NULL;
  m = emlrtCreateNumericMatrix(1, 1, mxSINGLE_CLASS, mxREAL);
  *(real32_T *)emlrtMxGetData(m) = *(real32_T *)&((char_T *)moduleInstance->pt1)
    [4];
  emlrtAssign(&e_y, m);
  emlrtSetFieldR2017b(c_y, 0, "b0", e_y, 1);
  f_y = NULL;
  m = emlrtCreateNumericMatrix(1, 1, mxSINGLE_CLASS, mxREAL);
  *(real32_T *)emlrtMxGetData(m) = *(real32_T *)&((char_T *)moduleInstance->pt1)
    [8];
  emlrtAssign(&f_y, m);
  emlrtSetFieldR2017b(c_y, 0, "b1", f_y, 2);
  g_y = NULL;
  m = emlrtCreateNumericMatrix(1, 1, mxSINGLE_CLASS, mxREAL);
  *(real32_T *)emlrtMxGetData(m) = *(real32_T *)&((char_T *)moduleInstance->pt1)
    [12];
  emlrtAssign(&g_y, m);
  emlrtSetFieldR2017b(c_y, 0, "fPrevSample", g_y, 3);
  h_y = NULL;
  m = emlrtCreateNumericMatrix(1, 1, mxSINGLE_CLASS, mxREAL);
  *(real32_T *)emlrtMxGetData(m) = *(real32_T *)&((char_T *)moduleInstance->pt1)
    [16];
  emlrtAssign(&h_y, m);
  emlrtSetFieldR2017b(c_y, 0, "fPrevFilterOut", h_y, 4);
  i_y = NULL;
  m = emlrtCreateNumericMatrix(1, 1, mxSINGLE_CLASS, mxREAL);
  *(real32_T *)emlrtMxGetData(m) = *(real32_T *)&((char_T *)moduleInstance->pt1)
    [20];
  emlrtAssign(&i_y, m);
  emlrtSetFieldR2017b(c_y, 0, "fOut", i_y, 5);
  emlrtSetCell(y, 1, c_y);
  return y;
}

static const mxArray *cgxe_mdl_get_sim_state
  (InstanceStruct_bKQgXCoH8tcEcvIVXTEX9C *moduleInstance)
{
  const mxArray *st;
  st = NULL;
  emlrtAssign(&st, emlrt_marshallOut(moduleInstance));
  return st;
}

static void emlrt_marshallIn(InstanceStruct_bKQgXCoH8tcEcvIVXTEX9C
  *moduleInstance, const mxArray *u)
{
  emlrtMsgIdentifier thisId;
  pt1filter r;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  thisId.fIdentifier = "y0";
  *moduleInstance->b_y0 = b_emlrt_marshallIn(moduleInstance, emlrtAlias
    (emlrtGetCell(moduleInstance->emlrtRootTLSGlobal, &thisId, u, 0)), "y0");
  thisId.fIdentifier = "pt1";
  r = d_emlrt_marshallIn(moduleInstance, emlrtAlias(emlrtGetCell
    (moduleInstance->emlrtRootTLSGlobal, &thisId, u, 1)), "pt1");
  *(real32_T *)&((char_T *)moduleInstance->pt1)[0] = r.a0;
  *(real32_T *)&((char_T *)moduleInstance->pt1)[4] = r.b0;
  *(real32_T *)&((char_T *)moduleInstance->pt1)[8] = r.b1;
  *(real32_T *)&((char_T *)moduleInstance->pt1)[12] = r.fPrevSample;
  *(real32_T *)&((char_T *)moduleInstance->pt1)[16] = r.fPrevFilterOut;
  *(real32_T *)&((char_T *)moduleInstance->pt1)[20] = r.fOut;
  emlrtDestroyArray(&u);
}

static real32_T b_emlrt_marshallIn(InstanceStruct_bKQgXCoH8tcEcvIVXTEX9C
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

static real32_T c_emlrt_marshallIn(InstanceStruct_bKQgXCoH8tcEcvIVXTEX9C
  *moduleInstance, const mxArray *u, const emlrtMsgIdentifier *parentId)
{
  real32_T y;
  y = f_emlrt_marshallIn(moduleInstance, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static pt1filter d_emlrt_marshallIn(InstanceStruct_bKQgXCoH8tcEcvIVXTEX9C
  *moduleInstance, const mxArray *nullptr, const char_T *identifier)
{
  emlrtMsgIdentifier thisId;
  pt1filter y;
  thisId.fIdentifier = (const char_T *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = e_emlrt_marshallIn(moduleInstance, emlrtAlias(nullptr), &thisId);
  emlrtDestroyArray(&nullptr);
  return y;
}

static pt1filter e_emlrt_marshallIn(InstanceStruct_bKQgXCoH8tcEcvIVXTEX9C
  *moduleInstance, const mxArray *u, const emlrtMsgIdentifier *parentId)
{
  static const int32_T dims = 0;
  static const char_T *fieldNames[6] = { "a0", "b0", "b1", "fPrevSample",
    "fPrevFilterOut", "fOut" };

  emlrtMsgIdentifier thisId;
  pt1filter y;
  thisId.fParent = parentId;
  thisId.bParentIsCell = false;
  emlrtCheckStructR2012b(moduleInstance->emlrtRootTLSGlobal, parentId, u, 6, (
    const char_T **)&fieldNames[0], 0U, (const void *)&dims);
  thisId.fIdentifier = "a0";
  y.a0 = c_emlrt_marshallIn(moduleInstance, emlrtAlias(emlrtGetFieldR2017b
    (moduleInstance->emlrtRootTLSGlobal, u, 0, 0, "a0")), &thisId);
  thisId.fIdentifier = "b0";
  y.b0 = c_emlrt_marshallIn(moduleInstance, emlrtAlias(emlrtGetFieldR2017b
    (moduleInstance->emlrtRootTLSGlobal, u, 0, 1, "b0")), &thisId);
  thisId.fIdentifier = "b1";
  y.b1 = c_emlrt_marshallIn(moduleInstance, emlrtAlias(emlrtGetFieldR2017b
    (moduleInstance->emlrtRootTLSGlobal, u, 0, 2, "b1")), &thisId);
  thisId.fIdentifier = "fPrevSample";
  y.fPrevSample = c_emlrt_marshallIn(moduleInstance, emlrtAlias
    (emlrtGetFieldR2017b(moduleInstance->emlrtRootTLSGlobal, u, 0, 3,
    "fPrevSample")), &thisId);
  thisId.fIdentifier = "fPrevFilterOut";
  y.fPrevFilterOut = c_emlrt_marshallIn(moduleInstance, emlrtAlias
    (emlrtGetFieldR2017b(moduleInstance->emlrtRootTLSGlobal, u, 0, 4,
    "fPrevFilterOut")), &thisId);
  thisId.fIdentifier = "fOut";
  y.fOut = c_emlrt_marshallIn(moduleInstance, emlrtAlias(emlrtGetFieldR2017b
    (moduleInstance->emlrtRootTLSGlobal, u, 0, 5, "fOut")), &thisId);
  emlrtDestroyArray(&u);
  return y;
}

static void cgxe_mdl_set_sim_state(InstanceStruct_bKQgXCoH8tcEcvIVXTEX9C
  *moduleInstance, const mxArray *st)
{
  emlrt_marshallIn(moduleInstance, emlrtAlias(st));
  emlrtDestroyArray(&st);
}

static real32_T f_emlrt_marshallIn(InstanceStruct_bKQgXCoH8tcEcvIVXTEX9C
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

static void init_simulink_io_address(InstanceStruct_bKQgXCoH8tcEcvIVXTEX9C
  *moduleInstance)
{
  moduleInstance->emlrtRootTLSGlobal = (void *)cgxertGetEMLRTCtx
    (moduleInstance->S);
  moduleInstance->u0 = (real32_T *)cgxertGetInputPortSignal(moduleInstance->S, 0);
  moduleInstance->b_y0 = (real32_T *)cgxertGetOutputPortSignal(moduleInstance->S,
    0);
  moduleInstance->pt1 = (pt1filter *)cgxertGetDWork(moduleInstance->S, 0);
}

/* CGXE Glue Code */
static void mdlOutputs_bKQgXCoH8tcEcvIVXTEX9C(SimStruct *S, int_T tid)
{
  InstanceStruct_bKQgXCoH8tcEcvIVXTEX9C *moduleInstance =
    (InstanceStruct_bKQgXCoH8tcEcvIVXTEX9C *)cgxertGetRuntimeInstance(S);
  cgxe_mdl_outputs(moduleInstance);
}

static void mdlInitialize_bKQgXCoH8tcEcvIVXTEX9C(SimStruct *S)
{
  InstanceStruct_bKQgXCoH8tcEcvIVXTEX9C *moduleInstance =
    (InstanceStruct_bKQgXCoH8tcEcvIVXTEX9C *)cgxertGetRuntimeInstance(S);
  cgxe_mdl_initialize(moduleInstance);
}

static void mdlUpdate_bKQgXCoH8tcEcvIVXTEX9C(SimStruct *S, int_T tid)
{
  InstanceStruct_bKQgXCoH8tcEcvIVXTEX9C *moduleInstance =
    (InstanceStruct_bKQgXCoH8tcEcvIVXTEX9C *)cgxertGetRuntimeInstance(S);
  cgxe_mdl_update(moduleInstance);
}

static void mdlDerivatives_bKQgXCoH8tcEcvIVXTEX9C(SimStruct *S)
{
  InstanceStruct_bKQgXCoH8tcEcvIVXTEX9C *moduleInstance =
    (InstanceStruct_bKQgXCoH8tcEcvIVXTEX9C *)cgxertGetRuntimeInstance(S);
  cgxe_mdl_derivative(moduleInstance);
}

static mxArray* getSimState_bKQgXCoH8tcEcvIVXTEX9C(SimStruct *S)
{
  mxArray* mxSS;
  InstanceStruct_bKQgXCoH8tcEcvIVXTEX9C *moduleInstance =
    (InstanceStruct_bKQgXCoH8tcEcvIVXTEX9C *)cgxertGetRuntimeInstance(S);
  mxSS = (mxArray *) cgxe_mdl_get_sim_state(moduleInstance);
  return mxSS;
}

static void setSimState_bKQgXCoH8tcEcvIVXTEX9C(SimStruct *S, const mxArray *ss)
{
  InstanceStruct_bKQgXCoH8tcEcvIVXTEX9C *moduleInstance =
    (InstanceStruct_bKQgXCoH8tcEcvIVXTEX9C *)cgxertGetRuntimeInstance(S);
  cgxe_mdl_set_sim_state(moduleInstance, emlrtAlias(ss));
}

static void mdlTerminate_bKQgXCoH8tcEcvIVXTEX9C(SimStruct *S)
{
  InstanceStruct_bKQgXCoH8tcEcvIVXTEX9C *moduleInstance =
    (InstanceStruct_bKQgXCoH8tcEcvIVXTEX9C *)cgxertGetRuntimeInstance(S);
  cgxe_mdl_terminate(moduleInstance);
  free((void *)moduleInstance);
}

static void mdlEnable_bKQgXCoH8tcEcvIVXTEX9C(SimStruct *S)
{
  InstanceStruct_bKQgXCoH8tcEcvIVXTEX9C *moduleInstance =
    (InstanceStruct_bKQgXCoH8tcEcvIVXTEX9C *)cgxertGetRuntimeInstance(S);
  cgxe_mdl_enable(moduleInstance);
}

static void mdlDisable_bKQgXCoH8tcEcvIVXTEX9C(SimStruct *S)
{
  InstanceStruct_bKQgXCoH8tcEcvIVXTEX9C *moduleInstance =
    (InstanceStruct_bKQgXCoH8tcEcvIVXTEX9C *)cgxertGetRuntimeInstance(S);
  cgxe_mdl_disable(moduleInstance);
}

static void mdlStart_bKQgXCoH8tcEcvIVXTEX9C(SimStruct *S)
{
  InstanceStruct_bKQgXCoH8tcEcvIVXTEX9C *moduleInstance =
    (InstanceStruct_bKQgXCoH8tcEcvIVXTEX9C *)calloc(1, sizeof
    (InstanceStruct_bKQgXCoH8tcEcvIVXTEX9C));
  moduleInstance->S = S;
  cgxertSetRuntimeInstance(S, (void *)moduleInstance);
  ssSetmdlOutputs(S, mdlOutputs_bKQgXCoH8tcEcvIVXTEX9C);
  ssSetmdlInitializeConditions(S, mdlInitialize_bKQgXCoH8tcEcvIVXTEX9C);
  ssSetmdlUpdate(S, mdlUpdate_bKQgXCoH8tcEcvIVXTEX9C);
  ssSetmdlDerivatives(S, mdlDerivatives_bKQgXCoH8tcEcvIVXTEX9C);
  ssSetmdlTerminate(S, mdlTerminate_bKQgXCoH8tcEcvIVXTEX9C);
  ssSetmdlEnable(S, mdlEnable_bKQgXCoH8tcEcvIVXTEX9C);
  ssSetmdlDisable(S, mdlDisable_bKQgXCoH8tcEcvIVXTEX9C);
  cgxe_mdl_start(moduleInstance);

  {
    uint_T options = ssGetOptions(S);
    options |= SS_OPTION_RUNTIME_EXCEPTION_FREE_CODE;
    ssSetOptions(S, options);
  }
}

static void mdlProcessParameters_bKQgXCoH8tcEcvIVXTEX9C(SimStruct *S)
{
}

void method_dispatcher_bKQgXCoH8tcEcvIVXTEX9C(SimStruct *S, int_T method, void
  *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_bKQgXCoH8tcEcvIVXTEX9C(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_bKQgXCoH8tcEcvIVXTEX9C(S);
    break;

   case SS_CALL_MDL_GET_SIM_STATE:
    *((mxArray**) data) = getSimState_bKQgXCoH8tcEcvIVXTEX9C(S);
    break;

   case SS_CALL_MDL_SET_SIM_STATE:
    setSimState_bKQgXCoH8tcEcvIVXTEX9C(S, (const mxArray *) data);
    break;

   default:
    /* Unhandled method */
    /*
       sf_mex_error_message("Stateflow Internal Error:\n"
       "Error calling method dispatcher for module: bKQgXCoH8tcEcvIVXTEX9C.\n"
       "Can't handle method %d.\n", method);
     */
    break;
  }
}

mxArray *cgxe_bKQgXCoH8tcEcvIVXTEX9C_BuildInfoUpdate(void)
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

mxArray *cgxe_bKQgXCoH8tcEcvIVXTEX9C_fallback_info(void)
{
  const char* fallbackInfoFields[] = { "fallbackType", "incompatiableSymbol" };

  mxArray* fallbackInfoStruct = mxCreateStructMatrix(1, 1, 2, fallbackInfoFields);
  mxArray* fallbackType = mxCreateString("incompatibleFunction");
  mxArray* incompatibleSymbol = mxCreateString("pt1filter_calcCoeff");
  mxSetFieldByNumber(fallbackInfoStruct, 0, 0, fallbackType);
  mxSetFieldByNumber(fallbackInfoStruct, 0, 1, incompatibleSymbol);
  return fallbackInfoStruct;
}
