function G = get_lowpass2(fcut, D, Ts)

    wcut = 2*pi*fcut;
    k1 = 2*D*Ts*wcut;
    
    a2 = 1/(Ts^2*wcut^2 + k1 + 1);
    a1 = -(k1 + 2) * a2;
    b0 = (1 + a1 + a2);

    B = [b0 0 0];
    A = [1 a1 a2];

    G = tf(B, A, Ts);
    set(G, 'variable', 'z^-1');

end

