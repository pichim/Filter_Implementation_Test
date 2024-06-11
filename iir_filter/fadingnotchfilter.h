#pragma once

#include "iirfilter.h"

typedef struct FadingNotchFilter_s{
    float D, Ts, fFadeMin, fFadeMax;
    IIRFilter_t filter;
} FadingNotchFilter_t;

void fadingNotchInit(FadingNotchFilter_t* fadingNotch, const float fcut, const float D, const float fFadeMin, const float fFadeMax, const float Ts);
void fadingNotchFilterReset(FadingNotchFilter_t* fadingNotch, const float fcut, const float output);
float fadingNotchFilterApply(FadingNotchFilter_t* fadingNotch, const float fcut, const float input);
float fadingNotchFilterApplyConstrained(FadingNotchFilter_t* fadingNotch, const float fcut, const float input, const float yMin, const float yMax);

// helper function
float fadingNotchFilterApplyFading(FadingNotchFilter_t* fadingNotch, const float fcut, const float input, const float output);