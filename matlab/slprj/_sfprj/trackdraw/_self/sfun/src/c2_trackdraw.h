#ifndef __c2_trackdraw_h__
#define __c2_trackdraw_h__

/* Include files */
#include "sf_runtime/sfc_sf.h"
#include "sf_runtime/sfc_mex.h"
#include "rtwtypes.h"
#include "multiword_types.h"

/* Type Definitions */
#ifndef typedef_SFc2_trackdrawInstanceStruct
#define typedef_SFc2_trackdrawInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c2_sfEvent;
  boolean_T c2_doneDoubleBufferReInit;
  uint8_T c2_is_active_c2_trackdraw;
  uint8_T c2_Image1[4605360];
  uint8_T c2_uv0[4605360];
  uint8_T c2_y[4605360];
  uint8_T c2_uv1[4605360];
  uint8_T c2_u[4605360];
  void *c2_fEmlrtCtx;
  real_T *c2_xr;
  real_T *c2_yr;
  real_T *c2_r;
  real_T *c2_X_factor;
  real_T *c2_Y_factor;
  real_T *c2_X_Offset;
  real_T *c2_Y_Offset;
} SFc2_trackdrawInstanceStruct;

#endif                                 /*typedef_SFc2_trackdrawInstanceStruct*/

/* Named Constants */

/* Variable Declarations */
extern struct SfDebugInstanceStruct *sfGlobalDebugInstanceStruct;

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c2_trackdraw_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c2_trackdraw_get_check_sum(mxArray *plhs[]);
extern void c2_trackdraw_method_dispatcher(SimStruct *S, int_T method, void
  *data);

#endif
