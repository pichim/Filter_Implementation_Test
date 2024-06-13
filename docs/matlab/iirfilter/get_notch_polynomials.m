function [B, A] = get_notch_polynomials(fcut, D, Ts)

    % prewarp is done implicitly
    omega = 2.0 * pi * fcut * Ts;
    sn = sin(omega);
    cs = cos(omega);

    b0 = 1.0 / (1.0 + D * sn);
    b1 = -2.0 * cs * b0;
    b2 = b0;
    a0 = b1;
    a1 = (1.0 - D * sn) * b0;

    B = [b0, b1, b2];
    A = [1, a0, a1];

end

