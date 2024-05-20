function G = get_phase_comp(fCenter, phaseLift, Ts)

    omega = 2.0 * pi * fCenter * Ts;
    sn = sin(phaseLift * pi/180);
    gain = (1 + sn) / (1 - sn);
    alpha = (12 - omega*omega) / (6 * omega * sqrt(gain));  % approximate prewarping (series expansion)
    k = 1.0 / (1.0 + alpha);

    b0 = (1 + alpha * gain) * k;
    b1 = (1 - alpha * gain) * k;
    a1 = (1 - alpha) * k;
    
    B = [b0 b1];
    A = [1 a1];

    G = tf(B, A, Ts);
    set(G, 'variable', 'z^-1');

end

