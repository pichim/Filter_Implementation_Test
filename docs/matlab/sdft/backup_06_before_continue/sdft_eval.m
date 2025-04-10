clc, clear all
%%

% Ts = 1 / 20e3;
% load data_00.mat
% time = data.time;
% inp = data.signals.values(:,1);
% out = data.signals.values(:,1) * 5.7615;
% N_data = length(time)

Ts = 8 * 50e-6;
N_data = 10000;
time = (0:N_data-1).' * Ts;

out = 10.0 + ...
     2.0 * sin(2.0*pi *  10.0*time) + ...
     7.0 * sin(2.0*pi *  50.0*time) + ...
     0*9.0 * sin(2.0*pi * 600.0*time) + ...
    10.0 * 1.0/time(end) * time;

f0 = 1.0;
f1 = 0.8 / (2.0*Ts);
t1 = time(end);
out_n = out + 20.0 * chirp(time, f0, t1, f1, 'linear', -90);

% sqrt(var) * randn
variance = 3.0;
out_n = out_n + sqrt(variance) * randn(N_data, 1);

f_min = 150.0;
% f_max = 1.2 * f1;

N = 100;
epsilon = 1e-2;


%%

if (mod(N, 2))
    N = N - 1;
end

df = 1 / (N*Ts)
freq = (0:N-1).' * df;

% w_hann = hann(N, 'periodic');
% w_hamming = hamming(N, 'periodic');
% X_hann    = calc_fft(w_hann);
% X_hamming = calc_fft(w_hamming);
% sum(w_hann)
% sum(w_hamming)
% figure(99)
% subplot(211)
% plot([w_hann, w_hamming]), grid on
% subplot(212)
% plot(freq, abs([X_hann, X_hamming])), grid on

ind_eval = 1:N/2+1;
freq = freq(ind_eval);


%%

[X_fft, X_w_fft] = calc_fft(out_n(N_data-N+1:N_data));


%%

X_sdft_M   = zeros(N_data-N+1, N/2 + 1);
X_w_sdft_M = zeros(N_data-N+1, N/2 + 1);
time_M = zeros(N_data-N+1, 1);
f_sdft_abs_max_M = zeros(N_data-N+1, 1);
f_w_sdft_abs_max_M = zeros(N_data-N+1, 1);
X_sdft_avg_M = zeros(N/2 + 1, 1);
X_w_sdft_avg_M = zeros(N/2 + 1, 1);

cntr = 0;
for i = 1:N_data
    [X_sdft, X_w_sdft, is_valid] = sdft_apply(out_n(i), N, epsilon);
    if (is_valid) % N_data-N+1 times valid

        cntr = cntr + 1;

        X_sdft_avg_M = X_sdft_avg_M + abs(X_sdft).^2 * N;
        X_w_sdft_avg_M = X_w_sdft_avg_M + abs(X_w_sdft).^2 * N;

        X_sdft_M(cntr,:) = X_sdft.';
        X_w_sdft_M(cntr,:) = X_w_sdft.';
        time_M(cntr) = time(i);

        X_sdft_abs = abs(X_sdft);
        X_sdft_abs_max = max( X_sdft_abs(freq > f_min) );
        f_sdft_abs_max_M(cntr) = freq( X_sdft_abs == X_sdft_abs_max);

        X_w_sdft_abs = abs(X_w_sdft);
        X_w_sdft_abs_max = max( X_w_sdft_abs(freq > f_min) );
        f_w_sdft_abs_max_M(cntr) = freq( X_w_sdft_abs == X_w_sdft_abs_max);
    end
end

X_sdft_avg_M = X_sdft_avg_M / cntr;
X_w_sdft_avg_M = X_w_sdft_avg_M / cntr;


%%

[X_fft(1:3), X_sdft(1:3)]
[X_w_fft(1:3), X_w_sdft(1:3)]


%%


figure(1)
subplot(311)
plot(time, [out_n, out]), grid on
xlabel('Time (sec)')
title('FFT vs SDFT')
subplot(323)
plot(freq, abs([X_fft(ind_eval), X_sdft])), grid on
ylabel('Magnitude')
subplot(324)
plot(freq, abs([X_fft(ind_eval) - X_sdft])), grid on
ylabel('Magnitude Difference')
subplot(325)
plot(freq, real([X_fft(ind_eval), X_sdft])), grid on
xlabel('Frequency (Hz)'), ylabel('Real')
subplot(326)
plot(freq, imag([X_fft(ind_eval), X_sdft])), grid on
xlabel('Frequency (Hz)'), ylabel('Imag')


figure(2)
subplot(311)
plot(time, [out_n, out]), grid on
xlabel('Time (sec)')
title('FFT vs SDFT windowed')
subplot(323)
plot(freq, abs([X_w_fft(ind_eval), X_w_sdft])), grid on
ylabel('Magnitude')
subplot(324)
plot(freq, abs([X_w_fft(ind_eval) - X_w_sdft])), grid on
ylabel('Magnitude Difference')
subplot(325)
plot(freq, real([X_w_fft(ind_eval), X_w_sdft])), grid on
xlabel('Frequency (Hz)'), ylabel('Real')
subplot(326)
plot(freq, imag([X_w_fft(ind_eval), X_w_sdft])), grid on
xlabel('Frequency (Hz)'), ylabel('Imag')


figure(3)
subplot(211)
qmesh = pcolor(time_M, freq, abs(X_sdft_M).'); hold on
plot(time_M, time_M * ((f1 - f0) / t1) + f0, 'k')
plot(time_M, f_sdft_abs_max_M), hold off
set(qmesh, 'EdgeColor', 'None');
title('SDFT vs. Time')
xlabel('Time (sec)'), ylabel('Frequency (Hz)')
colormap('jet')
set(gca, 'ColorScale', 'log')
subplot(212)
qmesh = pcolor(time_M, freq, abs(X_w_sdft_M).'); hold on
plot(time_M, time_M * ((f1 - f0) / t1) + f0, 'k')
plot(time_M, f_w_sdft_abs_max_M), hold off
set(qmesh, 'EdgeColor', 'None');
title('SDFT vs. Time windowed')
xlabel('Time (sec)'), ylabel('Frequency (Hz)')
colormap('jet')
set(gca, 'ColorScale', 'log')


figure(4)
plot(freq, sqrt([X_sdft_avg_M, X_w_sdft_avg_M]).^2), grid on
set(gca, 'YScale', 'log')
xlabel('Frequency (Hz)') %, ylabel('Imag')
title(sprintf("var = %0.2e, var(X) = %0.2e, var(Xw) = %0.2e", ...
    variance, mean(X_sdft_avg_M), mean(X_w_sdft_avg_M) * 2.0 / 3.0))


%%

noverlap = 0; % N-1

pxx_m   = pwelch(out_n, ones(N,1), noverlap, N, 1/Ts, 'power');
pxx_w_m = pwelch(out_n, hann(N, 'periodic'), noverlap, N, 1/Ts, 'power');

pxx = estimate_spectras(out_n, ones(N,1), noverlap, N, Ts);
pxx_w = estimate_spectras(out_n, hann(N, 'periodic'), noverlap, N, Ts);
pxx = pxx / 2;
pxx_w = pxx_w / 2;

figure(5)
plot(freq, [pxx_m, pxx_w_m]), grid on, hold on
plot(freq, [pxx, pxx_w]), hold off
set(gca, 'YScale', 'log')
xlabel('Frequency (Hz)') %, ylabel('Imag')

