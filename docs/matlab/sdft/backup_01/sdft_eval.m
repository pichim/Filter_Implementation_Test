clc, clear variables
%%

% Ts = 1 / 20e3;
% load data_00.mat
% time = data.time;
% inp = data.signals.values(:,1);
% out = data.signals.values(:,1) * 5.7615;
% N_data = length(time)

Ts = 1e-3;
N_data = 200;
time = (0:N_data-1).' * Ts;

out = 10 + ...
    2 * sin(2*pi* 10*time) + ...
    7 * sin(2*pi* 50*time) + ...
    5 * sin(2*pi*120*time);


%%

N = N_data;
if (mod(N, 2))
    N = N - 1;
end

x = out(1:N);

w = hann(N);

scale = 1 / N;
scale_w = 1 / sum(w);

X = fft(x) * scale;
X_w = fft(w .* x) * scale_w;


df = 1 / (N*Ts);
freq = (0:N-1).' * df; 

length(X)
length(freq)


%%

[X_, X_w_] = calc_sdft_full(x, N, 0.0);


for i = 1:N
    [X__ X_w__] = calc_sdft(x(i), N, 0.0);
end

% dft = dft.';

[X(1:3), X_(1:3), X__(1:3)]

[X_w(1:3), X_w_(1:3), X_w__(1:3)]

%%


figure(1)
subplot(311)
plot(time, x), grid on
subplot(323)
plot(freq, abs([X, X_])), grid on
subplot(324)
plot(freq, abs([X - X_])), grid on
subplot(325)
plot(freq, real([X, X_])), grid on
subplot(326)
plot(freq, imag([X, X_])), grid on


figure(2)
subplot(311)
plot(time, x), grid on
subplot(323)
plot(freq, abs([X_w, X_w_])), grid on
subplot(324)
plot(freq, abs([X_w - X_w_])), grid on
subplot(325)
plot(freq, real([X_w, X_w_])), grid on
subplot(326)
plot(freq, imag([X_w, X_w_])), grid on


figure(3)
subplot(311)
plot(time, x), grid on
subplot(323)
plot(freq, abs([X_, X__])), grid on
subplot(324)
plot(freq, abs([X_ - X__])), grid on
subplot(325)
plot(freq, real([X_, X__])), grid on
subplot(326)
plot(freq, imag([X_, X__])), grid on


figure(4)
subplot(311)
plot(time, x), grid on
subplot(323)
plot(freq, abs([X_w_, X_w__])), grid on
subplot(324)
plot(freq, abs([X_w_ - X_w__])), grid on
subplot(325)
plot(freq, real([X_w_, X_w__])), grid on
subplot(326)
plot(freq, imag([X_w_, X_w__])), grid on


X(1)
X_(1)







