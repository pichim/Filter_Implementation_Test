#include "FadingNotchFilter.h"

void FadingNotchFilter::fadingNotchInit(const float fcut, const float D, const float fFadeMin, const float fFadeMax, const float Ts)
{
    fadingNotch.D = D;
    fadingNotch.fFadeMin = fFadeMin;
    fadingNotch.fFadeMax = fFadeMax;
    fadingNotch.Ts = Ts;
    fadingNotch.filter.notchInit(fcut, D, Ts);
}

void FadingNotchFilter::reset(const float fcut, const float output)
{
    fadingNotch.filter.notchUpdate(fcut, fadingNotch.D, fadingNotch.Ts);
    fadingNotch.filter.reset(output);
}

float FadingNotchFilter::apply(const float fcut, const float input)
{
    fadingNotch.filter.notchUpdate(fcut, fadingNotch.D, fadingNotch.Ts);

    return applyFading(fcut, input, fadingNotch.filter.apply(input));
}

float FadingNotchFilter::applyConstrained(const float fcut, const float input, const float yMin, const float yMax)
{
    fadingNotch.filter.notchUpdate(fcut, fadingNotch.D, fadingNotch.Ts);

    return applyFading(fcut, input, fadingNotch.filter.applyConstrained(input, yMin, yMax));
}

float FadingNotchFilter::applyFading(const float fcut, const float input, const float output)
{
    if (fcut < fadingNotch.fFadeMin) 
        return input;
    else if (fcut > fadingNotch.fFadeMax)
        return output;
    else {
        const float w = (fcut - fadingNotch.fFadeMin) / (fadingNotch.fFadeMax - fadingNotch.fFadeMin);
        return (1.0f - w) * input + w * output;
    }
}       