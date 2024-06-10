function G = get_notch(fcut, D, Ts)

    [B, A] = get_notch_polynomials(fcut, D, Ts);

    G = ss(tf(B, A, Ts));

end

