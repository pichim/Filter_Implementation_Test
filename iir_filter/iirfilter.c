#include "iirfilter.h"

// First Order Lowpass Filter
// Time continous prototype: G(s) = wcut / (s +  wcut)
// Disrectization method: ZOH with one additional forward shift, e.g. G(z^-1) = Gzoh(z^-1) * z

void lowPassFilter1Init(IIRFilter_t* filter, const float fcut, const float Ts)
{
    iirFilterInit(filter, 1);
    lowPassFilter1Update(filter, fcut, Ts);
}

void lowPassFilter1Update(IIRFilter_t* filter, const float fcut, const float Ts)
{
    filter->A[0] = 1.0f;
    filter->A[1] = -expf(-Ts * 2.0f * M_PIf * fcut);
    filter->B[0] = 1.0f + filter->A[1];
    filter->B[1] = 0.0f;
}

// Second Order Notch Filter
// Time continous prototype: G(s) = (s^2 + 2 * D * wcut * s + wcut^2) / (s^2 + wcut^2)
// Disrectization method: Tustin with prewarping

void notchFilterInit(IIRFilter_t* filter, const float fcut, const float D, const float Ts)
{
    iirFilterInit(filter, 2);
    notchFilterUpdate(filter, fcut, D, Ts);
}

void notchFilterUpdate(IIRFilter_t* filter, const float fcut, const float D, const float Ts)
{
    const float Q = 1.0f / (2.0f * D);
    // prewarp is done implicitly
    const float omega = 2.0f * M_PIf * fcut * Ts;
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

// Second Order Lowpass Filter
// Time continous prototype: G(s) = wcut^2 / (s^2 + 2 * D * wcut * s + wcut^2)
// Disrectization method: Euler

void lowPassFilter2Init(IIRFilter_t* filter, const float fcut, const float D, const float Ts)
{
    iirFilterInit(filter, 2);
    lowPassFilter2Update(filter, fcut, D, Ts);
}

void lowPassFilter2Update(IIRFilter_t* filter, const float fcut, const float D, const float Ts)
{
    const float wcut = 2.0f * M_PIf * fcut;
    const float k1 = 2.0f * D * Ts * wcut;
        
    filter->A[0] = 1.0f;
    filter->A[2] = 1.0f / (Ts * Ts * wcut * wcut + k1 + 1.0f);
    filter->A[1] = -(k1 + 2.0f) * filter->A[2];
    filter->B[0] = 1.0f + filter->A[1] + filter->A[2];
    filter->B[1] = 0.0f;
    filter->B[2] = 0.0f;
}

float iirFilterApply(IIRFilter_t* filter, const float input)
{
    const float output = filter->B[0] * input + filter->w[0];
    return iirFilterApplyFilterUpdate(filter, input, output);
}

float iirFilterApplyConstrained(IIRFilter_t* filter, const float input, const float yMin, const float yMax)
{
    const float outputUnconstrained = filter->B[0] * input + filter->w[0];

    // constrain output
    const float output = (outputUnconstrained < yMin) ? yMin
                       : (outputUnconstrained > yMax) ? yMax
                       :  outputUnconstrained;

    return iirFilterApplyFilterUpdate(filter, input, output);
}

void iirFilterInit(IIRFilter_t* filter, const unsigned order)
{
    filter->order = order;
    for (unsigned i = 0; i < filter->order; ++i) {
        filter->w[i] = 0.0f;
    }
}

float iirFilterApplyFilterUpdate(IIRFilter_t* filter, const float input, const float output)
{
    // https://dsp.stackexchange.com/questions/72575/transposed-direct-form-ii
    for (unsigned i = 0; i < filter->order - 1; ++i) {
        filter->w[i] = filter->B[i + 1] * input + filter->w[i + 1] - filter->A[i + 1] * output;
    }
    filter->w[filter->order - 1] = filter->B[filter->order] * input - filter->A[filter->order] * output;

    return output;
}