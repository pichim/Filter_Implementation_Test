function [f_peak, ...
    is_peak, ...
    ptn_ratio, ...
    X_peak, ...
    X_mean_rest] = find_peaks_robust(X, ind_min, ind_max, df, ptn_ratio_min, N_peak, min_peak_width, use_median_noise)

    % Enhanced peak detection with robustness improvements
    % Additional parameters:
    % min_peak_width: minimum width of peak (default 1, use 3-5 for noise rejection)
    % use_median_noise: use median instead of mean for noise floor (default 0)
    
    % Set defaults for new parameters
    if nargin < 7, min_peak_width = 1; end
    if nargin < 8, use_median_noise = 0; end
    
    % Input validation
    if ind_min < 2 || ind_max > length(X)-1
        error('Index range must allow access to neighbors: ind_min >= 2, ind_max <= length(X)-1');
    end
    if N_peak < 1
        error('N_peak must be at least 1');
    end
    if min_peak_width < 1
        min_peak_width = 1;
    end

    % Calculate consistent boundary limits with margin for peak width checking
    margin = max(1, ceil(min_peak_width/2));
    i_start = max(margin + 1, ind_min-1);
    i_end = min(length(X) - margin, ind_max);

    % default return values
    f_peak = zeros(1, N_peak);
    is_peak = zeros(1, N_peak);
    ptn_ratio = zeros(1, N_peak);
    X_peak = zeros(1, N_peak);
    X_mean_rest = 0.0;
    ind_peak = zeros(1, N_peak);
    
    % Step 1: Find potential peaks with enhanced criteria
    for i = i_start:i_end
        is_local_max = 1; % assume it's a peak
        
        % Check immediate neighbors (basic local maximum)
        if X(i) <= X(i-1) || X(i) <= X(i+1)
            is_local_max = 0;
        end
        
        % Enhanced peak detection: check wider neighborhood for minimum peak width
        if is_local_max && min_peak_width > 1
            half_width = ceil(min_peak_width / 2);
            
            % Check that peak is highest in its neighborhood
            for j = -half_width:half_width
                if j ~= 0 && (i + j >= 1) && (i + j <= length(X))
                    if X(i) <= X(i + j)
                        is_local_max = 0;
                        break;
                    end
                end
            end
            
            % Additional check: ensure peak has minimum "shoulder width"
            % Peak should be consistently higher than points at distance half_width
            if is_local_max
                left_check = i - half_width;
                right_check = i + half_width;
                if left_check >= 1 && right_check <= length(X)
                    if X(i) <= X(left_check) || X(i) <= X(right_check)
                        is_local_max = 0;
                    end
                end
            end
        end
        
        % Insert valid peaks into top-N array
        if is_local_max
            for j = 1:N_peak
                if X(i) > X_peak(j)
                    % Shift elements manually (C-friendly)
                    if j < N_peak
                        for k = N_peak:-1:j+1
                            X_peak(k) = X_peak(k-1);
                            ind_peak(k) = ind_peak(k-1);
                            is_peak(k) = is_peak(k-1);
                        end
                    end
    
                    % Insert new peak at position j
                    X_peak(j) = X(i);
                    ind_peak(j) = i;
                    is_peak(j) = 1;
                    break;
                end
            end
        end
    end
    
    % Step 2: Calculate robust noise floor
    % Collect all non-peak values for noise estimation
    noise_values = [];
    noise_count = 0;
    
    for i = i_start:i_end
        is_part_of_noise = 1;
        
        % Exclude peaks and their extended neighborhoods
        for j = 1:N_peak
            if ind_peak(j) > 0
                exclusion_radius = max(2, min_peak_width);
                if abs(i - ind_peak(j)) <= exclusion_radius
                    is_part_of_noise = 0;
                    break;
                end
            end
        end
        
        if is_part_of_noise
            noise_count = noise_count + 1;
            if use_median_noise
                % Store values for median calculation (simple array)
                if noise_count == 1
                    noise_values = X(i);
                else
                    % Simple insertion to maintain sorted order for median
                    noise_values = [noise_values, X(i)];
                end
            else
                % Running mean calculation
                X_mean_rest = X_mean_rest + X(i);
            end
        end
    end
    
    % Calculate final noise floor
    if noise_count > 0
        if use_median_noise
            % Simple sorting for median (C-friendly bubble sort for small arrays)
            n = length(noise_values);
            for i = 1:n-1
                for j = 1:n-i
                    if noise_values(j) > noise_values(j+1)
                        temp = noise_values(j);
                        noise_values(j) = noise_values(j+1);
                        noise_values(j+1) = temp;
                    end
                end
            end
            % Calculate median
            if mod(n, 2) == 1
                X_mean_rest = noise_values((n+1)/2);
            else
                X_mean_rest = (noise_values(n/2) + noise_values(n/2 + 1)) / 2;
            end
        else
            X_mean_rest = X_mean_rest / noise_count;
        end
    else
        X_mean_rest = 0.0;
    end

    % Step 3: Calculate peak-to-noise ratios
    for i = 1:N_peak
        if X_mean_rest > 0
            ptn_ratio(i) = X_peak(i) / X_mean_rest;
        else
            ptn_ratio(i) = 0.0;
        end
    end

    % Step 4: Final peak validation and frequency calculation
    for i = 1:N_peak
        if is_peak(i) && ptn_ratio(i) > ptn_ratio_min
            peak_idx = ind_peak(i);
            
            % Enhanced boundary checking for quadratic interpolation
            if peak_idx > 1 && peak_idx < length(X)
                % Quadratic interpolation with additional validation
                y0 = X(peak_idx - 1);
                y1 = X(peak_idx);
                y2 = X(peak_idx + 1);
                
                % Additional check: ensure parabola opens downward (valid peak)
                if y0 < y1 && y2 < y1
                    f_peak(i) = peak_idx - 1;  % Convert to 0-based indexing
                    
                    % Quadratic interpolation
                    denom = 2.0 * (y0 - 2.0 * y1 + y2);
                    if abs(denom) > 1e-12
                        offset = (y0 - y2) / denom;
                        % Clamp offset to reasonable range (avoid wild interpolation)
                        if abs(offset) <= 0.5
                            f_peak(i) = f_peak(i) + offset;
                        end
                    end
                    
                    % Convert to frequency with proper bounds checking
                    f_peak(i) = max(i_start - 1, min(i_end, f_peak(i))) * df;
                else
                    % Invalid parabola, use simple peak position
                    f_peak(i) = (peak_idx - 1) * df;
                end
            else
                % Boundary peak - no interpolation possible
                f_peak(i) = (peak_idx - 1) * df;
            end
        else
            % Peak doesn't meet criteria
            is_peak(i) = 0;
            f_peak(i) = 0.0;
            ptn_ratio(i) = 0.0;
        end
    end
end
