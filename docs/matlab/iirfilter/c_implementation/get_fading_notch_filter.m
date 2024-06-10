function fading_notch_filter = get_fading_notch_filter()

    fading_notch_filter.D = [];
    fading_notch_filter.Ts = [];
    fading_notch_filter.fFadeMin = [];
    fading_notch_filter.fFadeMax = [];
    fading_notch_filter.filter = get_iir_filter;
    
end

