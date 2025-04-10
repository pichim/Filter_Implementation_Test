function [X_out, X_w_out, is_valid_out] = calc_sdft(x_new, N, epsilon)

    % currently using twiddle factor from (slignthly better, but does not matter nummerically)
    % - https://github.com/betaflight/betaflight/blob/master/src/main/common/sdft.c
    % alternative implementatin can be found here
    % - https://github.com/betaflight/betaflight/blob/master/src/main/common/sdft.c

    % X_fft(2) = X_fft(N)'
    % X_fft(3) = X_fft(N-1)'
    % ...
    % X_fft(N/2) = X_fft(N/2+2)

    persistent  r r_to_N x twiddle X X_w ind scale scale_ratio is_valid
    if isempty(x)
        r = 1.0 - epsilon;
        r_to_N = r^N;
        x = zeros(N, 1);
        twiddle = exp(1i*2*pi*(0:N-1).' / N);
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
    X(1) = twiddle(1) * (x(ind) - r_to_N * x_previous + r * X(1));
    ind_ = N/2 + 1;
    X(ind_) = twiddle(ind_) * (x(ind) - r_to_N * x_previous + r * X(ind_));
    for i = 2:N/2
        X(i) = twiddle(i) * (x(ind) - r_to_N * x_previous + r * X(i));
        X(N-i+2) = conj(X(i));
    end
    
    % hann
    k0 = 0.50; k1 = 0.25;
    % update windowed fft (hamming)
    X_w(1) = scale_ratio * (k0*X(1) - k1 * (X(N) + X(2)) );
    ind_ = N/2 + 1;
    X_w(ind_) = scale_ratio * (k0 * X(ind_) - k1 * (X(ind_-1) + X(ind_+1)) );
    for i = 2:N/2
        X_w(i) = scale_ratio * (k0 * X(i) - k1 * (X(i-1) + X(i+1)) );
        X_w(N-i+2) = conj(X_w(i));
    end

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