function [fadingNotch, output] = fading_notch_filter_apply(fadingNotch, fcut, input)

    fadingNotch.filter = notch_update(fadingNotch.filter, fcut, fadingNotch.D, fadingNotch.Ts);

    [fadingNotch.filter, output] = iir_filter_apply(fadingNotch.filter, input);
    [fadingNotch, output] = fading_notch_filter_apply_fading(fadingNotch, fcut, input, output);

end