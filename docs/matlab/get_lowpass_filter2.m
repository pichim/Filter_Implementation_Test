function G = get_lowpass_filter2(f, D, Ts)

    w = 2*pi*f;
    k1 = 2*D*Ts*w;
    a0 = 1/(Ts^2*w^2 + k1 + 1);
    a1 = -(k1 + 2) * a0;
    b2 = (1 + a1 + a0);

    B = [b2 0 0];
    A = [1 a1 a0];

    G = tf(B, A, Ts);
    set(G, 'variable', 'z^-1');

end

