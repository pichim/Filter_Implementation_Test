#include "pidcontroller.h"

void pidControllerInit(PIDController_t* pidController, const float Kp, const float Ki, const float Kd, const float fcutD, const float fcutRollOff, const float Ts)
{
    pidController->Kp = Kp;
    pidController->Ki = Ki;
    pidController->Kd = Kd;
    pidController->Ts = Ts;
    differentiatingLowPass1Init(&pidController->differentiatingLowPass1, fcutD, Ts);
    lowPass1Init(&pidController->lowPass1, fcutRollOff, Ts);
    pidController->uiPrevious = 0.0f;
}

// It is assumed that the error is zero and all signals are in steady state when this function is called,
// there for up is zero and ud is zero and the steady state output of the pid controller is ui

void pidControllerReset(PIDController_t* pidController, const float ui)
{
    pidController->uiPrevious = ui;
    iirFilterResetDifferentingFilterToZero(&pidController->differentiatingLowPass1, 0.0f);
    iirFilterReset(&pidController->lowPass1, ui);
}

float pidControllerApply(PIDController_t* pidController, const float error)
{
    // initialize the individual terms of the pid controller to zero
    float up, ui, ud;
    up = ui = ud = 0.0f;

    // proportional term
    if (pidController->Kp > 0.0f)
        up = pidController->Kp * error;

    // integral term
    if (pidController->Ki > 0.0f) {
        ui = pidController->Ki * error * pidController->Ts + pidController->uiPrevious;
        pidController->uiPrevious = ui;
    }

    // derivative term
    if (pidController->Kd > 0.0f)
        ud = pidController->Kd * iirFilterApply(&pidController->differentiatingLowPass1, error);
    
    // apply roll off filter
    return iirFilterApply(&pidController->lowPass1, up + ui + ud);
}

float pidControllerApplyConstrained(PIDController_t* pidController, const float error, const float uMin, const float uMax)
{
    // initialize the individual terms of the pid controller to zero
    float up, ui, ud;
    up = ui = ud = 0.0f;

    // proportional term
    if (pidController->Kp > 0.0f)
        up = pidController->Kp * error;

    // constrained integral term
    if (pidController->Ki > 0.0f) {
        ui = pidController->Ki * error * pidController->Ts + pidController->uiPrevious;
        ui = (ui < uMin) ? uMin
           : (ui > uMax) ? uMax
           :  ui;
        pidController->uiPrevious = ui;
    }

    // derivative term
    if (pidController->Kd > 0.0f)
        ud = pidController->Kd * iirFilterApply(&pidController->differentiatingLowPass1, error);
    
    // apply constrained roll off filter
    return iirFilterApplyConstrained(&pidController->lowPass1, up + ui + ud, uMin, uMax);
}