function G = get_leadlag1(fZero, fPole, Ts)

    alpha = fZero / fPole;
    fCenter = fPole * sqrt(alpha);
    phaseLift = asin( (1.0 - alpha) / (1.0 + alpha) ) * (180.0 / pi);

    G = get_phase_comp(fCenter, phaseLift, Ts);

end

