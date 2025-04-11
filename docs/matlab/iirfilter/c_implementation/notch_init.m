function filter = notch_init(filter, fcut, D, Ts)

    filter.order = 2;
    filter = notch_update(filter, fcut, D, Ts);
    filter = iir_filter_reset(filter, 0.0);

end
