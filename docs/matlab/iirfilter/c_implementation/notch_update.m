function filter = notch_update(filter, fcut, D, Ts)

    Q = 1.0 / (2.0 * D);
    % prewarp is done implicitly
    omega = 2.0 * pi * fcut * Ts;
    sn = sin(omega);
    cs = cos(omega);
    alpha = sn / (2.0 * Q);

    filter.B(1) = 1.0 / (1.0 + alpha);
    filter.B(2) = -2.0 * cs * filter.B(1);
    filter.B(3) = filter.B(1);
    filter.A(2) = (1.0 - alpha) * filter.B(1);
    filter.A(1) = filter.B(2);

end
