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

float PIDController::apply(const float error)
{
    const float up = pidController.Kp * error;
    const float ui = pidController.Ki * error * pidController.Ts + pidController.uiPrevious;
    pidController.uiPrevious = ui;
    const float ud = pidController.Kd * pidController.differentiatingLowPass1.apply(error);

    return pidController.lowPass1.apply(up + ui + ud);
}