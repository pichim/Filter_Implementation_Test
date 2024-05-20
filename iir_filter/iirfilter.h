#pragma once

#include <math.h>

#ifndef M_PIf
    #define M_PIf 3.14159265358979323846f /* pi */
#endif

typedef struct IIRFilter_s{
    unsigned order;
    float A[3];
    float B[3];
    float w[2];
} IIRFilter_t;

void lowPass1Init(IIRFilter_t* filter, const float fcut, const float Ts);
void lowPass1Update(IIRFilter_t* filter, const float fcut, const float Ts);

void leadLag1Init(IIRFilter_t* filter, const float fZero, const float fPole, const float Ts);
void leadLag1Update(IIRFilter_t* filter, const float fZero, const float fPole, const float Ts);
void phaseComp1Init(IIRFilter_t* filter, const float fCenter, const float phaseLift, const float Ts);
void phaseComp1Update(IIRFilter_t* filter, const float fCenter, const float phaseLift, const float Ts);

void notchInit(IIRFilter_t* filter, const float fcut, const float D, const float Ts);
void notchUpdate(IIRFilter_t* filter, const float fcut, const float D, const float Ts);

void lowPass2Init(IIRFilter_t* filter, const float fcut, const float D, const float Ts);
void lowPass2Update(IIRFilter_t* filter, const float fcut, const float D, const float Ts);

float iirFilterApply(IIRFilter_t* filter, const float input);
float iirFilterApplyConstrained(IIRFilter_t* filter, const float input, const float yMin, const float yMax);

void iirFilterInit(IIRFilter_t* filter, const unsigned order);
float iirFilterApplyFilterUpdate(IIRFilter_t* filter, const float input, const float output);