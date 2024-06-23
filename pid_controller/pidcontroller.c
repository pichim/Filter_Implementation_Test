#include "pidcontroller.h"

void pidt2ControllerInit(PIDController_t* pidController, const float Kp, const float Ki, const float Kd, const float fcutD, const float fcutRollOff, const float Ts)
{
    pidController->Kp = Kp;
    pidController->Ki = Ki;
    pidController->Kd = Kd;
    pidController->fcutD = fcutD;
    pidController->fcutRollOff = fcutRollOff;
    pidController->Ts = Ts;
    differentiatingLowPass1Init(&pidController->differentiatingLowPass1, fcutD, Ts);
    lowPass1Init(&pidController->lowPass1, fcutRollOff, Ts);
    pidController->uiPrevious = 0.0f;
}

void piControllerInit(PIDController_t* pidController, const float Kp, const float Ki, const float Ts)
{
    pidt2ControllerInit(pidController, Kp, Ki, 0.0f, 0.0f, 0.0f, Ts);
}

void pdt1ControllerInit(PIDController_t* pidController, const float Kp, const float Kd, const float fcutD, const float Ts)
{
    pidt2ControllerInit(pidController, Kp, 0.0f, Kd, fcutD, 0.0f, Ts);
}

void pdt1ControllerInit(PIDController_t* pidController, const float Kp, const float Kd, const float fcutD, const float fcutRollOff, const float Ts)
{
    pidt2ControllerInit(pidController, Kp, 0.0f, Kd, fcutD, fcutRollOff, Ts);
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
    if (pidController->fcutRollOff > 0.0f)
        return iirFilterApply(&pidController->lowPass1, up + ui + ud);
    else
        return up + ui + ud;
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
    if (pidController->fcutRollOff > 0.0f)
        return iirFilterApplyConstrained(&pidController->lowPass1, up + ui + ud, uMin, uMax);
    else {
        const float u = up + ui + ud;
        return (u < uMin) ? uMin
             : (u > uMax) ? uMax
             :  u;
    }
}