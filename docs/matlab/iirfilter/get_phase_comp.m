function G = get_phase_comp(fCenter, phaseLift, Ts)

    omega = 2.0 * pi * fCenter * Ts;
    sn = sin(phaseLift * (pi / 180.0));
    gain = (1.0 + sn) / (1.0 - sn);
    alpha = (12.0 - omega * omega) / (6.0 * omega * sqrt(gain)); % approximate prewarping (series expansion)
    k = 1.0 / (1.0 + alpha);

    b0 = (1.0 + alpha * gain) * k;
    b1 = (1.0 - alpha * gain) * k;
    a0 = (1.0 - alpha) * k;
    
    B = [b0, b1];
    A = [1, a0];

    G = ss(tf(B, A, Ts));

end

