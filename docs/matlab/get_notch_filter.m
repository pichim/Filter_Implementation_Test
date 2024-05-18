function G = get_notch_filter(f, D, Ts)

    Q = 1/2/D;
    % prewarp is done implicitly
    omega = 2*pi*f*Ts;
    sn = sin(omega);
    cs = cos(omega);
    alpha = sn / (2 * Q);
    b2 = 1 / (1 + alpha);
    b1 = -2 * cs / (1 + alpha);
    b0 = b2;
    a1 = b1;
    a0 = (1 - alpha) / (1 + alpha);

    B = [b2 b1 b0];
    A = [1 a1 a0];

    G = tf(B, A, Ts);
    set(G, 'variable', 'z^-1');

end

