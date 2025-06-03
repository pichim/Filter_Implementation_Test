function [f_peak, ...
    is_peak, ...
    ptn_ratio, ...
    X_peak, ...
    X_mean_rest] = find_peaks(X, ind_min, ind_max, df, ptn_ratio_min, N_peak)

    % default return values
    f_peak = zeros(1, N_peak);
    is_peak = zeros(1, N_peak);
    ptn_ratio = zeros(1, N_peak);
    X_peak = zeros(1, N_peak);
    X_mean_rest = 0.0;
    ind_peak = zeros(1, N_peak);
    
    % find peak
    i = ind_min-1;
    while i <= ind_max
        % local maximum
        if (X(i) > X(i-1) && X(i) > X(i+1))
            % insert peak i into the top-N array if it's big enough
            for j = 1:N_peak
                if (X(i) > X_peak(j))
                    % X_peak is in descending order
                    for k = N_peak:-1:j+1
                        X_peak(k)   = X_peak(k-1);
                        ind_peak(k) = ind_peak(k-1);
                    end
    
                    % insert new peak at position j
                    X_peak(j)   = X(i);
                    ind_peak(j) = i;
                    is_peak(j)  = 1;

                    % can be skipped anyways
                    i = i + 1;

                    % break so we only insert once
                    break
                end
            end
        end
        i = i + 1;
    end
    
    % calculate noise floor
    cntr = 0;
    for i = ind_min-1:ind_max
        is_part_of_rest = true;
        for j = 1:N_peak % sum(is_peak)
            % exclude peaks and neighbors
            if abs(i - ind_peak(j)) <= 2
                is_part_of_rest = false;
                break
            end
        end
        if (is_part_of_rest)
            X_mean_rest = X_mean_rest + X(i);
            cntr = cntr + 1;
        end
    end
    if cntr > 0
        X_mean_rest = X_mean_rest / cntr;
    else
        X_mean_rest = 0.0;
    end

    % X_mean_rest = mean(X(ind_min-1:ind_max));

    % X_sorted = insertionSortWithIndices(X(ind_min-1:ind_max));
    % X_mean_rest = mean(X_sorted(1:end - 10));
   
    % calculate ptn_rario
    if X_mean_rest > 0
        ptn_ratio = X_peak / X_mean_rest;
    end

    % calculate peak
    for i = 1:N_peak
        if ((is_peak(i)) &&  (ptn_ratio(i) > ptn_ratio_min))
            % quadratic interpolation of peak
            f_peak(i) = (ind_peak(i) - 1);
            % height of peak bin (y1) and shoulder bins (y0, y2)
            y0 = X(ind_peak(i) - 1);
            y1 = X(ind_peak(i)    );
            y2 = X(ind_peak(i) + 1);
            % estimate true peak position aka. meanBin (fit parabola y(x) over y0, y1 and y2, solve dy/dx=0 for x)
            denom = 2.0 * (y0 - 2.0 * y1 + y2);
            if (denom ~= 0.0)
                f_peak(i) = f_peak(i) + (y0 - y2) / denom;
            end
            f_peak(i) = max([ind_min - 1,  f_peak(i)]) * df +  0 * 0.5 * df;
            % % clamp
            % if f_peak(i) < ind_min - 1
            %     f_peak(i) = ind_min - 1;
            % elseif f_peak(i) > ind_max
            %     f_peak(i) = ind_max;
            % end
            % f_peak(i) = f_peak(i) * df;
        else
            is_peak(i) = 0;
        end
    end
end