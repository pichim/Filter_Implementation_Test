#include "iirfilter.h"

// First Order Lowpass Filter
// Time continous prototype: G(s) = wcut / (s +  wcut)
// Disrectization method: ZOH with one additional forward shift, e.g. G(z^-1) = Gzoh(z^-1) * z

void lowPass1Init(IIRFilter_t* filter, const float fcut, const float Ts)
{
    filter->order = 1;
    lowPass1Update(filter, fcut, Ts);
    iirFilterReset(filter, 0.0f);
}

void lowPass1Update(IIRFilter_t* filter, const float fcut, const float Ts)
{
    filter->A[1] = 0.0f;
    filter->B[0] = 1.0f - expf(-Ts * 2.0f * M_PIf * fcut);
    filter->B[1] = 0.0f;
    filter->B[2] = 0.0f;
    filter->A[0] = filter->B[0] - 1.0f;
}

// First Order Lead or Lag Filter
// Time continous prototype: G(s) = (wPole / wZero) * (s + wZero) / (s + wPole)
// Disrectization method: Tustin with prewarping

void leadLag1Init(IIRFilter_t* filter, const float fZero, const float fPole, const float Ts)
{
    filter->order = 1;
    leadLag1Update(filter, fZero, fPole, Ts);
    iirFilterReset(filter, 0.0f);
}

void leadLag1Update(IIRFilter_t* filter, const float fZero, const float fPole, const float Ts)
{
    const float alpha = fZero / fPole;
    const float fCenter = fPole * sqrtf(alpha);
    const float phaseLift = asinf( (1.0f - alpha) / (1.0f + alpha) ) * (180.0f / M_PIf);
    phaseComp1Update(filter, fCenter, phaseLift, Ts);
}

void phaseComp1Init(IIRFilter_t* filter, const float fCenter, const float phaseLift, const float Ts)
{
    filter->order = 1;
    phaseComp1Update(filter, fCenter, phaseLift, Ts);
    iirFilterReset(filter, 0.0f);
}

void phaseComp1Update(IIRFilter_t* filter, const float fCenter, const float phaseLift, const float Ts)
{
    const float omega = 2.0f * M_PIf * fCenter * Ts;
    const float sn = sinf(phaseLift * (M_PIf / 180.0f));
    const float gain = (1.0f + sn) / (1.0f - sn);
    const float alpha = (12.0f - omega * omega) / (6.0f * omega * sqrtf(gain)); // approximate prewarping (series expansion)
    const float k = 1.0f / (1.0f + alpha);

    filter->B[0] = (1.0f + alpha * gain) * k;
    filter->B[1] = (1.0f - alpha * gain) * k;
    filter->B[2] = 0.0f;
    filter->A[0] = (1.0f - alpha) * k;
    filter->A[1] = 0.0f;
}

// Second Order Notch Filter
// Time continous prototype: G(s) = (s^2 + wcut^2) / (s^2 + 2 * D * wcut * s + wcut^2)
// Disrectization method: Tustin with prewarping

void notchInit(IIRFilter_t* filter, const float fcut, const float D, const float Ts)
{
    filter->order = 2;
    notchUpdate(filter, fcut, D, Ts);
    iirFilterReset(filter, 0.0f);
}

void notchUpdate(IIRFilter_t* filter, const float fcut, const float D, const float Ts)
{
    const float Q = 1.0f / (2.0f * D);
    // prewarp is done implicitly
    const float omega = 2.0f * M_PIf * fcut * Ts;
    const float sn = sinf(omega);
    const float cs = cosf(omega);
    const float alpha = sn / (2.0f * Q);

    filter->B[0] = 1.0f / (1.0f + alpha);
    filter->B[1] = -2.0f * cs * filter->B[0];
    filter->B[2] = filter->B[0];
    filter->A[1] = (1.0f - alpha) * filter->B[0];
    filter->A[0] = filter->B[1];
}

// Second Order Lowpass Filter
// Time continous prototype: G(s) = wcut^2 / (s^2 + 2 * D * wcut * s + wcut^2)
// Disrectization method: Euler

void lowPass2Init(IIRFilter_t* filter, const float fcut, const float D, const float Ts)
{
    filter->order = 2;
    lowPass2Update(filter, fcut, D, Ts);
    iirFilterReset(filter, 0.0f);
}

void lowPass2Update(IIRFilter_t* filter, const float fcut, const float D, const float Ts)
{
    const float wcut = 2.0f * M_PIf * fcut;
    const float k1 = 2.0f * D * Ts * wcut;
        
    filter->A[1] = 1.0f / (Ts * Ts * wcut * wcut + k1 + 1.0f);
    filter->B[0] = 1.0f - filter->A[1] * (1.0f + k1);
    filter->B[1] = 0.0f;
    filter->B[2] = 0.0f;
    filter->A[0] = filter->B[0] - 1.0f - filter->A[1];
}

// Second Order Lead or Lag Filter
// Time continous prototype: G(s) = (wPole^2 / wZero^2) * (s^2 + 2*DZero*wZero*s + wZero^2) / (s^2 + 2*DPole*wPole*s + wPole^2)
// Disrectization method: Tustin with prewarping

void leadLag2Init(IIRFilter_t* filter, const float fZero, const float DZero, const float fPole, const float DPole, const float Ts)
{
    filter->order = 2;
    leadLag2Update(filter, fZero, DZero, fPole, DPole, Ts);
    iirFilterReset(filter, 0.0f);
}

void leadLag2Update(IIRFilter_t* filter, const float fZero, const float DZero, const float fPole, const float DPole, const float Ts)
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
                
    filter->B[0] = (k2 + 4.0f * (k4 + k0)) * k5;
    filter->B[1] = 2.0f * (k2 - 4.0f * k0) * k5;
    filter->B[2] = (k2 + 4.0f * (k0 - k4)) * k5;
    filter->A[1] = (k2 + 4.0f * (k1 - k3)) * k5;
    filter->A[0] = filter->B[0] + filter->B[1] + filter->B[2] - 1.0f - filter->A[1];
}

void iirFilterReset(IIRFilter_t* filter, const float output)
{
    filter->w[0] = output * (1.0f - filter->B[0]);
    if (filter->order == 2)
        filter->w[1] = filter->w[0] + output * (filter->A[0] - filter->B[1]);
}

float iirFilterApply(IIRFilter_t* filter, const float input)
{
    const float output = filter->B[0] * input + filter->w[0];
    iirFilterApplyFilterUpdate(filter, input, output);

    return output;
}

float iirFilterApplyConstrained(IIRFilter_t* filter, const float input, const float yMin, const float yMax)
{
    // constrain output
    const float outputUnconstrained = filter->B[0] * input + filter->w[0];
    const float output = (outputUnconstrained < yMin) ? yMin
                       : (outputUnconstrained > yMax) ? yMax
                       :  outputUnconstrained;
    iirFilterApplyFilterUpdate(filter, input, output);

    return output;
}

void iirFilterApplyFilterUpdate(IIRFilter_t* filter, const float input, const float output)
{
    // https://dsp.stackexchange.com/questions/72575/transposed-direct-form-ii
    for (unsigned i = 0; i < filter->order - 1; ++i) {
        filter->w[i] = filter->B[i + 1] * input + filter->w[i + 1] - filter->A[i] * output;
    }
    filter->w[filter->order - 1] = filter->B[filter->order] * input - filter->A[filter->order - 1] * output;
}