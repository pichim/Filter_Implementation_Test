#include "customcode_usV23h6UlpYViYoInLiPJG.h"
#ifdef __cplusplus
extern "C" {
#endif


/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
DLL_EXPORT_CC extern const char_T *get_dll_checksum_usV23h6UlpYViYoInLiPJG(void);
DLL_EXPORT_CC extern void integratorInit_usV23h6UlpYViYoInLiPJG(IIRFilter_t *filter, const real32_T Ts);
DLL_EXPORT_CC extern void integratorUpdate_usV23h6UlpYViYoInLiPJG(IIRFilter_t *filter, const real32_T Ts);
DLL_EXPORT_CC extern void differentiatorInit_usV23h6UlpYViYoInLiPJG(IIRFilter_t *filter, const real32_T Ts);
DLL_EXPORT_CC extern void differentiatorUpdate_usV23h6UlpYViYoInLiPJG(IIRFilter_t *filter, const real32_T Ts);
DLL_EXPORT_CC extern void lowPass1Init_usV23h6UlpYViYoInLiPJG(IIRFilter_t *filter, const real32_T fcut, const real32_T Ts);
DLL_EXPORT_CC extern void lowPass1Update_usV23h6UlpYViYoInLiPJG(IIRFilter_t *filter, const real32_T fcut, const real32_T Ts);
DLL_EXPORT_CC extern void differentiatingLowPass1Init_usV23h6UlpYViYoInLiPJG(IIRFilter_t *filter, const real32_T fcut, const real32_T Ts);
DLL_EXPORT_CC extern void differentiatingLowPass1Update_usV23h6UlpYViYoInLiPJG(IIRFilter_t *filter, const real32_T fcut, const real32_T Ts);
DLL_EXPORT_CC extern void leadLag1Init_usV23h6UlpYViYoInLiPJG(IIRFilter_t *filter, const real32_T fZero, const real32_T fPole, const real32_T Ts);
DLL_EXPORT_CC extern void leadLag1Update_usV23h6UlpYViYoInLiPJG(IIRFilter_t *filter, const real32_T fZero, const real32_T fPole, const real32_T Ts);
DLL_EXPORT_CC extern void phaseComp1Init_usV23h6UlpYViYoInLiPJG(IIRFilter_t *filter, const real32_T fCenter, const real32_T phaseLift, const real32_T Ts);
DLL_EXPORT_CC extern void phaseComp1Update_usV23h6UlpYViYoInLiPJG(IIRFilter_t *filter, const real32_T fCenter, const real32_T phaseLift, const real32_T Ts);
DLL_EXPORT_CC extern void notchInit_usV23h6UlpYViYoInLiPJG(IIRFilter_t *filter, const real32_T fcut, const real32_T D, const real32_T Ts);
DLL_EXPORT_CC extern void notchUpdate_usV23h6UlpYViYoInLiPJG(IIRFilter_t *filter, const real32_T fcut, const real32_T D, const real32_T Ts);
DLL_EXPORT_CC extern void lowPass2Init_usV23h6UlpYViYoInLiPJG(IIRFilter_t *filter, const real32_T fcut, const real32_T D, const real32_T Ts);
DLL_EXPORT_CC extern void lowPass2Update_usV23h6UlpYViYoInLiPJG(IIRFilter_t *filter, const real32_T fcut, const real32_T D, const real32_T Ts);
DLL_EXPORT_CC extern void leadLag2Init_usV23h6UlpYViYoInLiPJG(IIRFilter_t *filter, const real32_T fZero, const real32_T DZero, const real32_T fPole, const real32_T DPole, const real32_T Ts);
DLL_EXPORT_CC extern void leadLag2Update_usV23h6UlpYViYoInLiPJG(IIRFilter_t *filter, const real32_T fZero, const real32_T DZero, const real32_T fPole, const real32_T DPole, const real32_T Ts);
DLL_EXPORT_CC extern void iirFilterReset_usV23h6UlpYViYoInLiPJG(IIRFilter_t *filter, const real32_T output);
DLL_EXPORT_CC extern void iirFilterResetDifferentingFilterToZero_usV23h6UlpYViYoInLiPJG(IIRFilter_t *filter, const real32_T output);
DLL_EXPORT_CC extern real32_T iirFilterApply_usV23h6UlpYViYoInLiPJG(IIRFilter_t *filter, const real32_T input);
DLL_EXPORT_CC extern real32_T iirFilterApplyConstrained_usV23h6UlpYViYoInLiPJG(IIRFilter_t *filter, const real32_T input, const real32_T yMin, const real32_T yMax);
DLL_EXPORT_CC extern void iirFilterApplyFilterUpdate_usV23h6UlpYViYoInLiPJG(IIRFilter_t *filter, const real32_T input, const real32_T output);

/* Function Definitions */
DLL_EXPORT_CC const uint8_T *get_checksum_source_info(int32_T *size);
#ifdef __cplusplus
}
#endif

