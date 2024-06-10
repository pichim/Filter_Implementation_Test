function [fadingNotch, output] = fading_notch_filter_apply_fading(fadingNotch, fcut, input, output)

    if (fcut < fadingNotch.fFadeMin)
        output = input;
        return
    elseif (fcut > fadingNotch.fFadeMax)
        return
    else
        w = (fcut - fadingNotch.fFadeMin) / (fadingNotch.fFadeMax - fadingNotch.fFadeMin);
        output = (1.0 - w) * input + w * output;
        return
    end

end

