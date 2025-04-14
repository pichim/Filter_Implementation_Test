% function [f_peak_1, f_peak_2, ...
%           is_peak_1, is_peak_2, ...
%           ptn_ratio_1, ptn_ratio_2, ...
%           X_peak_1, X_peak_2, X_mean_rest] = ...
%             fit_max_freq_parabola_two_peaks(X, N, ind_min, ind_max, df)
% 
%     [f_peak_1, is_peak_1, ptn_ratio_1, X_peak_1, X_mean_rest_1, ind_peak_1] = ...
%         fit_max_freq_parabola(X, N, ind_min, ind_max, df);
% 
%     % If the first peak wasn't valid, skip second
%     if ~is_peak_1
%         % Just fill in second-peak outputs with defaults
%         f_peak_2    = 0.0;
%         is_peak_2   = false;
%         ptn_ratio_2 = 0.0;
%         X_peak_2    = 0.0;
%         X_mean_rest = X_mean_rest_1;  % The single-pass "rest" average
%         return;
%     end
% 
%     %-----------------------------
%     % 2) Exclude the first peak + neighbors
%     %-----------------------------
%     % We'll make a local copy "X2" of X, so we don't permanently modify the original.
%     X2 = X;
% 
%     % Mark the peak index ind_peak_1 as 0
%     X2(ind_peak_1) = 0;
% 
%     % Mark left neighbor if it exists
%     if (ind_peak_1 - 1) >= (ind_min - 1)
%         X2(ind_peak_1 - 1) = 0;
%     end
% 
%     % Mark right neighbor if it exists
%     if (ind_peak_1 + 1) <= ind_max
%         X2(ind_peak_1 + 1) = 0;
%     end
% 
%     %-----------------------------
%     % 3) Second pass: find the second peak from X2
%     %-----------------------------
%     [f_peak_2, is_peak_2, ptn_ratio_2, X_peak_2, X_mean_rest_2] = ...
%         fit_max_freq_parabola(X2, N, ind_min, ind_max, df);
% 
%     %-----------------------------
%     % 4) Decide final X_mean_rest
%     %-----------------------------
%     % For consistency, let's just use the second pass's mean-of-the-rest, which
%     % excludes the second peak + neighbors. If you prefer a single average
%     % that excludes *both* peaks + neighbors, you'd do another summation yourself.
%     % But we'll keep it simple:
%     X_mean_rest = X_mean_rest_2;
% end

function [f_peak_1, f_peak_2, ...
          is_peak_1, is_peak_2, ...
          ptn_ratio_1, ptn_ratio_2, ...
          X_peak_1, X_peak_2, X_mean_rest] = ...
            fit_max_freq_parabola_two_peaks(X, N, ind_min, ind_max, df)

    % identify the two peaks in [ind_min-1 .. ind_max]
    ind_first = ind_min - 1;  % start of search
    ind_last  = ind_max;

    % If range is invalid, just return defaults
    if ind_first > ind_last
        f_peak_1 = 0; is_peak_1 = false; ptn_ratio_1 = 0; X_peak_1 = 0;
        f_peak_2 = 0; is_peak_2 = false; ptn_ratio_2 = 0; X_peak_2 = 0;
        X_mean_rest = 0;
        return;
    end

    % find first (highest) peak
    X_peak_1   = -1.0;
    ind_peak_1 = ind_first;
    for i = ind_first:ind_last
        if X(i) > X_peak_1
            X_peak_1   = X(i);
            ind_peak_1 = i;
        end
    end

    % find second (highest) peak (must not be a neighbor of the first)
    X_peak_2   = -1.0;
    ind_peak_2 = -1;
    for i = ind_first:ind_last
        if abs(i - ind_peak_1) >= 2
            if X(i) > X_peak_2
                X_peak_2   = X(i);
                ind_peak_2 = i;
            end
        end
    end

    % compute the mean of the rest (excluding peaks & neighbors)
    X_mean_rest = 0.0;
    count = 0;
    for i = ind_first:ind_last
        % if i is the same or neighbor of peak1
        if abs(i - ind_peak_1) < 2 % 2
            continue; 
        end
        % if i is the same or neighbor of peak2
        if abs(i - ind_peak_2) < 2 % 2
            continue;
        end
        X_mean_rest = X_mean_rest + X(i);
        count = count + 1;
    end

    if count > 0
        X_mean_rest = X_mean_rest / count;
    else
        X_mean_rest = 0.0;
    end

    [X_sorted, ind_sorted] = insertionSortWithIndices(X(ind_min-1:ind_max));
    X_mean_rest = mean(X_sorted(1:end - 7));
    % X_peak_1 = X_sorted(end);
    % ind_peak_1 = find(X_peak_1 == X);
    % X_peak_2 = X_sorted(end-1);
    % ind_peak_2 = find(X_peak_2 == X);

    % evaluate each peak: ratio check + optional parabola

    % evaluate peak 1
    ptn_ratio_1 = 0.0;
    f_peak_1    = 0.0;
    is_peak_1   = false;

    % if ind_peak_1 >= ind_first && ind_peak_1 <= ind_last && (ind_peak_1 >= 1)
        % peak-to-noise
        if X_mean_rest > 0
            ptn_ratio_1 = (X_peak_1 / X_mean_rest);
        end
        % check threshold
        if ptn_ratio_1 >= 8
            is_peak_1 = true;
            % do parabolic interpolation if not at boundary
            f_peak_1 = (ind_peak_1 - 1);
            if (ind_peak_1 ~= ind_first) && (ind_peak_1 ~= ind_last)
                if (ind_peak_1 > 2) && (ind_peak_1 < (N/2 + 1))
                    y0 = X(ind_peak_1 - 1);
                    y1 = X(ind_peak_1);
                    y2 = X(ind_peak_1 + 1);
                    denom = 2.0*(y0 - 2.0*y1 + y2);
                    if denom ~= 0.0
                        f_peak_1 = f_peak_1 + (y0 - y2)/denom;
                    end
                    x0 = (ind_peak_1 - 1 - 1);
                    x1 = (ind_peak_1     - 1);
                    x2 = (ind_peak_1 + 1 - 1);
                    y0 = X(ind_peak_1 - 1);
                    y1 = X(ind_peak_1    );
                    y2 = X(ind_peak_1 + 1);
                    a_est = -(x0*y1 - x1*y0 - x0*y2 + x2*y0 + x1*y2 - x2*y1)/((x0 - x1)*(x0 - x2)*(x1 - x2));
                    b_est = (x0^2*y1 - x1^2*y0 - x0^2*y2 + x2^2*y0 + x1^2*y2 - x2^2*y1)/((x0 - x1)*(x0 - x2)*(x1 - x2));
                    c_est = -(- y2*x0^2*x1 + y1*x0^2*x2 + y2*x0*x1^2 - y1*x0*x2^2 - y0*x1^2*x2 + y0*x1*x2^2)/((x0 - x1)*(x0 - x2)*(x1 - x2));         
                    den1 = x0 * (y1 - y2);
                    den2 = x1 * (y2 - y0);
                    den3 = x2 * (y0 - y1);
                    f_peak_1 = 0.5 * (x0*den1 + x1*den2 + x2*den3) / (den1 + den2 + den3);
                    X_peak_1 = a_est * f_peak_1^2 + b_est * f_peak_1 + c_est;
                end
            end
            % clamp freq >= (ind_min - 1)*df
            f_peak_1 = max([ind_min - 1, f_peak_1]) * df;
        end
    % end

    % evaluate peak 2
    ptn_ratio_2 = 0.0;
    f_peak_2    = 0.0;
    is_peak_2   = false;

    % if ind_peak_2 >= ind_first && ind_peak_2 <= ind_last && (ind_peak_2 >= 1)
        if X_mean_rest > 0
            ptn_ratio_2 = (X_peak_2 / X_mean_rest);
        end
        if ptn_ratio_2 >= 8
            is_peak_2 = true;
            f_peak_2 = (ind_peak_2 - 1);
            if (ind_peak_2 ~= ind_first) && (ind_peak_2 ~= ind_last)
                if (ind_peak_2 > 2) && (ind_peak_2 < (N/2 + 1))
                    y0 = X(ind_peak_2 - 1);
                    y1 = X(ind_peak_2);
                    y2 = X(ind_peak_2 + 1);
                    denom = 2.0*(y0 - 2.0*y1 + y2);
                    if denom ~= 0.0
                        f_peak_2 = f_peak_2 + (y0 - y2)/denom;
                    end
                    % x0 = (ind_peak_2 - 1 - 1);
                    % x1 = (ind_peak_2     - 1);
                    % x2 = (ind_peak_2 + 1 - 1);
                    % y0 = X(ind_peak_2 - 1);
                    % y1 = X(ind_peak_2    );
                    % y2 = X(ind_peak_2 + 1);
                    % a_est = -(x0*y1 - x1*y0 - x0*y2 + x2*y0 + x1*y2 - x2*y1)/((x0 - x1)*(x0 - x2)*(x1 - x2));
                    % b_est = (x0^2*y1 - x1^2*y0 - x0^2*y2 + x2^2*y0 + x1^2*y2 - x2^2*y1)/((x0 - x1)*(x0 - x2)*(x1 - x2));
                    % c_est = -(- y2*x0^2*x1 + y1*x0^2*x2 + y2*x0*x1^2 - y1*x0*x2^2 - y0*x1^2*x2 + y0*x1*x2^2)/((x0 - x1)*(x0 - x2)*(x1 - x2));         
                    % den1 = x0 * (y1 - y2);
                    % den2 = x1 * (y2 - y0);
                    % den3 = x2 * (y0 - y1);
                    % f_peak_2 = 0.5 * (x0*den1 + x1*den2 + x2*den3) / (den1 + den2 + den3);
                    % X_peak_2 = a_est * f_peak_2^2 + b_est * f_peak_2 + c_est;
                end
            end
            f_peak_2 = max([ind_min - 1, f_peak_2]) * df;
        end
    % end

end


% function [f_peak_1, f_peak_2, ...
%           is_peak_1, is_peak_2, ...
%           ptn_ratio_1, ptn_ratio_2, ...
%           X_peak_1, X_peak_2, X_mean_rest] = ...
%             fit_max_freq_parabola_two_peaks(X, N, ind_min, ind_max, df)
% 
%     % ind two peaks and mean of the rest
%     [X_peak_1, ind_peak1, X_peak_2, ind_peak2, X_mean_rest] = ...
%         find_two_nonneighbor_peaks_and_mean_of_rest(X, ind_min, ind_max);
% 
%     % threshold check & parabolic interpolation
%     [f_peak_1, is_peak_1, ptn_ratio_1] = ...
%         process_peak(ind_peak1, X_peak_1, X_mean_rest, ...
%                     X, N, ind_min, ind_max, df);
% 
%     [f_peak_2, is_peak_2, ptn_ratio_2] = ...
%         process_peak(ind_peak2, X_peak_2, X_mean_rest, ...
%                     X, N, ind_min, ind_max, df);
% end
% 
% function [X_peak_1, ind_peak_1, X_peak_2, ind_peak_2, X_mean_rest] = ...
%     find_two_nonneighbor_peaks_and_mean_of_rest(X, ind_min, ind_max)
% 
%     % first (highest) peak
%     X_peak_1   = X(ind_min - 1);
%     ind_peak_1 = ind_min - 1;
%     for i = ind_min:ind_max
%         if X(i) > X_peak_1
%             X_peak_1   = X(i);
%             ind_peak_1 = i;
%         end
%     end
% 
%     % second (highest) peak
%     X_peak_2   = -inf;
%     ind_peak_2 = -1;
%     for i = ind_min-1:ind_max
%         if abs(i - ind_peak_1) >= 2
%             if X(i) > X_peak_2
%                 X_peak_2   = X(i);
%                 ind_peak_2 = i;
%             end
%         end
%     end
% 
%     % mean of the rest, exclude the two peaks and their neighbors
%     X_mean_rest = 0.0;
%     cntr = 0;
%     for i = ind_min-1:ind_max
%         if ~(check_is_excluded(i, ind_peak_1) || check_is_excluded(i, ind_peak_2))
%             X_mean_rest  = X_mean_rest + X(i);
%             cntr = cntr + 1;
%         end
%     end
% 
%     if cntr > 0
%         X_mean_rest = X_mean_rest / cntr;
%     else
%         X_mean_rest = 0.0;
%     end
% end
% 
% function is_excluded = check_is_excluded(i, ind_peak)
% 
%     % this can only happen if no second peak was found
%     if ind_peak < -1 
%         is_excluded = false;
%         return
%     end
% 
%     % it is a neighbor
%     if abs(i - ind_peak) < 2
%         is_excluded = true;
%         return
%     end
% 
%     is_excluded = false;
% end
% 
% function [f_peak, is_peak, ptn_ratio] = ...
%     process_peak(ind_peak, X_peak, X_mean_rest, X, N, ind_min, ind_max, df)
% % - if ind_peak < ind_min-1 or ind_peak > ind_max, skip
% % - if ratio < 8, skip
% % - otherwise do parabolic interpolation in X around [ind_peak-1..ind_peak+1]
% % - finally, clamp freq >= (ind_min - 1)*df
% 
%     % default valus
%     f_peak  = 0.0;
%     is_peak = true;
% 
%     % check peak-to-noise ratio
%     ptn_ratio = X_peak / X_mean_rest;
%     if ptn_ratio < 8.0
%         is_peak = false;
%         return
%     end
% 
%     % quadratic interpolation of peak
%     f_peak = (ind_peak - 1);
%     if (ind_peak ~= ind_min - 1 && ind_peak ~= ind_max)
%         if (ind_peak > 2 && ind_peak < N/2 + 1) % dont worry about the last index, f_max < f_nyq !
%             % height of peak bin (y1) and shoulder bins (y0, y2)
%             y0 = X(ind_peak - 1);
%             y1 = X(ind_peak    );
%             y2 = X(ind_peak + 1);
%             % estimate true peak position aka. meanBin (fit parabola y(x) over y0, y1 and y2, solve dy/dx=0 for x)
%             denom = 2.0 * (y0 - 2.0 * y1 + y2);
%             if (denom ~= 0.0)
%                 f_peak = f_peak + (y0 - y2) / denom;
%             end
%             % same as above
%             % f0 = ind_peak - 1 - 1;
%             % f1 = ind_peak     - 1;
%             % f2 = ind_peak + 1 - 1;
%             % X0 = X(ind_peak - 1);
%             % X1 = X(ind_peak    );
%             % X2 = X(ind_peak + 1);
%             % den1 = f0 * (X1 - X2);
%             % den2 = f1 * (X2 - X0);
%             % den3 = f2 * (X0 - X1);
%             % f_peak_ = 0.5 * (f0*den1 + f1*den2 + f2*den3) / (den1 + den2 + den3);
%         end
%     end
% 
%     % enforce freq >= (ind_min - 1)*df
%     f_peak = max([ind_min - 1, f_peak]) * df;
% end
