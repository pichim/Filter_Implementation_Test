#pragma once

#include <cstddef>

#ifndef M_PI
    # define M_PI 3.14159265358979323846
#endif

class IIRFilter {
public:
    IIRFilter(const size_t order);
    virtual ~IIRFilter() = default;

    virtual float apply(const float input) = 0;
    virtual float applyConstrained(const float input, const float yMin, const float yMax) = 0;

protected:
    struct IIRFilterParams {
        size_t order;
        float A[3];
        float B[3];
        float w[2];
    } params;

    void initFilter();
    float applyFilter(const float input);
    float applyFilterConstrained(const float input, float yMin, float yMax);
    float applyFilterStep(const float input, const float output);
};

class IIRFilter1 : public IIRFilter {
public:
    IIRFilter1();
    virtual float apply(const float input) = 0;
    virtual float applyConstrained(const float input, const float yMin, const float yMax) = 0;
private:
    static constexpr size_t order = 1;
};

class LowPassFilter1 : public IIRFilter1 {
public:
    LowPassFilter1(const float fcut, const float Ts);

    void update(const float fcut, const float Ts);
    
    float apply(const float input) override;
    float applyConstrained(const float input, const float yMin, const float yMax) override;
};

class IIRFilter2 : public IIRFilter {
public:
    IIRFilter2();
    virtual float apply(const float input) = 0;
    virtual float applyConstrained(const float input, const float yMin, const float yMax) = 0;
private:
    static constexpr size_t order = 2;
};

class NotchFilter : public IIRFilter2 {
public:
    NotchFilter(const float fcut, const float D, const float Ts);

    void update(const float fcut, const float D, const float Ts);

    float apply(const float input) override;
    float applyConstrained(const float input, const float yMin, const float yMax) override;
};

class LowPassFilter2 : public IIRFilter2 {
public:
    LowPassFilter2(const float fcut, const float D, const float Ts);

    void update(const float fcut, const float D, const float Ts);
    
    float apply(const float input) override;
    float applyConstrained(const float input, const float yMin, const float yMax) override;
};