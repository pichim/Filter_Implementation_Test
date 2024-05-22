function G = get_notch(fcut, D, Ts)

    Q = 1 / (2*D);
    % prewarp is done implicitly
    omega = 2*pi*fcut*Ts;
    sn = sin(omega);
    cs = cos(omega);
    alpha = sn / (2 * Q);

    b0 = 1 / (1 + alpha);
    b1 = -2 * cs / (1 + alpha);
    b2 = b0;
    a1 = b1;
    a2 = (1 - alpha) / (1 + alpha);

    B = [b0 b1 b2];
    A = [1 a1 a2];

    G = ss(tf(B, A, Ts));

end

