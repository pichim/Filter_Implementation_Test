#include "IIRFilter.h"

#include <math.h>

#ifndef M_PIf
    #define M_PIf 3.14159265358979323846f /* pi */
#endif

// Integrator
// Time continous prototype: G(s) = 1 / s
// Disrectization method: Euler

void IIRFilter::integratorInit(const float Ts)
{
    filter.order = 1;
    integratorUpdate(Ts);
    reset(0.0f);
}

void IIRFilter::integratorUpdate(const float Ts)
{
    filter.B[0] = Ts;
    filter.B[1] = 0.0f;
    filter.B[2] = 0.0f;
    filter.A[0] = -1.0f;
    filter.A[1] = 0.0f;
}

// Differentiator
// Time continous prototype: G(s) = s
// Disrectization method: Euler

void IIRFilter::differentiatorInit(const float Ts)
{
    filter.order = 1;
    differentiatorUpdate(Ts);
    resetDifferentingFilterToZero(0.0f);
}

void IIRFilter::differentiatorUpdate(const float Ts)
{
    filter.B[0] = 1.0f / Ts;
    filter.B[1] = -1.0f / Ts;
    filter.B[2] = 0.0f;
    filter.A[0] = 0.0f;
    filter.A[1] = 0.0f;
}

// First Order Lowpass Filter
// Time continous prototype: G(s) = wcut / (s +  wcut)
// Disrectization method: ZOH with one additional forward shift, e.g. G(z^-1) = Gzoh(z^-1) * z

void IIRFilter::lowPass1Init(const float fcut, const float Ts)
{
    filter.order = 1;
    lowPass1Update(fcut, Ts);
    reset(0.0f);
}

void IIRFilter::lowPass1Update(const float fcut, const float Ts)
{
    filter.A[1] = 0.0f;
    filter.B[0] = 1.0f - expf(-Ts * 2.0f * M_PIf * fcut);
    filter.B[1] = 0.0f;
    filter.B[2] = 0.0f;
    filter.A[0] = filter.B[0] - 1.0f;
}

void IIRFilter::differentiatingLowPass1Init(const float fcut, const float Ts)
{
    filter.order = 1;
    differentiatingLowPass1Update(fcut, Ts);
    resetDifferentingFilterToZero(0.0f);
}

void IIRFilter::differentiatingLowPass1Update(const float fcut, const float Ts)
{
    const float b0 = 1.0f - expf(-Ts * 2.0f * M_PIf * fcut);
    filter.A[1] = 0.0f;
    filter.B[0] = b0 / Ts;
    filter.B[1] = -filter.B[0];
    filter.B[2] = 0.0f;
    filter.A[0] = b0 - 1.0f;
}

// First Order Lead or Lag Filter
// Time continous prototype: G(s) = (wPole / wZero) * (s + wZero) / (s + wPole)
// Disrectization method: Tustin with prewarping

void IIRFilter::leadLag1Init(const float fZero, const float fPole, const float Ts)
{
    filter.order = 1;
    leadLag1Update(fZero, fPole, Ts);
    reset(0.0f);
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
    filter.order = 1;
    phaseComp1Update(fCenter, phaseLift, Ts);
    reset(0.0f);
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
    filter.B[2] = 0.0f;
    filter.A[0] = (1.0f - alpha) * k;
    filter.A[1] = 0.0f;
}

// Second Order Notch Filter
// Time continous prototype: G(s) = (s^2 + wcut^2) / (s^2 + 2 * D * wcut * s + wcut^2)
// Disrectization method: Tustin with prewarping

void IIRFilter::notchInit(const float fcut, const float D, const float Ts)
{
    filter.order = 2;
    notchUpdate(fcut, D, Ts);
    reset(0.0f);
}

void IIRFilter::notchUpdate(const float fcut, const float D, const float Ts)
{
    const float Q = 1.0f / (2.0f * D);
    // prewarp is done implicitly
    const float omega = 2.0f * M_PIf * fcut * Ts;
    const float sn = sinf(omega);
    const float cs = cosf(omega);
    const float alpha = sn / (2.0f * Q);

    filter.B[0] = 1.0f / (1.0f + alpha);
    filter.B[1] = -2.0f * cs * filter.B[0];
    filter.B[2] = filter.B[0];
    filter.A[1] = (1.0f - alpha) * filter.B[0];
    filter.A[0] = filter.B[1];
}

// Second Order Lowpass Filter
// Time continous prototype: G(s) = wcut^2 / (s^2 + 2 * D * wcut * s + wcut^2)
// Disrectization method: Euler

void IIRFilter::lowPass2Init(const float fcut, const float D, const float Ts)
{
    filter.order = 2;
    lowPass2Update(fcut, D, Ts);
    reset(0.0f);
}

void IIRFilter::lowPass2Update(const float fcut, const float D, const float Ts)
{
    const float wcut = 2.0f * M_PIf * fcut;
    const float k1 = 2.0f * D * Ts * wcut;
        
    filter.A[1] = 1.0f / (Ts * Ts * wcut * wcut + k1 + 1.0f);
    filter.B[0] = 1.0f - filter.A[1] * (1.0f + k1);
    filter.B[1] = 0.0f;
    filter.B[2] = 0.0f;
    filter.A[0] = filter.B[0] - 1.0f - filter.A[1];
}

// Second Order Lead or Lag Filter
// Time continous prototype: G(s) = (wPole^2 / wZero^2) * (s^2 + 2*DZero*wZero*s + wZero^2) / (s^2 + 2*DPole*wPole*s + wPole^2)
// Disrectization method: Tustin with prewarping

void IIRFilter::leadLag2Init(const float fZero, const float DZero, const float fPole, const float DPole, const float Ts)
{
    filter.order = 2;
    leadLag2Update(fZero, DZero, fPole, DPole, Ts);
    reset(0.0f);
}

void IIRFilter::leadLag2Update(const float fZero, const float DZero, const float fPole, const float DPole, const float Ts)
{
    // prewarping
    const float wZero = (2.0f / Ts) * tanf(M_PIf * fZero * Ts);
    const float wPole = (2.0f / Ts) * tanf(M_PIf * fPole * Ts);

    const float k0 = wPole * wPole;
    const float k1 = wZero * wZero;
    const float k2 = Ts * Ts * k0 * k1;
    const float k3 = DPole * Ts * wPole * k1;
    const float k4 = DZero * Ts * k0 * wZero;
    const float k5 = 1.0f / (k2 + 4.0f * (k1 + k3));
                
    filter.B[0] = (k2 + 4.0f * (k4 + k0)) * k5;
    filter.B[1] = 2.0f * (k2 - 4.0f * k0) * k5;
    filter.B[2] = (k2 + 4.0f * (k0 - k4)) * k5;
    filter.A[1] = (k2 + 4.0f * (k1 - k3)) * k5;
    filter.A[0] = filter.B[0] + filter.B[1] + filter.B[2] - 1.0f - filter.A[1];
}

void IIRFilter::reset(const float output)
{
    filter.w[0] = output * (1.0f - filter.B[0]);
    if (filter.order == 2)
        filter.w[1] = filter.w[0] + output * (filter.A[0] - filter.B[1]);
}

// Assuming a constant input, differentiating results in zero output
// Currently only implemented for first order differentiators

void IIRFilter::resetDifferentingFilterToZero(const float output)
{
    filter.w[0] = output * filter.B[1];
}

float IIRFilter::apply(const float input)
{
    const float output = filter.B[0] * input + filter.w[0];
    applyFilterUpdate(input, output);

    return output;
}

float IIRFilter::applyConstrained(const float input, const float yMin, const float yMax)
{
    // constrain output
    const float outputUnconstrained = filter.B[0] * input + filter.w[0];
    const float output = (outputUnconstrained < yMin) ? yMin
                       : (outputUnconstrained > yMax) ? yMax
                       :  outputUnconstrained;
    applyFilterUpdate(input, output);

    return output;
}

void IIRFilter::applyFilterUpdate(const float input, const float output)
{
    // https://dsp.stackexchange.com/questions/72575/transposed-direct-form-ii
    for (unsigned i = 0; i < filter.order - 1; ++i) {
        filter.w[i] = filter.B[i + 1] * input + filter.w[i + 1] - filter.A[i] * output;
    }
    filter.w[filter.order - 1] = filter.B[filter.order] * input - filter.A[filter.order - 1] * output;
}