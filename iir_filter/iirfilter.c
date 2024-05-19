#include "iirfilter.h"
#include <math.h>

void iirFilterInit(IIRFilter_t* filter, const size_t order)
{
    filter->order = order;
    for (size_t i = 0; i < filter->order; ++i) {
        filter->w[i] = 0.0f;
    }
}

float iirFilterApply(IIRFilter_t* filter, const float input)
{
    const float output = filter->B[0] * input + filter->w[0];

    return iirFilterApplyFilterStep(filter, input, output);
}

float iirFilterApplyConstrained(IIRFilter_t* filter,
                                 const float input,
                                 const float yMin,
                                 const float yMax)
{
    const float outputUnconstrained = filter->B[0] * input + filter->w[0];

    // constrain output
    const float output = (outputUnconstrained < yMin) ? yMin
                       : (outputUnconstrained > yMax) ? yMax
                       :  outputUnconstrained;

    return iirFilterApplyFilterStep(filter, input, output);
}

float iirFilterApplyFilterStep(IIRFilter_t* filter, const float input, const float output)
{
    // https://dsp.stackexchange.com/questions/72575/transposed-direct-form-ii
    for (size_t i = 0; i < filter->order - 1; ++i) {
        filter->w[i] = filter->B[i + 1] * input + filter->w[i + 1] - filter->A[i + 1] * output;
    }
    filter->w[filter->order - 1] = filter->B[filter->order] * input - filter->A[filter->order] * output;

    return output;
}

void lowPassFilter1Init(LowPassFilter1_t* lowpass1, const float fcut, const float Ts)
{
    iirFilterInit(&lowpass1->filter, 1);
    lowPassFilter1Update(lowpass1, fcut, Ts);
}

void lowPassFilter1Update(LowPassFilter1_t* lowpass1, const float fcut, const float Ts)
{
    IIRFilter_t* filter = &lowpass1->filter;

    filter->A[0] = 1.0f;
    filter->A[1] = -expf(-Ts * 2.0f * M_PI * fcut);

    filter->B[0] = 1.0f + filter->A[1];
    filter->B[1] = 0.0f;
}

float lowPassFilter1Apply(LowPassFilter1_t* lowpass1, const float input)
{
    return iirFilterApply(&lowpass1->filter, input);
}

float lowPassFilter1ApplyConstrained(LowPassFilter1_t* lowpass1,
                                     const float input,
                                     const float yMin,
                                     const float yMax)
{
    return iirFilterApplyConstrained(&lowpass1->filter, input, yMin, yMax);
}

// Second Order Notch Filter
// Time continous prototype: G(s) = (s^2 + 2 * D * wcut * s + wcut^2) / (s^2 + wcut^2)
// Disrectization method: Tustin with prewarping

void notchFilterInit(NotchFilter_t* notch, const float fcut, const float D, const float Ts)
{
    iirFilterInit(&notch->filter, 2);
    notchFilterUpdate(notch, fcut, D, Ts);
}

void notchFilterUpdate(NotchFilter_t* notch, const float fcut, const float D, const float Ts)
{
    IIRFilter_t* filter = &notch->filter;

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
    return iirFilterApply(&notch->filter, input);
}

float notchFilterApplyConstrained(NotchFilter_t* notch,
                                  const float input,
                                  const float yMin,
                                  const float yMax)
{
    return iirFilterApplyConstrained(&notch->filter, input, yMin, yMax);
}

// Second Order Lowpass Filter
// Time continous prototype: G(s) = wcut^2 / (s^2 + 2 * D * wcut * s + wcut^2)
// Disrectization method: Euler

void lowPassFilter2Init(LowPassFilter2_t* lowpass2, const float fcut, const float D, const float Ts)
{
    iirFilterInit(&lowpass2->filter, 2);
    lowPassFilter2Update(lowpass2, fcut, D, Ts);
}

void lowPassFilter2Update(LowPassFilter2_t* lowpass2, const float fcut, const float D, const float Ts)
{
    IIRFilter_t* filter = &lowpass2->filter;

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
    return iirFilterApply(&lowpass2->filter, input);
}

float lowPassFilter2ApplyConstrained(LowPassFilter2_t* lowpass2,
                                     const float input,
                                     const float yMin,
                                     const float yMax)
{
    return iirFilterApplyConstrained(&lowpass2->filter, input, yMin, yMax);
}