function G = get_lowpass2(fcut, D, Ts)

    wcut = 2*pi*fcut;
    k1 = 2*D*Ts*wcut;
    
    a0 = 1/(Ts^2*wcut^2 + k1 + 1);
    a1 = -(k1 + 2) * a0;
    b2 = (1 + a1 + a0);

    B = [b2 0 0];
    A = [1 a1 a0];

    G = tf(B, A, Ts);
    set(G, 'variable', 'z^-1');

end

