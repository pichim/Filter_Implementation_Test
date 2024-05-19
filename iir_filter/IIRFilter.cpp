#include "IIRFilter.h"
#include <cmath>

IIRFilter::IIRFilter(const size_t order)
{
    params.order = order;
    initFilter();
}

void IIRFilter::initFilter()
{
    for (size_t i = 0; i < params.order; ++i) {
        params.w[i] = 0.0f;
    }
}

float IIRFilter::applyFilter(const float input)
{
    const float output = params.B[0] * input + params.w[0];

    return applyFilterStep(input, output);
}

float IIRFilter::applyFilterConstrained(const float input, const float yMin, const float yMax)
{
    const float outputUnconstrained = params.B[0] * input + params.w[0];

    // constrain output
    const float output = (outputUnconstrained < yMin) ? yMin
                       : (outputUnconstrained > yMax) ? yMax
                       :  outputUnconstrained;

    return applyFilterStep(input, output);
}

float IIRFilter::applyFilterStep(const float input, const float output)
{
    // https://dsp.stackexchange.com/questions/72575/transposed-direct-form-ii
    for (size_t i = 0; i < params.order - 1; ++i) {
        params.w[i] = params.B[i + 1] * input + params.w[i + 1] - params.A[i + 1] * output;
    }
    params.w[params.order - 1] = params.B[params.order] * input - params.A[params.order] * output;

    return output;
}

// First Order Lowpass Filter
// Time continous prototype: G(s) = wcut / (s +  wcut)
// Disrectization method: ZOH with one additional forward shift, e.g. G(z^-1) = Gzoh(z^-1) * z

LowPassFilter1::LowPassFilter1(const float fcut, const float Ts) : IIRFilter(1)
{
    update(fcut, Ts);
}

void LowPassFilter1::update(const float fcut, const float Ts)
{        
    params.A[0] = 1.0f;
    params.A[1] = -expf(-Ts * 2.0f * M_PI * fcut);

    params.B[0] = 1.0f + params.A[1];
    params.B[1] = 0.0f;
}

float LowPassFilter1::apply(const float input)
{
    return applyFilter(input);
}

float LowPassFilter1::applyConstrained(const float input, const float yMin, const float yMax)
{
    return applyFilterConstrained(input, yMin, yMax);
}

// Second Order Notch Filter
// Time continous prototype: G(s) = (s^2 + 2 * D * wcut * s + wcut^2) / (s^2 + wcut^2)
// Disrectization method: Tustin with prewarping

NotchFilter::NotchFilter(const float fcut, const float D, const float Ts) : IIRFilter(2)
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

LowPassFilter2::LowPassFilter2(const float fcut, const float D, const float Ts) : IIRFilter(2)
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