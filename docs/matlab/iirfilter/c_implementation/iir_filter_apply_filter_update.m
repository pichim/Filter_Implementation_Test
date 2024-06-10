function filter = iir_filter_apply_filter_update(filter, input, output)

    % https://dsp.stackexchange.com/questions/72575/transposed-direct-form-ii
    for i = 1:filter.order - 1
        filter.w(i) = filter.B(i + 1) * input + filter.w(i + 1) - filter.A(i) * output;
    end
    filter.w(filter.order) = filter.B(filter.order + 1) * input - filter.A(filter.order) * output;

end

