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

float pidControllerApply(PIDController_t* pidController, const float error)
{
    const float up = pidController->Kp * error;
    const float ui = pidController->Ki * error * pidController->Ts + pidController->uiPrevious;
    pidController->uiPrevious = ui;
    const float ud = pidController->Kd * iirFilterApply(&pidController->differentiatingLowPass1, error);

    return iirFilterApply(&pidController->lowPass1, up + ui + ud);
}