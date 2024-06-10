function fadingNotch = fading_notch_init(fadingNotch, fcut, D, fFadeMin, fFadeMax, Ts)

    fadingNotch.D = D;
    fadingNotch.fFadeMin = fFadeMin;
    fadingNotch.fFadeMax = fFadeMax;
    fadingNotch.Ts = Ts;
    fadingNotch.filter = notch_init(fadingNotch.filter, fcut, D, Ts);

end

