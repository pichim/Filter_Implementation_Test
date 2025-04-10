function [X_out, X_w_out, is_valid_out] = calc_sdft(x_new, N, epsilon)

    do_use_bronsonp_twiddle = true; % true is slignthly better, but does not matter nummerically

    persistent  r r_to_N x twiddle X X_w ind scale scale_ratio is_valid
    if isempty(x)
        r = 1.0 - epsilon;
        r_to_N = r^N;
        x = zeros(N, 1);
        if (do_use_bronsonp_twiddle)
            % https://github.com/bronsonp/SlidingDFT/blob/master/sliding_dft.hpp
            twiddle = exp(1i*2*pi*(0:N-1).' / N);
        else
            % https://github.com/betaflight/betaflight/blob/master/src/main/common/sdft.c
            twiddle = r * exp(1i*2*pi*(0:N-1).' / N);
        end
        X = zeros(N, 1);
        X_w = zeros(N, 1);
        ind = 1;
        scale = 1 / N;
        scale_ratio = 2.0; % N / sum(hann(N)) * (N - 1) / N;
        is_valid = false;
        display('--- init ---');
    end

    % udpate signal
    x_previous = x(ind);
    x(ind) = scale * x_new;

    % update fft
    for i = 1:N
        if (do_use_bronsonp_twiddle)
            X(i) = twiddle(i) * (x(ind) - r_to_N * x_previous + r * X(i));
        else
            X(i) = twiddle(i) * (x(ind) - r_to_N * x_previous + X(i));
        end
    end
    
    % hann
    k0 = 0.50; k1 = 0.25;
    % update windowed fft (hamming)
    X_w(1) = scale_ratio * (k0*X(1) - k1 * (X(N) + X(2)) );
    for i = 2:N-1
        X_w(i) = scale_ratio * (k0 * X(i) - k1 * (X(i-1) + X(i+1)) );
    end
    X_w(N) = scale_ratio * (k0 * X(N) - k1 * (X(N-1) + X(1)) );

    % increment index
    ind = ind + 1;
    if ind > N
        ind = 1;
        if (~is_valid)
            is_valid = true;
        end
    end

    X_out = X;
    X_w_out = X_w;
    is_valid_out = is_valid;

end