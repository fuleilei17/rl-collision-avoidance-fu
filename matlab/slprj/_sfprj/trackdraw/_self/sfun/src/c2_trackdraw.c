/* Include files */

#include "trackdraw_sfun.h"
#include "c2_trackdraw.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "trackdraw_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c_with_debugger(S, sfGlobalDebugInstanceStruct);

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization);
static void chart_debug_initialize_data_addresses(SimStruct *S);
static const mxArray* sf_opaque_get_hover_data_for_msg(void *chartInstance,
  int32_T msgSSID);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static real_T _sfTime_;
static const char * c2_debug_family_names[10] = { "Image1", "nargin", "nargout",
  "xr", "yr", "r", "X_factor", "Y_factor", "X_Offset", "Y_Offset" };

/* Function Declarations */
static void initialize_c2_trackdraw(SFc2_trackdrawInstanceStruct *chartInstance);
static void initialize_params_c2_trackdraw(SFc2_trackdrawInstanceStruct
  *chartInstance);
static void enable_c2_trackdraw(SFc2_trackdrawInstanceStruct *chartInstance);
static void disable_c2_trackdraw(SFc2_trackdrawInstanceStruct *chartInstance);
static void c2_update_debugger_state_c2_trackdraw(SFc2_trackdrawInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c2_trackdraw(SFc2_trackdrawInstanceStruct
  *chartInstance);
static void set_sim_state_c2_trackdraw(SFc2_trackdrawInstanceStruct
  *chartInstance, const mxArray *c2_st);
static void finalize_c2_trackdraw(SFc2_trackdrawInstanceStruct *chartInstance);
static void sf_gateway_c2_trackdraw(SFc2_trackdrawInstanceStruct *chartInstance);
static void mdl_start_c2_trackdraw(SFc2_trackdrawInstanceStruct *chartInstance);
static void c2_chartstep_c2_trackdraw(SFc2_trackdrawInstanceStruct
  *chartInstance);
static void initSimStructsc2_trackdraw(SFc2_trackdrawInstanceStruct
  *chartInstance);
static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber, uint32_T c2_instanceNumber);
static const mxArray *c2_sf_marshallOut(void *chartInstanceVoid, void *c2_inData);
static real_T c2_emlrt_marshallIn(SFc2_trackdrawInstanceStruct *chartInstance,
  const mxArray *c2_b_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_b_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_b_emlrt_marshallIn(SFc2_trackdrawInstanceStruct *chartInstance,
  const mxArray *c2_b_u, const emlrtMsgIdentifier *c2_parentId, uint8_T c2_b_y
  [4605360]);
static void c2_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static void c2_imread(SFc2_trackdrawInstanceStruct *chartInstance, uint8_T c2_X
                      [4605360]);
static void c2_warning(SFc2_trackdrawInstanceStruct *chartInstance, real_T
  c2_varargin_1, char_T c2_varargin_2[200]);
static const mxArray *c2_emlrt_marshallOut(SFc2_trackdrawInstanceStruct
  *chartInstance, const char_T c2_b_u[2]);
static const mxArray *c2_b_emlrt_marshallOut(SFc2_trackdrawInstanceStruct
  *chartInstance, const char_T c2_b_u[41]);
static const mxArray *c2_c_emlrt_marshallOut(SFc2_trackdrawInstanceStruct
  *chartInstance, const real_T c2_b_u);
static const mxArray *c2_d_emlrt_marshallOut(SFc2_trackdrawInstanceStruct
  *chartInstance, const char_T c2_b_u[200]);
static const mxArray *c2_e_emlrt_marshallOut(SFc2_trackdrawInstanceStruct
  *chartInstance, const char_T c2_b_u[43]);
static const mxArray *c2_f_emlrt_marshallOut(SFc2_trackdrawInstanceStruct
  *chartInstance, const char_T c2_b_u[10]);
static const mxArray *c2_c_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static int32_T c2_c_emlrt_marshallIn(SFc2_trackdrawInstanceStruct *chartInstance,
  const mxArray *c2_b_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static uint8_T c2_d_emlrt_marshallIn(SFc2_trackdrawInstanceStruct *chartInstance,
  const mxArray *c2_b_is_active_c2_trackdraw, const char_T *c2_identifier);
static uint8_T c2_e_emlrt_marshallIn(SFc2_trackdrawInstanceStruct *chartInstance,
  const mxArray *c2_b_u, const emlrtMsgIdentifier *c2_parentId);
static void init_dsm_address_info(SFc2_trackdrawInstanceStruct *chartInstance);
static void init_simulink_io_address(SFc2_trackdrawInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c2_trackdraw(SFc2_trackdrawInstanceStruct *chartInstance)
{
  if (sf_is_first_init_cond(chartInstance->S)) {
    initSimStructsc2_trackdraw(chartInstance);
    chart_debug_initialize_data_addresses(chartInstance->S);
  }

  chartInstance->c2_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c2_is_active_c2_trackdraw = 0U;
}

static void initialize_params_c2_trackdraw(SFc2_trackdrawInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void enable_c2_trackdraw(SFc2_trackdrawInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c2_trackdraw(SFc2_trackdrawInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c2_update_debugger_state_c2_trackdraw(SFc2_trackdrawInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *get_sim_state_c2_trackdraw(SFc2_trackdrawInstanceStruct
  *chartInstance)
{
  const mxArray *c2_st;
  const mxArray *c2_b_y = NULL;
  uint8_T c2_hoistedGlobal;
  const mxArray *c2_c_y = NULL;
  c2_st = NULL;
  c2_st = NULL;
  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_createcellmatrix(1, 1), false);
  c2_hoistedGlobal = chartInstance->c2_is_active_c2_trackdraw;
  c2_c_y = NULL;
  sf_mex_assign(&c2_c_y, sf_mex_create("y", &c2_hoistedGlobal, 3, 0U, 0U, 0U, 0),
                false);
  sf_mex_setcell(c2_b_y, 0, c2_c_y);
  sf_mex_assign(&c2_st, c2_b_y, false);
  return c2_st;
}

static void set_sim_state_c2_trackdraw(SFc2_trackdrawInstanceStruct
  *chartInstance, const mxArray *c2_st)
{
  const mxArray *c2_b_u;
  chartInstance->c2_doneDoubleBufferReInit = true;
  c2_b_u = sf_mex_dup(c2_st);
  chartInstance->c2_is_active_c2_trackdraw = c2_d_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell("is_active_c2_trackdraw", c2_b_u, 0)),
    "is_active_c2_trackdraw");
  sf_mex_destroy(&c2_b_u);
  c2_update_debugger_state_c2_trackdraw(chartInstance);
  sf_mex_destroy(&c2_st);
}

static void finalize_c2_trackdraw(SFc2_trackdrawInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void sf_gateway_c2_trackdraw(SFc2_trackdrawInstanceStruct *chartInstance)
{
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 0U, chartInstance->c2_sfEvent);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c2_Y_Offset, 6U, 1U, 0U,
                        chartInstance->c2_sfEvent, false);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c2_X_Offset, 5U, 1U, 0U,
                        chartInstance->c2_sfEvent, false);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c2_Y_factor, 4U, 1U, 0U,
                        chartInstance->c2_sfEvent, false);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c2_X_factor, 3U, 1U, 0U,
                        chartInstance->c2_sfEvent, false);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c2_r, 2U, 1U, 0U,
                        chartInstance->c2_sfEvent, false);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c2_yr, 1U, 1U, 0U,
                        chartInstance->c2_sfEvent, false);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c2_xr, 0U, 1U, 0U,
                        chartInstance->c2_sfEvent, false);
  chartInstance->c2_sfEvent = CALL_EVENT;
  c2_chartstep_c2_trackdraw(chartInstance);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_trackdrawMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void mdl_start_c2_trackdraw(SFc2_trackdrawInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c2_chartstep_c2_trackdraw(SFc2_trackdrawInstanceStruct
  *chartInstance)
{
  real_T c2_hoistedGlobal;
  real_T c2_b_hoistedGlobal;
  real_T c2_c_hoistedGlobal;
  real_T c2_d_hoistedGlobal;
  real_T c2_e_hoistedGlobal;
  real_T c2_f_hoistedGlobal;
  real_T c2_g_hoistedGlobal;
  real_T c2_b_xr;
  real_T c2_b_yr;
  real_T c2_b_r;
  real_T c2_b_X_factor;
  real_T c2_b_Y_factor;
  real_T c2_b_X_Offset;
  real_T c2_b_Y_Offset;
  uint32_T c2_debug_family_var_map[10];
  real_T c2_nargin = 7.0;
  real_T c2_nargout = 0.0;
  int32_T c2_i0;
  static char_T c2_cv0[2] = { 'o', 'n' };

  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 0U, chartInstance->c2_sfEvent);
  c2_hoistedGlobal = *chartInstance->c2_xr;
  c2_b_hoistedGlobal = *chartInstance->c2_yr;
  c2_c_hoistedGlobal = *chartInstance->c2_r;
  c2_d_hoistedGlobal = *chartInstance->c2_X_factor;
  c2_e_hoistedGlobal = *chartInstance->c2_Y_factor;
  c2_f_hoistedGlobal = *chartInstance->c2_X_Offset;
  c2_g_hoistedGlobal = *chartInstance->c2_Y_Offset;
  c2_b_xr = c2_hoistedGlobal;
  c2_b_yr = c2_b_hoistedGlobal;
  c2_b_r = c2_c_hoistedGlobal;
  c2_b_X_factor = c2_d_hoistedGlobal;
  c2_b_Y_factor = c2_e_hoistedGlobal;
  c2_b_X_Offset = c2_f_hoistedGlobal;
  c2_b_Y_Offset = c2_g_hoistedGlobal;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 10U, 10U, c2_debug_family_names,
    c2_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(chartInstance->c2_Image1, 0U,
    c2_b_sf_marshallOut, c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargin, 1U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargout, 2U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_b_xr, 3U, c2_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_b_yr, 4U, c2_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_b_r, 5U, c2_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_b_X_factor, 6U, c2_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_b_Y_factor, 7U, c2_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_b_X_Offset, 8U, c2_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_b_Y_Offset, 9U, c2_sf_marshallOut);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 2);
  c2_imread(chartInstance, chartInstance->c2_uv0);
  for (c2_i0 = 0; c2_i0 < 4605360; c2_i0++) {
    chartInstance->c2_Image1[c2_i0] = chartInstance->c2_uv0[c2_i0];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 3);
  sf_mex_call_debug(sfGlobalDebugInstanceStruct, "hold", 0U, 1U, 14,
                    c2_emlrt_marshallOut(chartInstance, c2_cv0));
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, -3);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c2_sfEvent);
}

static void initSimStructsc2_trackdraw(SFc2_trackdrawInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber, uint32_T c2_instanceNumber)
{
  (void)(c2_machineNumber);
  (void)(c2_chartNumber);
  (void)(c2_instanceNumber);
}

static const mxArray *c2_sf_marshallOut(void *chartInstanceVoid, void *c2_inData)
{
  const mxArray *c2_mxArrayOutData;
  real_T c2_b_u;
  const mxArray *c2_b_y = NULL;
  SFc2_trackdrawInstanceStruct *chartInstance;
  chartInstance = (SFc2_trackdrawInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  c2_b_u = *(real_T *)c2_inData;
  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", &c2_b_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_b_y, false);
  return c2_mxArrayOutData;
}

static real_T c2_emlrt_marshallIn(SFc2_trackdrawInstanceStruct *chartInstance,
  const mxArray *c2_b_u, const emlrtMsgIdentifier *c2_parentId)
{
  real_T c2_b_y;
  real_T c2_d0;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_b_u), &c2_d0, 1, 0, 0U, 0, 0U, 0);
  c2_b_y = c2_d0;
  sf_mex_destroy(&c2_b_u);
  return c2_b_y;
}

static void c2_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_nargout;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_b_y;
  SFc2_trackdrawInstanceStruct *chartInstance;
  chartInstance = (SFc2_trackdrawInstanceStruct *)chartInstanceVoid;
  c2_nargout = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = (const char *)c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_b_y = c2_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_nargout), &c2_thisId);
  sf_mex_destroy(&c2_nargout);
  *(real_T *)c2_outData = c2_b_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_b_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData;
  int32_T c2_i1;
  int32_T c2_i2;
  const mxArray *c2_b_y = NULL;
  int32_T c2_i3;
  int32_T c2_i4;
  int32_T c2_i5;
  SFc2_trackdrawInstanceStruct *chartInstance;
  chartInstance = (SFc2_trackdrawInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  c2_i1 = 0;
  for (c2_i2 = 0; c2_i2 < 3; c2_i2++) {
    c2_i3 = 0;
    for (c2_i4 = 0; c2_i4 < 1240; c2_i4++) {
      for (c2_i5 = 0; c2_i5 < 1238; c2_i5++) {
        chartInstance->c2_u[(c2_i5 + c2_i3) + c2_i1] = (*(uint8_T (*)[4605360])
          c2_inData)[(c2_i5 + c2_i3) + c2_i1];
      }

      c2_i3 += 1238;
    }

    c2_i1 += 1535120;
  }

  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", chartInstance->c2_u, 3, 0U, 1U, 0U,
    3, 1238, 1240, 3), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_b_y, false);
  return c2_mxArrayOutData;
}

static void c2_b_emlrt_marshallIn(SFc2_trackdrawInstanceStruct *chartInstance,
  const mxArray *c2_b_u, const emlrtMsgIdentifier *c2_parentId, uint8_T c2_b_y
  [4605360])
{
  int32_T c2_i6;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_b_u), chartInstance->c2_uv1, 1, 3, 0U,
                1, 0U, 3, 1238, 1240, 3);
  for (c2_i6 = 0; c2_i6 < 4605360; c2_i6++) {
    c2_b_y[c2_i6] = chartInstance->c2_uv1[c2_i6];
  }

  sf_mex_destroy(&c2_b_u);
}

static void c2_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_Image1;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  int32_T c2_i7;
  int32_T c2_i8;
  int32_T c2_i9;
  int32_T c2_i10;
  int32_T c2_i11;
  SFc2_trackdrawInstanceStruct *chartInstance;
  chartInstance = (SFc2_trackdrawInstanceStruct *)chartInstanceVoid;
  c2_b_Image1 = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = (const char *)c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_Image1), &c2_thisId,
                        chartInstance->c2_y);
  sf_mex_destroy(&c2_b_Image1);
  c2_i7 = 0;
  for (c2_i8 = 0; c2_i8 < 3; c2_i8++) {
    c2_i9 = 0;
    for (c2_i10 = 0; c2_i10 < 1240; c2_i10++) {
      for (c2_i11 = 0; c2_i11 < 1238; c2_i11++) {
        (*(uint8_T (*)[4605360])c2_outData)[(c2_i11 + c2_i9) + c2_i7] =
          chartInstance->c2_y[(c2_i11 + c2_i9) + c2_i7];
      }

      c2_i9 += 1238;
    }

    c2_i7 += 1535120;
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

const mxArray *sf_c2_trackdraw_get_eml_resolved_functions_info(void)
{
  const mxArray *c2_nameCaptureInfo = NULL;
  c2_nameCaptureInfo = NULL;
  sf_mex_assign(&c2_nameCaptureInfo, sf_mex_create("nameCaptureInfo", NULL, 0,
    0U, 1U, 0U, 2, 0, 1), false);
  return c2_nameCaptureInfo;
}

static void c2_imread(SFc2_trackdrawInstanceStruct *chartInstance, uint8_T c2_X
                      [4605360])
{
  int8_T c2_fileStatus;
  int8_T c2_b_fileStatus;
  int8_T c2_libjpegReadDone;
  int8_T c2_b_libjpegReadDone;
  real_T c2_msgCode;
  real_T c2_libjpegMsgCode;
  int8_T c2_warnBufferFlag;
  int8_T c2_errWarnType;
  int8_T c2_b_errWarnType;
  int32_T c2_i12;
  real_T c2_b_libjpegMsgCode;
  char_T c2_libjpegWarnBuffer[200];
  int8_T c2_c_libjpegReadDone;
  int8_T c2_c_fileStatus;
  static char_T c2_fname[11] = { 'c', 'i', 'r', 'c', 'l', 'e', '.', 'j', 'p',
    'g', '\x00' };

  static real_T c2_outDims[3] = { 1238.0, 1240.0, 3.0 };

  static char_T c2_cv1[43] = { 'M', 'A', 'T', 'L', 'A', 'B', ':', 'i', 'm', 'a',
    'g', 'e', 's', 'c', 'i', ':', 'i', 'm', 'r', 'e', 'a', 'd', ':', 'c', 'o',
    'd', 'e', 'g', 'e', 'n', 'F', 'i', 'l', 'e', 'O', 'p', 'e', 'n', 'E', 'r',
    'r', 'o', 'r' };

  static char_T c2_cv2[10] = { 'c', 'i', 'r', 'c', 'l', 'e', '.', 'j', 'p', 'g'
  };

  static char_T c2_cv3[41] = { 'M', 'A', 'T', 'L', 'A', 'B', ':', 'i', 'm', 'a',
    'g', 'e', 's', 'c', 'i', ':', 'j', 'p', 'g', ':', 'u', 'n', 'h', 'a', 'n',
    'd', 'l', 'e', 'd', 'L', 'i', 'b', 'r', 'a', 'r', 'y', 'E', 'r', 'r', 'o',
    'r' };

  c2_fileStatus = c2_b_fileStatus;
  c2_libjpegReadDone = c2_b_libjpegReadDone;
  c2_msgCode = c2_libjpegMsgCode;
  c2_warnBufferFlag = c2_errWarnType;
  c2_b_errWarnType = c2_warnBufferFlag;
  for (c2_i12 = 0; c2_i12 < 200; c2_i12++) {
    c2_libjpegWarnBuffer[c2_i12] = ' ';
  }

  c2_b_libjpegMsgCode = c2_msgCode;
  c2_c_libjpegReadDone = c2_libjpegReadDone;
  c2_c_fileStatus = c2_fileStatus;
  jpegreader_uint8(c2_fname, c2_X, c2_outDims, 3.0, &c2_c_fileStatus,
                   &c2_c_libjpegReadDone, &c2_b_libjpegMsgCode,
                   c2_libjpegWarnBuffer, &c2_b_errWarnType);
  if ((c2_c_fileStatus == -1) || (c2_c_libjpegReadDone == 0) ||
      (c2_b_errWarnType == -1)) {
    if (!(c2_c_fileStatus == -1)) {
    } else {
      sf_mex_call_debug(sfGlobalDebugInstanceStruct, "error", 0U, 1U, 14,
                        sf_mex_call_debug(sfGlobalDebugInstanceStruct, "message",
        1U, 2U, 14, c2_e_emlrt_marshallOut(chartInstance, c2_cv1), 14,
        c2_f_emlrt_marshallOut(chartInstance, c2_cv2)));
    }

    if (!(c2_b_errWarnType == -1)) {
    } else {
      sf_mex_call_debug(sfGlobalDebugInstanceStruct, "error", 0U, 1U, 14,
                        sf_mex_call_debug(sfGlobalDebugInstanceStruct, "message",
        1U, 3U, 14, c2_b_emlrt_marshallOut(chartInstance, c2_cv3), 14,
        c2_c_emlrt_marshallOut(chartInstance, 8.0), 14, c2_d_emlrt_marshallOut
        (chartInstance, c2_libjpegWarnBuffer)));
    }

    if (!(c2_c_libjpegReadDone != 1)) {
    } else {
      sf_mex_call_debug(sfGlobalDebugInstanceStruct, "error", 0U, 1U, 14,
                        sf_mex_call_debug(sfGlobalDebugInstanceStruct, "message",
        1U, 3U, 14, c2_b_emlrt_marshallOut(chartInstance, c2_cv3), 14,
        c2_c_emlrt_marshallOut(chartInstance, 8.0), 14, c2_d_emlrt_marshallOut
        (chartInstance, c2_libjpegWarnBuffer)));
    }
  }

  if (c2_b_errWarnType == -2) {
    c2_warning(chartInstance, 8.0, c2_libjpegWarnBuffer);
  }
}

static void c2_warning(SFc2_trackdrawInstanceStruct *chartInstance, real_T
  c2_varargin_1, char_T c2_varargin_2[200])
{
  const mxArray *c2_b_y = NULL;
  static char_T c2_cv4[7] = { 'w', 'a', 'r', 'n', 'i', 'n', 'g' };

  const mxArray *c2_c_y = NULL;
  static char_T c2_cv5[7] = { 'm', 'e', 's', 's', 'a', 'g', 'e' };

  const mxArray *c2_d_y = NULL;
  static char_T c2_msgID[41] = { 'M', 'A', 'T', 'L', 'A', 'B', ':', 'i', 'm',
    'a', 'g', 'e', 's', 'c', 'i', ':', 'j', 'p', 'g', ':', 'u', 'n', 'h', 'a',
    'n', 'd', 'l', 'e', 'd', 'L', 'i', 'b', 'r', 'a', 'r', 'y', 'E', 'r', 'r',
    'o', 'r' };

  const mxArray *c2_e_y = NULL;
  const mxArray *c2_f_y = NULL;
  (void)chartInstance;
  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", c2_cv4, 10, 0U, 1U, 0U, 2, 1, 7),
                false);
  c2_c_y = NULL;
  sf_mex_assign(&c2_c_y, sf_mex_create("y", c2_cv5, 10, 0U, 1U, 0U, 2, 1, 7),
                false);
  c2_d_y = NULL;
  sf_mex_assign(&c2_d_y, sf_mex_create("y", c2_msgID, 10, 0U, 1U, 0U, 2, 1, 41),
                false);
  c2_e_y = NULL;
  sf_mex_assign(&c2_e_y, sf_mex_create("y", &c2_varargin_1, 0, 0U, 0U, 0U, 0),
                false);
  c2_f_y = NULL;
  sf_mex_assign(&c2_f_y, sf_mex_create("y", c2_varargin_2, 10, 0U, 1U, 0U, 2, 1,
    200), false);
  sf_mex_call_debug(sfGlobalDebugInstanceStruct, "feval", 0U, 2U, 14, c2_b_y, 14,
                    sf_mex_call_debug(sfGlobalDebugInstanceStruct, "feval", 1U,
    4U, 14, c2_c_y, 14, c2_d_y, 14, c2_e_y, 14, c2_f_y));
}

static const mxArray *c2_emlrt_marshallOut(SFc2_trackdrawInstanceStruct
  *chartInstance, const char_T c2_b_u[2])
{
  const mxArray *c2_b_y = NULL;
  (void)chartInstance;
  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", c2_b_u, 10, 0U, 1U, 0U, 2, 1, 2),
                false);
  return c2_b_y;
}

static const mxArray *c2_b_emlrt_marshallOut(SFc2_trackdrawInstanceStruct
  *chartInstance, const char_T c2_b_u[41])
{
  const mxArray *c2_b_y = NULL;
  (void)chartInstance;
  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", c2_b_u, 10, 0U, 1U, 0U, 2, 1, 41),
                false);
  return c2_b_y;
}

static const mxArray *c2_c_emlrt_marshallOut(SFc2_trackdrawInstanceStruct
  *chartInstance, const real_T c2_b_u)
{
  const mxArray *c2_b_y = NULL;
  (void)chartInstance;
  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", &c2_b_u, 0, 0U, 0U, 0U, 0), false);
  return c2_b_y;
}

static const mxArray *c2_d_emlrt_marshallOut(SFc2_trackdrawInstanceStruct
  *chartInstance, const char_T c2_b_u[200])
{
  const mxArray *c2_b_y = NULL;
  (void)chartInstance;
  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", c2_b_u, 10, 0U, 1U, 0U, 2, 1, 200),
                false);
  return c2_b_y;
}

static const mxArray *c2_e_emlrt_marshallOut(SFc2_trackdrawInstanceStruct
  *chartInstance, const char_T c2_b_u[43])
{
  const mxArray *c2_b_y = NULL;
  (void)chartInstance;
  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", c2_b_u, 10, 0U, 1U, 0U, 2, 1, 43),
                false);
  return c2_b_y;
}

static const mxArray *c2_f_emlrt_marshallOut(SFc2_trackdrawInstanceStruct
  *chartInstance, const char_T c2_b_u[10])
{
  const mxArray *c2_b_y = NULL;
  (void)chartInstance;
  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", c2_b_u, 10, 0U, 1U, 0U, 2, 1, 10),
                false);
  return c2_b_y;
}

static const mxArray *c2_c_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData;
  int32_T c2_b_u;
  const mxArray *c2_b_y = NULL;
  SFc2_trackdrawInstanceStruct *chartInstance;
  chartInstance = (SFc2_trackdrawInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  c2_b_u = *(int32_T *)c2_inData;
  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", &c2_b_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_b_y, false);
  return c2_mxArrayOutData;
}

static int32_T c2_c_emlrt_marshallIn(SFc2_trackdrawInstanceStruct *chartInstance,
  const mxArray *c2_b_u, const emlrtMsgIdentifier *c2_parentId)
{
  int32_T c2_b_y;
  int32_T c2_i13;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_b_u), &c2_i13, 1, 6, 0U, 0, 0U, 0);
  c2_b_y = c2_i13;
  sf_mex_destroy(&c2_b_u);
  return c2_b_y;
}

static void c2_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_sfEvent;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  int32_T c2_b_y;
  SFc2_trackdrawInstanceStruct *chartInstance;
  chartInstance = (SFc2_trackdrawInstanceStruct *)chartInstanceVoid;
  c2_b_sfEvent = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = (const char *)c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_b_y = c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_sfEvent),
    &c2_thisId);
  sf_mex_destroy(&c2_b_sfEvent);
  *(int32_T *)c2_outData = c2_b_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static uint8_T c2_d_emlrt_marshallIn(SFc2_trackdrawInstanceStruct *chartInstance,
  const mxArray *c2_b_is_active_c2_trackdraw, const char_T *c2_identifier)
{
  uint8_T c2_b_y;
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = (const char *)c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_b_y = c2_e_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c2_b_is_active_c2_trackdraw), &c2_thisId);
  sf_mex_destroy(&c2_b_is_active_c2_trackdraw);
  return c2_b_y;
}

static uint8_T c2_e_emlrt_marshallIn(SFc2_trackdrawInstanceStruct *chartInstance,
  const mxArray *c2_b_u, const emlrtMsgIdentifier *c2_parentId)
{
  uint8_T c2_b_y;
  uint8_T c2_u0;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_b_u), &c2_u0, 1, 3, 0U, 0, 0U, 0);
  c2_b_y = c2_u0;
  sf_mex_destroy(&c2_b_u);
  return c2_b_y;
}

static void init_dsm_address_info(SFc2_trackdrawInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void init_simulink_io_address(SFc2_trackdrawInstanceStruct *chartInstance)
{
  chartInstance->c2_fEmlrtCtx = (void *)sfrtGetEmlrtCtx(chartInstance->S);
  chartInstance->c2_xr = (real_T *)ssGetInputPortSignal_wrapper(chartInstance->S,
    0);
  chartInstance->c2_yr = (real_T *)ssGetInputPortSignal_wrapper(chartInstance->S,
    1);
  chartInstance->c2_r = (real_T *)ssGetInputPortSignal_wrapper(chartInstance->S,
    2);
  chartInstance->c2_X_factor = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 3);
  chartInstance->c2_Y_factor = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 4);
  chartInstance->c2_X_Offset = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 5);
  chartInstance->c2_Y_Offset = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 6);
}

/* SFunction Glue Code */
#ifdef utFree
#undef utFree
#endif

#ifdef utMalloc
#undef utMalloc
#endif

#ifdef __cplusplus

extern "C" void *utMalloc(size_t size);
extern "C" void utFree(void*);

#else

extern void *utMalloc(size_t size);
extern void utFree(void*);

#endif

void sf_c2_trackdraw_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3251161017U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(3605281416U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(653700651U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1287321159U);
}

mxArray* sf_c2_trackdraw_get_post_codegen_info(void);
mxArray *sf_c2_trackdraw_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals", "postCodegenInfo" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1, 1, sizeof
    (autoinheritanceFields)/sizeof(autoinheritanceFields[0]),
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("6PC1lJZWaRZHWpSy6eKxzF");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,7,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,3,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,4,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,4,"type",mxType);
    }

    mxSetField(mxData,4,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,5,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,5,"type",mxType);
    }

    mxSetField(mxData,5,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,6,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,6,"type",mxType);
    }

    mxSetField(mxData,6,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  {
    mxArray* mxPostCodegenInfo = sf_c2_trackdraw_get_post_codegen_info();
    mxSetField(mxAutoinheritanceInfo,0,"postCodegenInfo",mxPostCodegenInfo);
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c2_trackdraw_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,1);
  mxSetCell(mxcell3p, 0, mxCreateString(
             "matlab.io.sharedimage.internal.coder.ImreadJpegBuildable"));
  return(mxcell3p);
}

mxArray *sf_c2_trackdraw_jit_fallback_info(void)
{
  const char *infoFields[] = { "fallbackType", "fallbackReason",
    "hiddenFallbackType", "hiddenFallbackReason", "incompatibleSymbol" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 5, infoFields);
  mxArray *fallbackType = mxCreateString("late");
  mxArray *fallbackReason = mxCreateString("ir_function_calls");
  mxArray *hiddenFallbackType = mxCreateString("");
  mxArray *hiddenFallbackReason = mxCreateString("");
  mxArray *incompatibleSymbol = mxCreateString("jpegreader_uint8");
  mxSetField(mxInfo, 0, infoFields[0], fallbackType);
  mxSetField(mxInfo, 0, infoFields[1], fallbackReason);
  mxSetField(mxInfo, 0, infoFields[2], hiddenFallbackType);
  mxSetField(mxInfo, 0, infoFields[3], hiddenFallbackReason);
  mxSetField(mxInfo, 0, infoFields[4], incompatibleSymbol);
  return mxInfo;
}

mxArray *sf_c2_trackdraw_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

mxArray* sf_c2_trackdraw_get_post_codegen_info(void)
{
  const char* fieldNames[] = { "exportedFunctionsUsedByThisChart",
    "exportedFunctionsChecksum" };

  mwSize dims[2] = { 1, 1 };

  mxArray* mxPostCodegenInfo = mxCreateStructArray(2, dims, sizeof(fieldNames)/
    sizeof(fieldNames[0]), fieldNames);

  {
    mxArray* mxExportedFunctionsChecksum = mxCreateString("");
    mwSize exp_dims[2] = { 0, 1 };

    mxArray* mxExportedFunctionsUsedByThisChart = mxCreateCellArray(2, exp_dims);
    mxSetField(mxPostCodegenInfo, 0, "exportedFunctionsUsedByThisChart",
               mxExportedFunctionsUsedByThisChart);
    mxSetField(mxPostCodegenInfo, 0, "exportedFunctionsChecksum",
               mxExportedFunctionsChecksum);
  }

  return mxPostCodegenInfo;
}

static const mxArray *sf_get_sim_state_info_c2_trackdraw(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S'type','srcId','name','auxInfo'{{M[8],M[0],T\"is_active_c2_trackdraw\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 1, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c2_trackdraw_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc2_trackdrawInstanceStruct *chartInstance = (SFc2_trackdrawInstanceStruct *)
      sf_get_chart_instance_ptr(S);
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _trackdrawMachineNumber_,
           2,
           1,
           1,
           0,
           7,
           0,
           0,
           0,
           0,
           0,
           &chartInstance->chartNumber,
           &chartInstance->instanceNumber,
           (void *)S);

        /* Each instance must initialize its own list of scripts */
        init_script_number_translation(_trackdrawMachineNumber_,
          chartInstance->chartNumber,chartInstance->instanceNumber);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_trackdrawMachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _trackdrawMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"xr");
          _SFD_SET_DATA_PROPS(1,1,1,0,"yr");
          _SFD_SET_DATA_PROPS(2,1,1,0,"r");
          _SFD_SET_DATA_PROPS(3,1,1,0,"X_factor");
          _SFD_SET_DATA_PROPS(4,1,1,0,"Y_factor");
          _SFD_SET_DATA_PROPS(5,1,1,0,"X_Offset");
          _SFD_SET_DATA_PROPS(6,1,1,0,"Y_Offset");
          _SFD_STATE_INFO(0,0,2);
          _SFD_CH_SUBSTATE_COUNT(0);
          _SFD_CH_SUBSTATE_DECOMP(0);
        }

        _SFD_CV_INIT_CHART(0,0,0,0);

        {
          _SFD_CV_INIT_STATE(0,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(0,0,NULL,NULL,0,NULL);

        /* Initialization of MATLAB Function Model Coverage */
        _SFD_CV_INIT_EML(0,1,1,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,289);
        _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(6,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)NULL);
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _trackdrawMachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static void chart_debug_initialize_data_addresses(SimStruct *S)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc2_trackdrawInstanceStruct *chartInstance = (SFc2_trackdrawInstanceStruct *)
      sf_get_chart_instance_ptr(S);
    if (ssIsFirstInitCond(S)) {
      /* do this only if simulation is starting and after we know the addresses of all data */
      {
        _SFD_SET_DATA_VALUE_PTR(0U, (void *)chartInstance->c2_xr);
        _SFD_SET_DATA_VALUE_PTR(1U, (void *)chartInstance->c2_yr);
        _SFD_SET_DATA_VALUE_PTR(2U, (void *)chartInstance->c2_r);
        _SFD_SET_DATA_VALUE_PTR(3U, (void *)chartInstance->c2_X_factor);
        _SFD_SET_DATA_VALUE_PTR(4U, (void *)chartInstance->c2_Y_factor);
        _SFD_SET_DATA_VALUE_PTR(5U, (void *)chartInstance->c2_X_Offset);
        _SFD_SET_DATA_VALUE_PTR(6U, (void *)chartInstance->c2_Y_Offset);
      }
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "s8kt7WZlM4BdD9jQB16v8DG";
}

static void sf_opaque_initialize_c2_trackdraw(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc2_trackdrawInstanceStruct*) chartInstanceVar
    )->S,0);
  initialize_params_c2_trackdraw((SFc2_trackdrawInstanceStruct*)
    chartInstanceVar);
  initialize_c2_trackdraw((SFc2_trackdrawInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c2_trackdraw(void *chartInstanceVar)
{
  enable_c2_trackdraw((SFc2_trackdrawInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c2_trackdraw(void *chartInstanceVar)
{
  disable_c2_trackdraw((SFc2_trackdrawInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c2_trackdraw(void *chartInstanceVar)
{
  sf_gateway_c2_trackdraw((SFc2_trackdrawInstanceStruct*) chartInstanceVar);
}

static const mxArray* sf_opaque_get_sim_state_c2_trackdraw(SimStruct* S)
{
  return get_sim_state_c2_trackdraw((SFc2_trackdrawInstanceStruct *)
    sf_get_chart_instance_ptr(S));     /* raw sim ctx */
}

static void sf_opaque_set_sim_state_c2_trackdraw(SimStruct* S, const mxArray *st)
{
  set_sim_state_c2_trackdraw((SFc2_trackdrawInstanceStruct*)
    sf_get_chart_instance_ptr(S), st);
}

static void sf_opaque_terminate_c2_trackdraw(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc2_trackdrawInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_trackdraw_optimization_info();
    }

    finalize_c2_trackdraw((SFc2_trackdrawInstanceStruct*) chartInstanceVar);
    utFree(chartInstanceVar);
    if (ssGetUserData(S)!= NULL) {
      sf_free_ChartRunTimeInfo(S);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc2_trackdraw((SFc2_trackdrawInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c2_trackdraw(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c2_trackdraw((SFc2_trackdrawInstanceStruct*)
      sf_get_chart_instance_ptr(S));
  }
}

static void mdlSetWorkWidths_c2_trackdraw(SimStruct *S)
{
  /* Set overwritable ports for inplace optimization */
  ssSetStatesModifiedOnlyInUpdate(S, 1);
  ssMdlUpdateIsEmpty(S, 1);
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_trackdraw_optimization_info(sim_mode_is_rtw_gen(S),
      sim_mode_is_modelref_sim(S), sim_mode_is_external(S));
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,2);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,1);
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,2,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_set_chart_accesses_machine_info(S, sf_get_instance_specialization(),
      infoStruct, 2);
    sf_update_buildInfo(S, sf_get_instance_specialization(),infoStruct,2);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 4, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 5, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 6, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,2,7);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=0; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 7; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,2);
    sf_register_codegen_names_for_scoped_functions_defined_by_chart(S);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(1710059626U));
  ssSetChecksum1(S,(953344202U));
  ssSetChecksum2(S,(1599542739U));
  ssSetChecksum3(S,(1852995308U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSetStateSemanticsClassicAndSynchronous(S, true);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c2_trackdraw(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c2_trackdraw(SimStruct *S)
{
  SFc2_trackdrawInstanceStruct *chartInstance;
  chartInstance = (SFc2_trackdrawInstanceStruct *)utMalloc(sizeof
    (SFc2_trackdrawInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  memset(chartInstance, 0, sizeof(SFc2_trackdrawInstanceStruct));
  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c2_trackdraw;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c2_trackdraw;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c2_trackdraw;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c2_trackdraw;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c2_trackdraw;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c2_trackdraw;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c2_trackdraw;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c2_trackdraw;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c2_trackdraw;
  chartInstance->chartInfo.mdlStart = mdlStart_c2_trackdraw;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c2_trackdraw;
  chartInstance->chartInfo.callGetHoverDataForMsg = NULL;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->chartInfo.callAtomicSubchartUserFcn = NULL;
  chartInstance->chartInfo.callAtomicSubchartAutoFcn = NULL;
  chartInstance->chartInfo.debugInstance = sfGlobalDebugInstanceStruct;
  chartInstance->S = S;
  sf_init_ChartRunTimeInfo(S, &(chartInstance->chartInfo), false, 0);
  init_dsm_address_info(chartInstance);
  init_simulink_io_address(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  chart_debug_initialization(S,1);
  mdl_start_c2_trackdraw(chartInstance);
}

void c2_trackdraw_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c2_trackdraw(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c2_trackdraw(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c2_trackdraw(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c2_trackdraw_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
