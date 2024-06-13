function G = get_leadlag1(fZero, fPole, Ts)

    wZero = (2.0 / Ts) * tan(pi * fZero * Ts);
    wPole = (2.0 / Ts) * tan(pi * fPole * Ts);
    k = 1.0 / (Ts * wPole + 2.0);
    b0 = wPole * (Ts*wZero + 2.0) / wZero * k;
    b1 = wPole * (Ts*wZero - 2.0) / wZero * k;
    a0 = (Ts * wPole - 2.0) * k;

    B = [b0, b1];
    A = [1, a0];

    G = ss(tf(B, A, Ts));

    % % prewarp is done implicitly
    % omegaZero = 2.0 * pi * fZero * Ts;
    % snZero = sin(omegaZero);
    % csZero = cos(omegaZero);
    % omegaPole = 2.0 * pi * fPole * Ts;
    % snPole = sin(omegaPole);
    % csPole = cos(omegaPole);
    % k0 = 1.0 / (snPole - csPole + 1.0);
    % k1 = k0 / (csZero - 1.0);
    % 
    % b0 = -(1.0 - csPole) * (snZero - csZero + 1) * k1;
    % b1 =  (1.0 - csPole) * (csZero + snZero - 1) * k1;
    % a0 =  (1.0 - csPole - snPole) * k0;
    % 
    % B = [b0, b1];
    % A = [1, a0];
    % 
    % G = ss(tf(B, A, Ts));

end

