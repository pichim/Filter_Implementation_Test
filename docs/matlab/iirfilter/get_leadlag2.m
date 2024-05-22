function G = get_leadlag2(fZero, DZero, fPole, DPole, Ts)

    wZero = 2*pi*fZero;
    wPole = 2*pi*fPole;

    wZero = 2/Ts * tan(wZero*Ts/2);
    wPole = 2/Ts * tan(wPole*Ts/2);

    k0 = wPole * wPole;
    k1 = wZero * wZero;
    k2 = Ts * Ts * k0 * k1;
    k3 = DPole * Ts * wPole * k1;
    k4 = DZero * Ts * k0 * wZero;
    k5 = 1 / (k2 + 4*(k1 + k3));
    
    b0 = (k2 + 4*(k4 + k0)) * k5;
    b1 = 2*(k2 - 4*k0) * k5;
    b2 = (k2 + 4*(k0 - k4)) * k5;
    a1 = 2*(k2 - 4*k1) * k5;
    a2 = (k2 + 4*(k1 - k3)) * k5;
    
    B = [b0 b1 b2];
    A = [1 a1 a2];

    G = ss(tf(B, A, Ts));

end

