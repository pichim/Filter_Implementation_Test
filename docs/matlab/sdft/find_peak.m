function [f_peak, ...
    is_peak, ...
    ptn_ratio, ...
    X_peak, ...
    X_mean_rest] = find_peak(X, ind_min, ind_max, df, ptn_ratio_min)

    % default return values
    f_peak = 0.0;
    is_peak = 0;
    ptn_ratio = 0.0;
    X_peak = 0.0;
    X_mean_rest = 0.0;
    ind_peak = 0;
    
    % find peak
    for i = ind_min-1:ind_max
        % local maximum
        if (X(i) > X(i-1) && X(i) > X(i+1))
            if (X(i) > X_peak)
                ind_peak = i;
                X_peak = X(i);
                is_peak = 1;
            end
        end
    end
    
    % calculate noise floor
    cntr = 0;
    for i = ind_min-1:ind_max
        if abs(i - ind_peak) > 2
            X_mean_rest = X_mean_rest + X(i);
            cntr = cntr + 1;
        end
    end
    if cntr > 0
        X_mean_rest = X_mean_rest / cntr;
    else
        X_mean_rest = 0.0;
    end

    % X_sorted = insertionSortWithIndices(X(ind_min-1:ind_max));
    % X_mean_rest = mean(X_sorted(1:end - 4));
   
    % calculate ptn_rario
    if X_mean_rest > 0
        ptn_ratio = X_peak / X_mean_rest;
    end

    % calculate peak
    if (is_peak) &&  ptn_ratio > ptn_ratio_min
        % quadratic interpolation of peak
        f_peak = (ind_peak - 1);
        % height of peak bin (y1) and shoulder bins (y0, y2)
        y0 = X(ind_peak - 1);
        y1 = X(ind_peak    );
        y2 = X(ind_peak + 1);
        % estimate true peak position aka. meanBin (fit parabola y(x) over y0, y1 and y2, solve dy/dx=0 for x)
        denom = 2.0 * (y0 - 2.0 * y1 + y2);
        if (denom ~= 0.0)
            f_peak = f_peak + (y0 - y2) / denom;
        end
        f_peak = max([ind_min - 1,  f_peak]) * df;
    else
        is_peak = 0;
    end
end