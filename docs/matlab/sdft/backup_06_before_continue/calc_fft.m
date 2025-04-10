function [X, X_w] = calc_fft(x)

    N = length(x);

    w = hann(N, 'periodic');
    
    scale = 1 / N;
    scale_w = 1 / sum(w);

    % x = x - mean(x);
    
    X = fft(x) * scale;
    X_w = fft(w .* x) * scale_w;

end

