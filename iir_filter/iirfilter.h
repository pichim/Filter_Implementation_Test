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

void lowPassFilter1Init(IIRFilter_t* filter, const float fcut, const float Ts);
void lowPassFilter1Update(IIRFilter_t* filter, const float fcut, const float Ts);
void notchFilterInit(IIRFilter_t* filter, const float fcut, const float D, const float Ts);
void notchFilterUpdate(IIRFilter_t* filter, const float fcut, const float D, const float Ts);
void lowPassFilter2Init(IIRFilter_t* filter, const float fcut, const float D, const float Ts);
void lowPassFilter2Update(IIRFilter_t* filter, const float fcut, const float D, const float Ts);

float iirFilterApply(IIRFilter_t* filter, const float input);
float iirFilterApplyConstrained(IIRFilter_t* filter, const float input, const float yMin, const float yMax);

void iirFilterInit(IIRFilter_t* filter, const unsigned order);
float iirFilterApplyFilterUpdate(IIRFilter_t* filter, const float input, const float output);