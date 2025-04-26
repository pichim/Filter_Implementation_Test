function val_f = nl_lowpass(val, val_f_past, knl1, knl2, Ts)
    
    % % linear pt1
    % e = val - val_f_past;
    % inp = knl1 * e;
    % val_f  = inp * Ts + val_f_past;
    % non-linear pt1
    e = val - val_f_past;
    inp = knl1 * e + knl2 * ( abs(e) .* e ); % large error -> faster
    val_f  = inp * Ts + val_f_past;

end

