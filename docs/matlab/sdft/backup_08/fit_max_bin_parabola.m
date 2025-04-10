function f_max = fit_max_bin_parabola(X, N, ind_min, ind_max, df)

    X_eval_max = max( X(ind_min-1:ind_max) );
    ind_max_eval = find(X == X_eval_max);
    f_max = (ind_max_eval - 1);
    if (ind_max_eval ~= ind_min - 1 && ind_max_eval ~= ind_max)
        if (ind_max_eval > 2 && ind_max_eval < N/2 + 1) % dont worry about the last index, f_max < f_nyq !
            f0 = ind_max_eval - 1;
            f1 = ind_max_eval    ;
            f2 = ind_max_eval + 1;
            X0 = X(ind_max_eval - 1);
            X1 = X(ind_max_eval    );
            X2 = X(ind_max_eval + 1);
            den1 = f0 * (X1 - X2);
            den2 = f1 * (X2 - X0);
            den3 = f2 * (X0 - X1);
            f_max = 0.5 * (f0*den1 + f1*den2 + f2*den3) / (den1 + den2 + den3) - 0.5;
        end
    end
    f_max = max([ind_min - 1,  f_max]) * df;

end