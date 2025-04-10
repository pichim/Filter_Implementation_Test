function [X_out, X_w_out] = calc_sdft(x_new, N, epsilon)

    persistent  r r_to_N x twiddle X X_w ind scale scale_ratio
    if isempty(x)
        r = 1.0 - epsilon;
        r_to_N = r^N;
        x = zeros(N, 1);
        % https://github.com/bronsonp/SlidingDFT/blob/master/sliding_dft.hpp
        twiddle = exp(1i*2*pi*(0:N-1).' / N);
        % % https://github.com/betaflight/betaflight/blob/master/src/main/common/sdft.c
        % twiddle = r * exp(1i*2*pi*(0:N-1).' / N);
        X = zeros(N, 1);
        X_w = zeros(N, 1);
        ind = 1;
        scale = 1 / N;
        scale_ratio = N / sum(hann(N)) * (N - 1) / N;
    end

    % udpate signal
    x_previous = x(ind);
    x(ind) = scale * x_new;

    % update fft
    for i = 1:N
        % https://github.com/bronsonp/SlidingDFT/blob/master/sliding_dft.hpp
        X(i) = twiddle(i) * (x(ind) - r_to_N * x_previous + r * X(i));
        % % https://github.com/betaflight/betaflight/blob/master/src/main/common/sdft.c
        % X(i) = twiddle(i) * (x(ind) - r_to_N * x_old + X(i));
    end
    
    % update windowed fft (hann)
    X_w(1) = scale_ratio * (0.5*X(1) - 0.25 * (X(N) + X(2)) );
    for i = 2:N-1
        X_w(i) = scale_ratio * (0.5 * X(i) - 0.25 * (X(i-1) + X(i+1)) );
    end
    X_w(N) = scale_ratio * (0.5 * X(N) - 0.25 * (X(N-1) + X(1)) );

    % increment index
    ind = ind + 1;
    if ind > N
        ind = 1;
    end

    X_out = X;
    X_w_out = X_w;

end