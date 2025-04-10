#pragma once

#include "iirfilter_c.h"

typedef struct PIDController_s{
    float Kp, Ki, Kd, fcutD, fcutRollOff, Ts;
    IIRFilter_t differentiatingLowPass1;
    IIRFilter_t lowPass1;
    float uiPrevious;
} PIDController_t;

void pidt2ControllerInit(PIDController_t* pidController, const float Kp, const float Ki, const float Kd, const float fcutD, const float fcutRollOff, const float Ts);
void piControllerInit(PIDController_t* pidController, const float Kp, const float Ki, const float Ts);
void pdt1ControllerInit(PIDController_t* pidController, const float Kp, const float Kd, const float fcutD, const float Ts);
void pdt1ControllerInit(PIDController_t* pidController, const float Kp, const float Kd, const float fcutD, const float fcutRollOff, const float Ts);
void pidControllerReset(PIDController_t* pidController, const float ui);
float pidControllerApply(PIDController_t* pidController, const float error);
float pidControllerApplyConstrained(PIDController_t* pidController, const float error, const float uMin, const float uMax);
