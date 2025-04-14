function [f_peak, is_peak, ptn_ratio, X_peak, X_mean_rest, ind_peak] = ...
    fit_max_freq_parabola(X, N, ind_min, ind_max, df)

    % find maxima within allowed region
    X_peak = X(ind_min-1);
    X_peak_lower = 0.0;
    X_peak_upper = X(ind_min);
    X_mean_rest = X(ind_min-1);
    ind_peak = ind_min-1;
    for i = ind_min:ind_max
        if (X(i) > X_peak)
            ind_peak = i;
            X_peak = X(ind_peak);
            X_peak_lower = X(ind_peak - 1);
            if ind_peak == ind_max
                X_peak_upper = 0.0;
            else
                X_peak_upper = X(ind_peak + 1);
            end
        end
        X_mean_rest = X_mean_rest + X(i);
    end

    % correct with peak and neighbors
    X_mean_rest = X_mean_rest - (X_peak_lower + X_peak + X_peak_upper);

    % calculate the average
    if (ind_peak == ind_min-1 || ind_peak == ind_max)
        X_mean_rest = X_mean_rest / (ind_max - ind_min);
    else
        X_mean_rest = X_mean_rest / (ind_max - ind_min - 1);
    end

    % X_sorted = insertionSortWithIndices(X(ind_min-1:ind_max));
    % X_mean_rest = mean(X_sorted(1:end - 4));
    
    % decide if peak is big enough relative to noise and therefor should be
    % tracked
    is_peak = true;
    ptn_ratio = X_peak / X_mean_rest;
    if ptn_ratio < 10
        is_peak = false;
        f_peak = 0.0; % will not be processed further
        return
    end

    % quadratic interpolation of peak
    f_peak = (ind_peak - 1);
    if (ind_peak ~= ind_min - 1 && ind_peak ~= ind_max)
        if (ind_peak > 2 && ind_peak < N/2 + 1) % dont worry about the last index, f_max < f_nyq !
            % % height of peak bin (y1) and shoulder bins (y0, y2)
            % y0 = X(ind_peak - 1);
            % y1 = X(ind_peak    );
            % y2 = X(ind_peak + 1);
            % % estimate true peak position aka. meanBin (fit parabola y(x) over y0, y1 and y2, solve dy/dx=0 for x)
            % denom = 2.0 * (y0 - 2.0 * y1 + y2);
            % if (denom ~= 0.0)
            %     f_peak = f_peak + (y0 - y2) / denom;
            % end
            x0 = (ind_peak - 1 - 1);
            x1 = (ind_peak     - 1);
            x2 = (ind_peak + 1 - 1);
            y0 = X(ind_peak - 1);
            y1 = X(ind_peak    );
            y2 = X(ind_peak + 1);
            a_est = -(x0*y1 - x1*y0 - x0*y2 + x2*y0 + x1*y2 - x2*y1)/((x0 - x1)*(x0 - x2)*(x1 - x2));
            b_est = (x0^2*y1 - x1^2*y0 - x0^2*y2 + x2^2*y0 + x1^2*y2 - x2^2*y1)/((x0 - x1)*(x0 - x2)*(x1 - x2));
            c_est = -(- y2*x0^2*x1 + y1*x0^2*x2 + y2*x0*x1^2 - y1*x0*x2^2 - y0*x1^2*x2 + y0*x1*x2^2)/((x0 - x1)*(x0 - x2)*(x1 - x2));         
            den1 = x0 * (y1 - y2);
            den2 = x1 * (y2 - y0);
            den3 = x2 * (y0 - y1);
            f_peak = 0.5 * (x0*den1 + x1*den2 + x2*den3) / (den1 + den2 + den3);
            X_peak = a_est * f_peak^2 + b_est * f_peak + c_est;
        end
    end
    f_peak = max([ind_min - 1,  f_peak]) * df;

end