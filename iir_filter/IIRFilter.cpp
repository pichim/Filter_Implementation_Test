#include "IIRFilter.h"

// First Order Lowpass Filter
// Time continous prototype: G(s) = wcut / (s +  wcut)
// Disrectization method: ZOH with one additional forward shift, e.g. G(z^-1) = Gzoh(z^-1) * z

void IIRFilter::lowPass1Init(const float fcut, const float Ts)
{
    init(1);
    lowPass1Update(fcut, Ts);
}

void IIRFilter::lowPass1Update(const float fcut, const float Ts)
{
    filter.A[0] = 1.0f;
    filter.A[1] = -expf(-Ts * 2.0f * M_PIf * fcut);
    filter.B[0] = 1.0f + filter.A[1];
    filter.B[1] = 0.0f;
}

// First Order Lead or Lag Filter
// Time continous prototype: G(s) = (wPole / wZero) * (s + wZero) / (s + wPole)
// Disrectization method: Tustin with prewarping

void IIRFilter::leadLag1Init(const float fZero, const float fPole, const float Ts)
{
    init(1);
    leadLag1Update(fZero, fPole, Ts);
}

void IIRFilter::leadLag1Update(const float fZero, const float fPole, const float Ts)
{
    const float alpha = fZero / fPole;
    const float fCenter = fPole * sqrtf(alpha);
    const float phaseLift = asinf( (1.0f - alpha) / (1.0f + alpha) ) * (180.0f / M_PIf);
    phaseComp1Update(fCenter, phaseLift, Ts);
}

void IIRFilter::phaseComp1Init(const float fCenter, const float phaseLift, const float Ts)
{
    init(1);
    phaseComp1Update(fCenter, phaseLift, Ts);
}

void IIRFilter::phaseComp1Update(const float fCenter, const float phaseLift, const float Ts)
{
    const float omega = 2.0f * M_PIf * fCenter * Ts;
    const float sn = sinf(phaseLift * (M_PIf / 180.0f));
    const float gain = (1.0f + sn) / (1.0f - sn);
    const float alpha = (12.0f - omega * omega) / (6.0f * omega * sqrtf(gain)); // approximate prewarping (series expansion)
    const float k = 1.0f / (1.0f + alpha);

    filter.B[0] = (1.0f + alpha * gain) * k;
    filter.B[1] = (1.0f - alpha * gain) * k;
    filter.A[1] = (1.0f - alpha) * k;
}

// Second Order Notch Filter
// Time continous prototype: G(s) = (s^2 + 2 * D * wcut * s + wcut^2) / (s^2 + wcut^2)
// Disrectization method: Tustin with prewarping

void IIRFilter::notchInit(const float fcut, const float D, const float Ts)
{
    init(2);
    notchUpdate(fcut, D, Ts);
}

void IIRFilter::notchUpdate(const float fcut, const float D, const float Ts)
{
    // IIRFilter_t* filter = &notch->filter;

    const float Q = 1.0f / (2.0f * D);
    // prewarp is done implicitly
    const float omega = 2.0f * M_PIf * fcut * Ts;
    const float sn = sinf(omega);
    const float cs = cosf(omega);
    const float alpha = sn / (2.0f * Q);

    filter.B[0] = 1.0f / (1.0f + alpha);
    filter.B[1] = -2.0f * cs / (1.0f + alpha);
    filter.B[2] = filter.B[0];
    filter.A[0] = 1.0f;
    filter.A[1] = filter.B[1];
    filter.A[2] = (1.0f - alpha) / (1.0f + alpha);
}

// Second Order Lowpass Filter
// Time continous prototype: G(s) = wcut^2 / (s^2 + 2 * D * wcut * s + wcut^2)
// Disrectization method: Euler

void IIRFilter::lowPass2Init(const float fcut, const float D, const float Ts)
{
    init(2);
    lowPass2Update(fcut, D, Ts);
}

void IIRFilter::lowPass2Update(const float fcut, const float D, const float Ts)
{
    const float wcut = 2.0f * M_PIf * fcut;
    const float k1 = 2.0f * D * Ts * wcut;
        
    filter.A[0] = 1.0f;
    filter.A[2] = 1.0f / (Ts * Ts * wcut * wcut + k1 + 1.0f);
    filter.A[1] = -(k1 + 2.0f) * filter.A[2];
    filter.B[0] = 1.0f + filter.A[1] + filter.A[2];
    filter.B[1] = 0.0f;
    filter.B[2] = 0.0f;
}

void IIRFilter::init(const unsigned order)
{
    filter.order = order;
    for (unsigned i = 0; i < filter.order; ++i) {
        filter.w[i] = 0.0f;
    }
}

float IIRFilter::apply(const float input)
{
    const float output = filter.B[0] * input + filter.w[0];
    return applyFilterUpdate(input, output);
}

float IIRFilter::applyConstrained(const float input, const float yMin, const float yMax)
{
    const float outputUnconstrained = filter.B[0] * input + filter.w[0];

    // constrain output
    const float output = (outputUnconstrained < yMin) ? yMin
                       : (outputUnconstrained > yMax) ? yMax
                       :  outputUnconstrained;

    return applyFilterUpdate(input, output);
}

float IIRFilter::applyFilterUpdate(const float input, const float output)
{
    // https://dsp.stackexchange.com/questions/72575/transposed-direct-form-ii
    for (unsigned i = 0; i < filter.order - 1; ++i) {
        filter.w[i] = filter.B[i + 1] * input + filter.w[i + 1] - filter.A[i + 1] * output;
    }
    filter.w[filter.order - 1] = filter.B[filter.order] * input - filter.A[filter.order] * output;

    return output;
}