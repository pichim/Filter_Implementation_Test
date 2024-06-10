function filter = iir_filter_reset(filter, output)

    filter.w(1) = output * (1.0 - filter.B(1));
    if (filter.order == 2)
        filter.w(2) = filter.w(1) + output * (filter.A(1) - filter.B(2));
    end

end