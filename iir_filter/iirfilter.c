#include "iirfilter.h"
#include <math.h>

void iirFilter2Init(IIRFilter2_t* filter)
{
    filter->order = 2;
    for (size_t i = 0; i < filter->order; ++i) {
        filter->w[i] = 0.0f;
    }
}

float iirFilter2Apply(IIRFilter2_t* filter, const float input)
{
    const float output = filter->B[0] * input + filter->w[0];

    return iirFilter2ApplyFilterStep(filter, input, output);
}

float iirFilter2ApplyConstrained(IIRFilter2_t* filter,
                                 const float input,
                                 const float yMin,
                                 const float yMax)
{
    const float outputUnconstrained = filter->B[0] * input + filter->w[0];

    // constrain output
    const float output = (outputUnconstrained < yMin) ? yMin
                       : (outputUnconstrained > yMax) ? yMax
                       :  outputUnconstrained;

    return iirFilter2ApplyFilterStep(filter, input, output);
}

float iirFilter2ApplyFilterStep(IIRFilter2_t* filter, const float input, const float output)
{
    // https://dsp.stackexchange.com/questions/72575/transposed-direct-form-ii
    for (size_t i = 0; i < filter->order - 1; ++i) {
        filter->w[i] = filter->B[i + 1] * input + filter->w[i + 1] - filter->A[i + 1] * output;
    }
    filter->w[filter->order - 1] = filter->B[filter->order] * input - filter->A[filter->order] * output;

    return output;
}

// Second Order Notch Filter
// Time continous prototype: G(s) = (s^2 + 2 * D * wcut * s + wcut^2) / (s^2 + wcut^2)
// Disrectization method: Tustin with prewarping

void notchFilterInit(NotchFilter_t* notch, const float fcut, const float D, const float Ts)
{
    iirFilter2Init(&notch->filter);
    notchFilterUpdate(notch, fcut, D, Ts);
}

void notchFilterUpdate(NotchFilter_t* notch, const float fcut, const float D, const float Ts)
{
    IIRFilter2_t* filter = &notch->filter;

    const float Q = 1.0f / (2.0f * D);
    // prewarp is done implicitly
    const float omega = 2.0f * M_PI * fcut * Ts;
    const float sn = sinf(omega);
    const float cs = cosf(omega);
    const float alpha = sn / (2.0f * Q);

    filter->B[0] = 1.0f / (1.0f + alpha);
    filter->B[1] = -2.0f * cs / (1.0f + alpha);
    filter->B[2] = filter->B[0];

    filter->A[0] = 1.0f;
    filter->A[1] = filter->B[1];
    filter->A[2] = (1.0f - alpha) / (1.0f + alpha);
}

float notchFilterApply(NotchFilter_t* notch, const float input)
{
    return iirFilter2Apply(&notch->filter, input);
}

float notchFilterApplyConstrained(NotchFilter_t* notch,
                                  const float input,
                                  const float yMin,
                                  const float yMax)
{
    return iirFilter2ApplyConstrained(&notch->filter, input, yMin, yMax);
}

// Second Order Lowpass Filter
// Time continous prototype: G(s) = wcut^2 / (s^2 + 2 * D * wcut * s + wcut^2)
// Disrectization method: Euler

void lowPassFilter2Init(LowPassFilter2_t* lowpass2, const float fcut, const float D, const float Ts)
{
    iirFilter2Init(&lowpass2->filter);
    lowPassFilter2Update(lowpass2, fcut, D, Ts);
}

void lowPassFilter2Update(LowPassFilter2_t* lowpass2, const float fcut, const float D, const float Ts)
{
    IIRFilter2_t* filter = &lowpass2->filter;

    const float wcut = 2.0f * M_PI * fcut;
    const float k1 = 2.0f * D * Ts * wcut;
        
    filter->A[0] = 1.0f;
    filter->A[2] = 1.0f / (Ts * Ts * wcut * wcut + k1 + 1.0f);
    filter->A[1] = -(k1 + 2.0f) * filter->A[2];

    filter->B[0] = 1.0f + filter->A[1] + filter->A[2];
    filter->B[1] = 0.0f;
    filter->B[2] = 0.0f;
}

float lowPassFilter2Apply(LowPassFilter2_t* lowpass2, const float input)
{
    return iirFilter2Apply(&lowpass2->filter, input);
}

float lowPassFilter2ApplyConstrained(LowPassFilter2_t* lowpass2,
                                     const float input,
                                     const float yMin,
                                     const float yMax)
{
    return iirFilter2ApplyConstrained(&lowpass2->filter, input, yMin, yMax);
}