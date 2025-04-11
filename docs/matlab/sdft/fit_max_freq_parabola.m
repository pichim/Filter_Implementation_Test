function [f_peak, is_peak, peak_to_noise_ratio, X_peak, X_not_peak_mean] = ...
    fit_max_freq_parabola(X, N, ind_min, ind_max, df)

    % find maxima within allowed region
    X_peak = 0.0;
    ind_peak = 1;
    for i = ind_min-1:ind_max
        if (X(i) > X_peak)
            X_peak = X(i);
            ind_peak = i;
        end
    end

    % average X exept for peak and peak neighbor
    X_not_peak_mean = 0.0;
    cntr = 0;
    % peak is at the lower end
    if (ind_peak == ind_min-1)
        for i = ind_min:ind_max
            X_not_peak_mean = X_not_peak_mean + X(i);
        end
        cntr = ind_max - ind_min + 1;
    % peak is at the upper end
    elseif (ind_peak == ind_max)
        for i = ind_min-1:ind_max-1
            X_not_peak_mean = X_not_peak_mean + X(i);
        end
        cntr = ind_max - ind_min + 1;
    % peak is in between
    else
        for i = ind_min-1:ind_max
            if (i ~= ind_peak - 1 && i ~= ind_peak && i ~= ind_peak + 1)
                X_not_peak_mean = X_not_peak_mean + X(i);
            end
        end
        cntr = ind_max - ind_min - 1;
    end
    X_not_peak_mean = X_not_peak_mean / cntr;
    
    % decide if peak is big enough relative to noise and therefor should be
    % tracked
    is_peak = true;
    peak_to_noise_ratio = X_peak / X_not_peak_mean;
    if peak_to_noise_ratio < 6.0 
        is_peak = false;
        f_peak = 0.0; % will not be processed further
        return
    end

    % quadratic interpolation of peak
    f_peak = (ind_peak - 1);
    if (ind_peak ~= ind_min - 1 && ind_peak ~= ind_max)
        if (ind_peak > 2 && ind_peak < N/2 + 1) % dont worry about the last index, f_max < f_nyq !
            % height of peak bin (y1) and shoulder bins (y0, y2)
            y0 = X(ind_peak - 1);
            y1 = X(ind_peak    );
            y2 = X(ind_peak + 1);
            % estimate true peak position aka. meanBin (fit parabola y(x) over y0, y1 and y2, solve dy/dx=0 for x)
            denom = 2.0 * (y0 - 2.0 * y1 + y2);
            if (denom ~= 0.0)
                f_peak = f_peak + (y0 - y2) / denom;
            end
            % same as above
            % f0 = ind_peak - 1 - 1;
            % f1 = ind_peak     - 1;
            % f2 = ind_peak + 1 - 1;
            % X0 = X(ind_peak - 1);
            % X1 = X(ind_peak    );
            % X2 = X(ind_peak + 1);
            % den1 = f0 * (X1 - X2);
            % den2 = f1 * (X2 - X0);
            % den3 = f2 * (X0 - X1);
            % f_peak_ = 0.5 * (f0*den1 + f1*den2 + f2*den3) / (den1 + den2 + den3);
        end
    end

    f_peak = max([ind_min - 1,  f_peak]) * df;

end