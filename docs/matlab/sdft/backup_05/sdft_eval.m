clc, clear all
%%

% Ts = 1 / 20e3;
% load data_00.mat
% time = data.time;
% inp = data.signals.values(:,1);
% out = data.signals.values(:,1) * 5.7615;
% N_data = length(time)

Ts = 1e-3;
N_data = 1000;
time = (0:N_data-1).' * Ts;

out = 10 + ...
    2 * sin(2*pi* 10*time) + ...
    7 * sin(2*pi* 50*time) + ...
    5 * sin(2*pi*120*time) + ...
    0 * 1/time(end) * time;

out = out + 20 * chirp(time, 1, time(end), 0.8 / (2*Ts), 'linear', -90);

%%

N = 100;
if (mod(N, 2))
    N = N - 1;
end
% x = out(1:N);

df = 1 / (N*Ts)
freq = (0:N-1).' * df;

ind_eval = 1:N/2+1;

w_hann = hann(N, 'periodic');
w_hamming = hamming(N, 'periodic');
X_hann    = calc_fft(w_hann);
X_hamming = calc_fft(w_hamming);
sum(w_hann)
sum(w_hamming)
figure(99)
subplot(211)
plot([w_hann, w_hamming]), grid on
subplot(212)
plot(freq, abs([X_hann, X_hamming])), grid on


%%

[X_fft, X_w_fft] = calc_fft(out(N_data-N+1:N_data));


%%

X_sdft_M   = zeros(N_data-N+1, N/2 + 1);
X_w_sdft_M = zeros(N_data-N+1, N/2 + 1);
time_M = zeros(N_data-N+1, 1);

ind = 1;
for i = 1:N_data
    [X_sdft, X_w_sdft, is_valid] = calc_sdft(out(i), N, 1e-4);
    if (is_valid) % N_data-N+1 times valid
        X_sdft_M(ind,:) = X_sdft.';
        X_w_sdft_M(ind,:) = X_w_sdft.';
        time_M(ind) = time(i);
        ind = ind + 1;
    end
end


%%


[X_fft(1:3), X_sdft(1:3)]
[X_w_fft(1:3), X_w_sdft(1:3)]


%%


figure(11)
subplot(311)
plot(time, out), grid on
xlabel('Time (sec)')
title('FFT vs SDFT')
subplot(323)
plot(freq(ind_eval), abs([X_fft(ind_eval), X_sdft])), grid on
ylabel('Magnitude')
subplot(324)
plot(freq(ind_eval), abs([X_fft(ind_eval) - X_sdft])), grid on
ylabel('Magnitude Difference')
subplot(325)
plot(freq(ind_eval), real([X_fft(ind_eval), X_sdft])), grid on
xlabel('Frequency (Hz)'), ylabel('Real')
subplot(326)
plot(freq(ind_eval), imag([X_fft(ind_eval), X_sdft])), grid on
xlabel('Frequency (Hz)'), ylabel('Imag')


figure(22)
subplot(311)
plot(time, out), grid on
xlabel('Time (sec)')
title('FFT vs SDFT windowed')
subplot(323)
plot(freq(ind_eval), abs([X_w_fft(ind_eval), X_w_sdft])), grid on
ylabel('Magnitude')
subplot(324)
plot(freq(ind_eval), abs([X_w_fft(ind_eval) - X_w_sdft])), grid on
ylabel('Magnitude Difference')
subplot(325)
plot(freq(ind_eval), real([X_w_fft(ind_eval), X_w_sdft])), grid on
xlabel('Frequency (Hz)'), ylabel('Real')
subplot(326)
plot(freq(ind_eval), imag([X_w_fft(ind_eval), X_w_sdft])), grid on
xlabel('Frequency (Hz)'), ylabel('Imag')


X_fft(1)
X_sdft(1)
X_w_fft(1)
X_w_sdft(1)


figure(33)
subplot(211)
qmesh = pcolor(time_M, freq(ind_eval), abs(X_sdft_M).');
set(qmesh, 'EdgeColor', 'None');
title('SDFT vs. Time')
xlabel('Time (sec)'), ylabel('Frequency (Hz)')
colormap('jet')
set(gca, 'ColorScale', 'log')
% ylim([0 1/(2.0*Ts)])
subplot(212)
qmesh = pcolor(time_M, freq(ind_eval), abs(X_w_sdft_M).');
set(qmesh, 'EdgeColor', 'None');
title('SDFT vs. Time windowed')
xlabel('Time (sec)'), ylabel('Frequency (Hz)')
colormap('jet')
set(gca, 'ColorScale', 'log')
% ylim([0 1/(2.0*Ts)])






