function G = get_lowpass_filter1(f, Ts)

    a0 = -exp(-Ts*2*pi*f);
    a1 = 1;
    b0 = 0;
    b1 = (1 + a0);
    
    Gd = tf([b1 b0], [a1 a0], Ts);

    B = [b1 b0];
    A = [a1 a0];

    G = tf(B, A, Ts);
    set(G, 'variable', 'z^-1');

end

