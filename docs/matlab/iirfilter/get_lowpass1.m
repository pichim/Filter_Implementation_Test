function G = get_lowpass1(fcut, Ts)

    a0 = -exp(-Ts*2*pi*fcut);
    b0 = 0;
    b1 = (1 + a0);
    
    B = [b1 b0];
    A = [1 a0];

    G = tf(B, A, Ts);
    set(G, 'variable', 'z^-1');

end

