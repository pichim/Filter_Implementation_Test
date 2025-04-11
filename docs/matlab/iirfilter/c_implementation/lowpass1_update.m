function filter = lowpass1_update(filter, fcut, Ts)

    filter.A(2) = 0.0;
    filter.B(1) = 1.0 - exp(-Ts * 2.0 * pi * fcut);
    filter.B(2) = 0.0;
    filter.B(3) = 0.0;
    filter.A(1) = filter.B(1) - 1.0;

end
