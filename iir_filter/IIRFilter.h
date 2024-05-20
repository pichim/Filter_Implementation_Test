#pragma once

#include <math.h>

class IIRFilter {
public:
    IIRFilter() {};
    virtual ~IIRFilter() = default;

    void lowPass1Init(const float fcut, const float Ts);
    void lowPass1Update(const float fcut, const float Ts);

    void leadLag1Init(const float fZero, const float fPole, const float Ts);
    void leadLag1Update(const float fZero, const float fPole, const float Ts);
    void phaseComp1Init(const float fCenter, const float phaseLift, const float Ts);
    void phaseComp1Update(const float fCenter, const float phaseLift, const float Ts);

    void notchInit(const float fcut, const float D, const float Ts);
    void notchUpdate(const float fcut, const float D, const float Ts);

    void lowPass2Init(const float fcut, const float D, const float Ts);
    void lowPass2Update(const float fcut, const float D, const float Ts);

    void init(const unsigned order);
    float apply(const float input);
    float applyConstrained(const float input, const float yMin, const float yMax);

private:
    struct IIRFilterParams{
        unsigned order;
        float A[3];
        float B[3];
        float w[2];
    } filter;

    float applyFilterUpdate(const float input, const float output);
};