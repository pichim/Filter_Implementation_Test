function G = get_lowpass1(fcut, Ts)

    a1 = -exp(-Ts*2*pi*fcut);
    b0 = (1 + a1);
    
    B = [b0 0];
    A = [1 a1];

    G = tf(B, A, Ts);
    set(G, 'variable', 'z^-1');

end
