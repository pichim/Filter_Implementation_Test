function G = get_differentiator(Ts)
    
    B = [1.0 / Ts, -1.0 / Ts];
    A = [1.0, 0];

    G = ss(tf(B, A, Ts));

end