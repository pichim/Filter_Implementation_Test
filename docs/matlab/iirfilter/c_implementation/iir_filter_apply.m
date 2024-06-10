function [filter, output] = iir_filter_apply(filter, input)

    output = filter.B(1) * input + filter.w(1);
    filter = iir_filter_apply_filter_update(filter, input, output);

end