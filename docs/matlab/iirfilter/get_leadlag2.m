function G = get_leadlag2(fZero, DZero, fPole, DPole, Ts)

    % prewarp is done implicitly
    omegaZero = 2.0 * pi * fZero * Ts;
    snZero = sin(omegaZero);
    csZero = cos(omegaZero);
    omegaPole = 2.0 * pi * fPole * Ts;
    snPole = sin(omegaPole);
    csPole = cos(omegaPole);
    k0 = 1.0 / (1.0 + DPole * snPole);
    k1 = k0 * (csPole - 1.0) / (csZero - 1.0);

    b0 = (1.0 + DZero * snZero) * k1;
    b1 = -2.0 * csZero * k1;
    b2 = (1.0 - DZero * snZero) * k1;
    a0 = -2.0 * csPole * k0;
    a1 = (1.0 - DPole * snPole) * k0;
    
    B = [b0, b1, b2];
    A = [1, a0, a1];

    G = ss(tf(B, A, Ts));

    % wZero = (2.0 / Ts) * tan(pi * fZero * Ts);
    % wPole = (2.0 / Ts) * tan(pi * fPole * Ts);
    % 
    % k0 = wPole * wPole;
    % k1 = wZero * wZero;
    % k2 = Ts * Ts * k0 * k1;
    % k3 = DPole * Ts * wPole * k1;
    % k4 = DZero * Ts * k0 * wZero;
    % k5 = 1.0 / (k2 + 4.0 * (k1 + k3));
    % 
    % b0 = (k2 + 4.0 * (k4 + k0)) * k5;
    % b1 = 2.0 * (k2 - 4.0 * k0) * k5;
    % b2 = (k2 + 4.0 * (k0 - k4)) * k5;
    % a1 = (k2 + 4.0 * (k1 - k3)) * k5;
    % a0 = b0 + b1 + b2 - 1.0 - a1;
    % 
    % B = [b0, b1, b2];
    % A = [1, a0, a1];
    % 
    % G = ss(tf(B, A, Ts));

end

