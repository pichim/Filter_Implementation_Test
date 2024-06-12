#pragma once

#include "IIRFilter.h"

class PIDController{
public:
    PIDController() {};
    virtual ~PIDController() = default;

    void pidControllerInit(const float Kp, const float Ki, const float Kd, const float fcutD, const float fcutRollOff, const float Ts);

    float apply(const float error); 

private:
    struct PIDControllerParams{
        float Kp, Ki, Kd, Ts;
        IIRFilter differentiatingLowPass1;
        IIRFilter lowPass1;
        float uiPrevious;
    } pidController;
};