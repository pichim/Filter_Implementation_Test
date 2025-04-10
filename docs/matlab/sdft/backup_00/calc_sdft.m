function [X, X_w] = calc_sdft(x, N)

    r = 1.0 - 1e-4 * 0;
    r_to_N = r^N;
    
    scale = 1 / N;
    scale_ratio = N / sum(hann(N));
    
    X = zeros(N, 1);
    X_w = zeros(N, 1);
    
    for i = 1:N
        for j = 1:N
            % https://github.com/bronsonp/SlidingDFT/blob/master/sliding_dft.hpp
            twiddle = exp(1i*2*pi*(j - 1) / N);
            X(j) = twiddle * (scale * x(i) + r * X(j));
            % % https://github.com/betaflight/betaflight/blob/master/src/main/common/sdft.c
            % twiddle = r * exp(1i*2*pi*(j - 1) / N);
            % X(j) = twiddle * (scale * x(i) + X(j));
        end
    end
    
    X_w(1) = scale_ratio * (0.5*X(1) - 0.25 * (X(N) + X(2)) );
    for i = 2:N-1
        X_w(i) = scale_ratio * (0.5 * X(i) - 0.25 * (X(i-1) + X(i+1)) );
    end
    X_w(N) = scale_ratio * (0.5 * X(N) - 0.25 * (X(N-1) + X(1)) );

end

