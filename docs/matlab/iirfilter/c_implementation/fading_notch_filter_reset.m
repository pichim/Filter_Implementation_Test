function fadingNotch = fading_notch_filter_reset(fadingNotch, fcut, output)

    fadingNotch.filter = notch_update(fadingNotch.filter, fcut, fadingNotch.D, fadingNotch.Ts);
    fadingNotch.filter = iirFilterReset(fadingNotch.filter, output);

end