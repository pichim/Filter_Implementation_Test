#pragma once

#include <stddef.h>

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

typedef struct {
    size_t order;
    float A[3];
    float B[3];
    float w[2];
} IIRFilter2_t;

void iirFilter2Init(IIRFilter2_t* filter);
float iirFilter2Apply(IIRFilter2_t* filter, const float input);
float iirFilter2ApplyConstrained(IIRFilter2_t* filter, const float input, const float yMin, const float yMax);
float iirFilter2ApplyFilterStep(IIRFilter2_t* filter, const float input, const float output);

typedef struct {
    IIRFilter2_t filter;
} NotchFilter_t;

void notchFilterInit(NotchFilter_t* notch, const float fcut, const float D, const float Ts);
void notchFilterUpdate(NotchFilter_t* notch, const float fcut, const float D, const float Ts);
float notchFilterApply(NotchFilter_t* notch, const float input);
float notchFilterApplyConstrained(NotchFilter_t* notch, const float input, const float yMin, const float yMax);

typedef struct {
    IIRFilter2_t filter;
} LowPassFilter2_t;

void lowPassFilter2Init(LowPassFilter2_t* lowpass2, const float fcut, const float D, const float Ts);
void lowPassFilter2Update(LowPassFilter2_t* lowpass2, const float fcut, const float D, const float Ts);
float lowPassFilter2Apply(LowPassFilter2_t* lowpass2, const float input);
float lowPassFilter2ApplyConstrained(LowPassFilter2_t* lowpass2, const float input, const float yMin, const float yMax);