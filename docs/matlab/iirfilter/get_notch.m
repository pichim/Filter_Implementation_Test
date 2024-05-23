function G = get_notch(fcut, D, Ts)

    Q = 1.0 / (2.0 * D);
    % prewarp is done implicitly
    omega = 2.0 * pi * fcut * Ts;
    sn = sin(omega);
    cs = cos(omega);
    alpha = sn / (2.0 * Q);

    b0 = 1.0 / (1.0 + alpha);
    b1 = -2.0 * cs * b0;
    b2 = b0;
    a1 = (1.0 - alpha) * b0;
    a0 = b1;

    B = [b0, b1, b2];
    A = [1, a0, a1];

    G = ss(tf(B, A, Ts));

end

