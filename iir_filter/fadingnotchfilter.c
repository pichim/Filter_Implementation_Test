#include "fadingnotchfilter_c.h"

void fadingNotchInit(FadingNotchFilter_t* fadingNotch, const float fcut, const float D, const float fFadeMin, const float fFadeMax, const float Ts)
{
    fadingNotch->D = D;
    fadingNotch->fFadeMin = fFadeMin;
    fadingNotch->fFadeMax = fFadeMax;
    fadingNotch->Ts = Ts;
    notchInit(&fadingNotch->notch, fcut, D, Ts);
}

void fadingNotchFilterReset(FadingNotchFilter_t* fadingNotch, const float fcut, const float output)
{
    notchUpdate(&fadingNotch->notch, fcut, fadingNotch->D, fadingNotch->Ts);
    iirFilterReset(&fadingNotch->notch, output);
}

float fadingNotchFilterApply(FadingNotchFilter_t* fadingNotch, const float fcut, const float input)
{
    notchUpdate(&fadingNotch->notch, fcut, fadingNotch->D, fadingNotch->Ts);

    return fadingNotchFilterApplyFading(fadingNotch, fcut, input, iirFilterApply(&fadingNotch->notch, input));
}

float fadingNotchFilterApplyConstrained(FadingNotchFilter_t* fadingNotch, const float fcut, const float input, const float yMin, const float yMax)
{
    notchUpdate(&fadingNotch->notch, fcut, fadingNotch->D, fadingNotch->Ts);

    return fadingNotchFilterApplyFading(fadingNotch, fcut, input, iirFilterApplyConstrained(&fadingNotch->notch, input, yMin, yMax));
}

float fadingNotchFilterApplyFading(FadingNotchFilter_t* fadingNotch, const float fcut, const float input, const float output)
{
    if (fcut < fadingNotch->fFadeMin) 
        return input;
    else if (fcut > fadingNotch->fFadeMax)
        return output;
    else {
        const float w = (fcut - fadingNotch->fFadeMin) / (fadingNotch->fFadeMax - fadingNotch->fFadeMin);
        return (1.0f - w) * input + w * output;
    }
}
