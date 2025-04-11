function filter = lowpass1_init(filter, fcut, Ts)

    filter.order = 1;
    filter = lowpass1_update(filter, fcut, Ts);
    filter = iir_filter_reset(filter, 0.0);

end
