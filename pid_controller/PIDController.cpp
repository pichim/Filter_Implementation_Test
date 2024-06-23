#include "PIDController.h"

void PIDController::pidControllerInit(const float Kp, const float Ki, const float Kd, const float fcutD, const float fcutRollOff, const float Ts)
{
    pidController.Kp = Kp;
    pidController.Ki = Ki;
    pidController.Kd = Kd;
    pidController.Ts = Ts;
    pidController.differentiatingLowPass1.differentiatingLowPass1Init(fcutD, Ts);
    pidController.lowPass1.lowPass1Init(fcutRollOff, Ts);
    pidController.uiPrevious = 0.0f;
}

// It is assumed that the error is zero and all signals are in steady state when this function is called,
// there for up is zero and ud is zero and the steady state output of the pid controller is ui

void PIDController::reset(const float ui)
{
    pidController.uiPrevious = ui;
    pidController.differentiatingLowPass1.resetDifferentingFilterToZero(0.0f);
    pidController.lowPass1.reset(ui);
}

float PIDController::apply(const float error)
{
    // initialize the individual terms of the pid controller to zero
    float up, ui, ud;
    up = ui = ud = 0.0f;

    // proportional term
    if (pidController.Kp > 0.0f)
        up = pidController.Kp * error;

    // integral term
    if (pidController.Ki > 0.0f) {
        ui = pidController.Ki * error * pidController.Ts + pidController.uiPrevious;
        pidController.uiPrevious = ui;
    }

    // derivative term
    if (pidController.Kd > 0.0f)
        ud = pidController.Kd * pidController.differentiatingLowPass1.apply(error);

    // apply roll off filter
    return pidController.lowPass1.apply(up + ui + ud);
}

float PIDController::applyConstrained(const float error, const float uMin, const float uMax)
{
    // initialize the individual terms of the pid controller to zero
    float up, ui, ud;
    up = ui = ud = 0.0f;

    // proportional term
    if (pidController.Kp > 0.0f)
        up = pidController.Kp * error;

    // constrained integral term
    if (pidController.Ki > 0.0f) {
        ui = pidController.Ki * error * pidController.Ts + pidController.uiPrevious;
        ui = (ui < uMin) ? uMin
           : (ui > uMax) ? uMax
           :  ui;
        pidController.uiPrevious = ui;
    }

    // derivative term
    if (pidController.Kd > 0.0f)
        ud = pidController.Kd * pidController.differentiatingLowPass1.apply(error);

    // apply constrained roll off filter
    return pidController.lowPass1.applyConstrained(up + ui + ud, uMin, uMax);
}