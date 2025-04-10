/*
 * pt1filter.c
 *
 *  Created on: 09.09.2019
 *      Author: hene
 *
 ******************************************************************************
 *
 *      Copyright 2019 ZHAW Zurich University of Applied Science
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

#include "pt1filter.h"

// ****************************************************************************
// regular pt1 functions
// ****************************************************************************

// Calculate pt1 filter coefficiants --> fCutoffFreq - rad/s
void pt1filter_calcCoeff(pt1filter* f, float fCutoffFreq, float fPeriod)
{
    /*
     * Tiefpass kontinuierlich
     *               1
     * G(s) = ----------------
     *        1/cutoff[rad/s] * s + 1
     *
     * Tustin Transformation
     *
     *      2     1 - (z^-1)
     * s = --- * ------------
     *      Ts    1 + (z^-1)
     *
     *         b0 * (1 + z^-1)     y
     * G(z) = ---------------- = ---
     *          1 + a0 * z^-1     u
     *
     *           ________
     *   u      |        |     y
     *   ------>|  G(z)  |---->
     *          |________|
     *
     * u * b0 * (1 + z^-1) = y * (1 + a0 * z^-1)
     *
     * yk = b0 * (uk + uk-1) - a0 * yk-1
     *
     */
    if (fCutoffFreq > 0)
    {
        f->a0 = (fPeriod - 2.0f / fCutoffFreq) / (fPeriod + 2.0f / fCutoffFreq);
        f->b0 = f->b1 = fPeriod / (fPeriod + 2.0f / fCutoffFreq);
    }
    else
    {
    	f->a0 = f->b0 = 0;
    	f->b1 = 1;
    }

    f->fPrevSample = 0;
    f->fPrevFilterOut = 0;

}

// Calculate next pt1 filter step
float pt1filter_calc(pt1filter* f, float fActValue)
{
	float fOut;
	float fSample = fActValue;

    fOut = f->b1 * fSample + f->b0 * f->fPrevSample - f->a0 * f->fPrevFilterOut;

    f->fPrevSample = fSample;
    f->fPrevFilterOut = fOut;

    f->fOut = fOut;
    return fOut;
}

// Set pt1 filter to specific value
void pt1filter_set(pt1filter* f, float fSample) {
	f->fPrevSample = fSample;
	f->fPrevFilterOut = fSample;
	f->fOut = fSample;
}

