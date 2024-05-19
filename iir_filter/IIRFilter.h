#pragma once

#include <math.h>

class IIRFilter {
public:
    IIRFilter() {};
    virtual ~IIRFilter() = default;

    void lowPassFilter1Init(const float fcut, const float Ts);
    void lowPassFilter1Update(const float fcut, const float Ts);
    void notchFilterInit(const float fcut, const float D, const float Ts);
    void notchFilterUpdate(const float fcut, const float D, const float Ts);
    void lowPassFilter2Init(const float fcut, const float D, const float Ts);
    void lowPassFilter2Update(const float fcut, const float D, const float Ts);

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