function f_max_eval = fit_max_freq_parabola(X_eval, freq, N, f_min, f_max, df)

    X_eval_max = max( X_eval(f_min <= freq & freq <= f_max) );
    f_max_eval = freq( X_eval == X_eval_max);
    if (f_max_eval ~= f_min && f_max_eval ~= f_max)
        bin_index = round( f_max_eval / df ) + 1;
        if (bin_index > 2 && bin_index < N/2 + 1) % dont worry about the last index, f_max < f_nyq !
            x0 = freq(bin_index - 1);
            x1 = freq(bin_index    );
            x2 = freq(bin_index + 1);
            y0 = X_eval(bin_index - 1);
            y1 = X_eval(bin_index    );
            y2 = X_eval(bin_index + 1);
            den1 = x0 * (y1 - y2);
            den2 = x1 * (y2 - y0);
            den3 = x2 * (y0 - y1);
            % TODO: Check why if adding df/2 is actually correct also for other signals
            f_max_eval = 0.5 * (x0*den1 + x1*den2 + x2*den3) / (den1 + den2 + den3) + df/2;
        end
    end

end

