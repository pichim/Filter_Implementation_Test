function G = get_pid_controller(Kp, Ki, Kd, fcutD, fcutRollOff, Ts)

    G = ss( (Kp + ...
             Ki * get_integrator(Ts) + ...
             Kd * get_differentiating_lowpass1(fcutD, Ts)) * get_lowpass1(fcutRollOff, Ts) );

end

