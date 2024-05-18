#pragma once

#include <cstddef>

#ifndef M_PI
    # define M_PI 3.14159265358979323846
#endif

class IIRFilter2 {
public:
    IIRFilter2();
    virtual ~IIRFilter2() = default;

    virtual void update(const float fcut, const float D, const float Ts) = 0;
    virtual float apply(const float input) = 0;
    virtual float applyConstrained(const float input, const float yMin, const float yMax) = 0;

protected:
    struct IIRFilter2Params {
        static const size_t order = 2;
        float A[order + 1];
        float B[order + 1];
        float w[order];
    } params;

    void initFilter();
    float applyFilter(const float input);
    float applyFilterConstrained(const float input,  float yMin, const float yMax);
    float applyFilterStep(const float input, const float output);
};

class NotchFilter : public IIRFilter2 {
public:
    NotchFilter(const float fcut, const float D, const float Ts);

    void update(const float fcut, const float D, const float Ts) override;
    float apply(const float input) override;
    float applyConstrained(const float input, const float yMin, const float yMax) override;
};

class LowPassFilter2 : public IIRFilter2 {
public:
    LowPassFilter2(const float fcut, const float D, const float Ts);

    void update(const float fcut, const float D, const float Ts) override;
    float apply(const float input) override;
    float applyConstrained(const float input, const float yMin, const float yMax) override;
};