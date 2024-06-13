function G = get_phase_comp(fCenter, phaseLift, Ts)

    sn = sin(pi / 180.0 * phaseLift);
    k = sqrt((1.0 - sn) / (1.0 + sn));
    fZero = fCenter * k;
    fPole = fCenter / k;

    G = get_leadlag1(fZero, fPole, Ts);

end

