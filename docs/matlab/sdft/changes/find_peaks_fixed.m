function [f_peak, ...
    is_peak, ...
    ptn_ratio, ...
    X_peak, ...
    X_mean_rest] = find_peaks_fixed(X, ind_min, ind_max, df, ptn_ratio_min, N_peak)

    % Input validation
    if ind_min < 2 || ind_max > length(X)-1
        error('Index range must allow access to neighbors: ind_min >= 2, ind_max <= length(X)-1');
    end
    if N_peak < 1
        error('N_peak must be at least 1');
    end

    % Calculate consistent boundary limits
    i_start = max(2, ind_min-1);
    i_end = min(length(X)-1, ind_max);

    % default return values
    f_peak = zeros(1, N_peak);
    is_peak = zeros(1, N_peak);
    ptn_ratio = zeros(1, N_peak);
    X_peak = zeros(1, N_peak);
    X_mean_rest = 0.0;
    ind_peak = zeros(1, N_peak);
    
    % find peaks with boundary checks
    for i = i_start:i_end
        % local maximum (boundary checks already ensured above)
        if (X(i) > X(i-1) && X(i) > X(i+1))
            % insert peak i into the top-N array if it's big enough
            for j = 1:N_peak
                if (X(i) > X_peak(j))
                    % X_peak is in descending order - shift elements manually
                    if j < N_peak
                        for k = N_peak:-1:j+1
                            X_peak(k) = X_peak(k-1);
                            ind_peak(k) = ind_peak(k-1);
                            is_peak(k) = is_peak(k-1);
                        end
                    end
    
                    % insert new peak at position j
                    X_peak(j) = X(i);
                    ind_peak(j) = i;
                    is_peak(j) = 1;

                    % break so we only insert once
                    break;
                end
            end
        end
    end
    
    % calculate noise floor (use same range as peak finding)
    cntr = 0;
    for i = i_start:i_end
        is_part_of_rest = 1; % true
        for j = 1:N_peak
            % only check peaks that actually exist
            if ind_peak(j) > 0
                % exclude peaks and neighbors
                if abs(i - ind_peak(j)) <= 2
                    is_part_of_rest = 0; % false
                    break;
                end
            end
        end
        if is_part_of_rest
            X_mean_rest = X_mean_rest + X(i);
            cntr = cntr + 1;
        end
    end
    if cntr > 0
        X_mean_rest = X_mean_rest / cntr;
    else
        X_mean_rest = 0.0;  % or could use a small epsilon to avoid division issues
    end

    % calculate ptn_ratio (element-wise division)
    for i = 1:N_peak
        if X_mean_rest > 0
            ptn_ratio(i) = X_peak(i) / X_mean_rest;
        else
            ptn_ratio(i) = 0.0;
        end
    end

    % calculate final peak frequencies with quadratic interpolation
    for i = 1:N_peak
        if (is_peak(i) && ptn_ratio(i) > ptn_ratio_min)
            % Ensure we can safely access neighbors for interpolation
            peak_idx = ind_peak(i);
            if peak_idx > 1 && peak_idx < length(X)
                % quadratic interpolation of peak
                f_peak(i) = peak_idx - 1;  % Convert to 0-based indexing
                
                % height of peak bin (y1) and shoulder bins (y0, y2)
                y0 = X(peak_idx - 1);
                y1 = X(peak_idx);
                y2 = X(peak_idx + 1);
                
                % estimate true peak position (fit parabola y(x) over y0, y1, y2, solve dy/dx=0 for x)
                denom = 2.0 * (y0 - 2.0 * y1 + y2);
                if abs(denom) > 1e-12  % Use small epsilon instead of exact zero check
                    f_peak(i) = f_peak(i) + (y0 - y2) / denom;
                end
                
                % Clamp to valid range and convert to frequency
                f_peak(i) = max(i_start - 1, min(i_end, f_peak(i))) * df;
            else
                % Fallback for boundary peaks
                f_peak(i) = (peak_idx - 1) * df;
            end
        else
            is_peak(i) = 0;
            f_peak(i) = 0.0;  % Ensure consistent output
        end
    end
end
