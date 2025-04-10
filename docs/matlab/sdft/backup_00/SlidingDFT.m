function [X_out, X_w_out] = SlidingDFT(x_new, N)

    X_w = zeros(N, 1);

    persistent x X Xw ind
    if isempty(x)
        x = zeros(N, 1);
        X = zeros(N, 1);
        X_w = zeros(N, 1);
        ind = 1;
        display("init");
    end

    r = 1.0 - 1e-4 * 0;
    r_to_N = r^N;
    
    scale = 1 / N;
    scale_ratio = N / sum(hann(N));

    x_old = x(ind);
    x(ind) = scale * x_new;
        
    for i = 1:N
        % https://github.com/bronsonp/SlidingDFT/blob/master/sliding_dft.hpp
        twiddle = exp(1i*2*pi*(i - 1) / N);
        X(i) = twiddle * (x(ind) - r_to_N * x_old + r * X(i));
        % % https://github.com/betaflight/betaflight/blob/master/src/main/common/sdft.c
        % twiddle = r * exp(1i*2*pi*(i - 1) / N);
        % X(i) = twiddle * (x(ind) - r_to_N * x_old + X(i));
    end
    
    X_w(1) = scale_ratio * (0.5*X(1) - 0.25 * (X(N) + X(2)) );
    for i = 2:N-1
        X_w(i) = scale_ratio * (0.5 * X(i) - 0.25 * (X(i-1) + X(i+1)) );
    end
    X_w(N) = scale_ratio * (0.5 * X(N) - 0.25 * (X(N-1) + X(1)) );

    ind = ind + 1;
    if ind > N
        ind = 1;
    end

    X_out = X;
    X_w_out = X_w;

end