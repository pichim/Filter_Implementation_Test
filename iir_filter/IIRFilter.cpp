#include "IIRFilter.h"
#include <cmath>

IIRFilter2::IIRFilter2()
{
    initFilter();
}

void IIRFilter2::initFilter()
{
    for (size_t i = 0; i < IIRFilter2Params::order; ++i) {
        params.w[i] = 0.0f;
    }
}

float IIRFilter2::applyFilter(const float input)
{
    const float output = params.B[0] * input + params.w[0];

    return applyFilterStep(input, output);
}

float IIRFilter2::applyFilterConstrained(const float input, const float yMin, const float yMax)
{
    const float outputUnconstrained = params.B[0] * input + params.w[0];

    // constrain output
    const float output = (outputUnconstrained < yMin) ? yMin
                       : (outputUnconstrained > yMax) ? yMax
                       :  outputUnconstrained;

    return applyFilterStep(input, output);
}

float IIRFilter2::applyFilterStep(const float input, const float output)
{
    // https://dsp.stackexchange.com/questions/72575/transposed-direct-form-ii
    for (size_t i = 0; i < IIRFilter2Params::order - 1; ++i) {
        params.w[i] = params.B[i + 1] * input + params.w[i + 1] - params.A[i + 1] * output;
    }
    params.w[IIRFilter2Params::order - 1] = params.B[IIRFilter2Params::order] * input - params.A[IIRFilter2Params::order] * output;

    return output;
}

// Second Order Notch Filter
// Time continous prototype: G(s) = (s^2 + 2 * D * wcut * s + wcut^2) / (s^2 + wcut^2)
// Disrectization method: Tustin with prewarping

NotchFilter::NotchFilter(const float fcut, const float D, const float Ts)
{
    update(fcut, D, Ts);
}

void NotchFilter::update(const float fcut, const float D, const float Ts)
{
    const float Q = 1.0f / (2.0f * D);
    // prewarp is done implicitly
    const float omega = 2.0f * M_PI * fcut * Ts;
    const float sn = sinf(omega);
    const float cs = cosf(omega);
    const float alpha = sn / (2.0f * Q);

    params.B[0] = 1.0f / (1.0f + alpha);
    params.B[1] = -2.0f * cs / (1.0f + alpha);
    params.B[2] = params.B[0];

    params.A[0] = 1.0f;
    params.A[1] = params.B[1];
    params.A[2] = (1.0f - alpha) / (1.0f + alpha);
}

float NotchFilter::apply(const float input)
{
    return applyFilter(input);
}

float NotchFilter::applyConstrained(const float input, const float yMin, const float yMax)
{
    return applyFilterConstrained(input, yMin, yMax);
}

// Second Order Lowpass Filter
// Time continous prototype: G(s) = wcut^2 / (s^2 + 2 * D * wcut * s + wcut^2)
// Disrectization method: Euler

LowPassFilter2::LowPassFilter2(const float fcut, const float D, const float Ts)
{
    update(fcut, D, Ts);
}

void LowPassFilter2::update(const float fcut, const float D, const float Ts)
{
    const float wcut = 2.0f * M_PI * fcut;
    const float k1 = 2.0f * D * Ts * wcut;
        
    params.A[0] = 1.0f;
    params.A[2] = 1.0f / (Ts * Ts * wcut * wcut + k1 + 1.0f);
    params.A[1] = -(k1 + 2.0f) * params.A[2];

    params.B[0] = 1.0f + params.A[1] + params.A[2];
    params.B[1] = 0.0f;
    params.B[2] = 0.0f;
}

float LowPassFilter2::apply(const float input)
{
    return applyFilter(input);
}

float LowPassFilter2::applyConstrained(const float input, const float yMin, const float yMax)
{
    return applyFilterConstrained(input, yMin, yMax);
}