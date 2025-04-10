#pragma once

#include "IIRFilter.h"

class FadingNotchFilter{
public:
    FadingNotchFilter() {};
    virtual ~FadingNotchFilter() = default;

    void fadingNotchInit(const float fcut, const float D, const float fFadeMin, const float fFadeMax, const float Ts);

    void reset(const float fcut, const float output);
    float apply(const float fcut, const float input);
    float applyConstrained(const float fcut, const float input, const float yMin, const float yMax);

private:
    struct FadingNotchFilterParams{
        float D, Ts, fFadeMin, fFadeMax;
        IIRFilter notch;
    } fadingNotch;

    float applyFading(const float fcut, const float input, const float output);
};
