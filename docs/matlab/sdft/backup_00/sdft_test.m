clc, clear variables
%%

N = 200;
Ts = 1e-3;

time = (0:N-1).' * Ts;

df = 1/(N*Ts);
freq = (0:df:1/Ts-df).';

x = 10 + ...
    2 * sin(2*pi* 10*time) + ...
    7 * sin(2*pi* 50*time) + ...
    5 * sin(2*pi*120*time);% + ...
    % randn(N,1);

W = 1 / 2;
window = hann(N);
Ww = sum(window) / N / 2;

scale = 1 / (N * W);
scale_ = 1 / (N * Ww);
scale_ratio = W / Ww;

X = fft(x) * scale;
Xw = fft(window .* x) * scale_;

X_ = zeros(size(time));
Xw_ = zeros(size(time));

r = 1.0 - 0*1e-5;
r_to_N = r^N;

% r = 0.999;
% r_to_N = r;

for i = 1:N

    for j = 1:N
        % X_(j) = r * exp(1i*2*pi*(j - 1) / N) * (X_(j) + scale * x(i));
        X_(j) = exp(1i*2*pi*(j - 1) / N) * (r * X_(j) + scale * x(i));
    end

end

Xw_(1) = scale_ratio*(0.5*X_(1) - 0.25*(X_(N) + X_(2)));
for i = 2:N-1
    Xw_(i) = scale_ratio*(0.5*X_(i) - 0.25*(X_(i-1) + X_(i+1)));
end
Xw_(N) = scale_ratio*(0.5*scale_ratio*X_(N) - 0.25*(X_(N-1) + X_(1)));


figure(1)
subplot(311)
plot(time, x)
subplot(323)
plot(freq, abs([X, X_]))
subplot(324)
plot(freq, abs([X - X_]))% ./ abs(X))
subplot(325)
plot(freq, real([X, X_]))
subplot(326)
plot(freq, imag([X, X_]))


figure(2)
subplot(311)
plot(time, x)
subplot(323)
plot(freq, abs([Xw, Xw_]))
subplot(324)
plot(freq, abs([Xw - Xw_]))% ./ abs(Xw))
subplot(325)
plot(freq, real([Xw, Xw_]))
subplot(326)
plot(freq, imag([Xw, Xw_]))


