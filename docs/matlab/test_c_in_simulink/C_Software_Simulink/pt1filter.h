/*
 * pt1filter.h
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

#ifndef PT1FILTER_H_
#define PT1FILTER_H_

#include "stdint.h"

typedef struct {
	float a0;
	float b0;
	float b1;
	float fPrevSample;
	float fPrevFilterOut;
	float fOut;
} pt1filter;

void pt1filter_calcCoeff(pt1filter* f, float fCutoffFreq, float fPeriod);
float pt1filter_calc(pt1filter* f, float fActValue);
void pt1filter_set(pt1filter* f, float fSample);

#endif /* PT1FILTER_H_ */
