function G = get_integrator(Ts)
    
    B = [Ts, 0.0];
    A = [1.0, -1.0];

    G = ss(tf(B, A, Ts));

end