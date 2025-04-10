clc, clear all
%%

% Notes:
% - Currently the current controller runs at 25 kHz
% - I assume the outher loops, so the vel and pos controller run at 5 kHz
% - mod(N, 2) has to be zero
% - Direct fft and sdft are equal only if epsilon is zero
% - Peak detection works best for abs(X) and not X*conj(X) = abs(X)^2

Ts_fast = 1/5e3;
N_ds = 4;            % downsampling factor
Ts = N_ds * Ts_fast; % sampling time

T_sim = 5;                 % simulation time
N_sim = floor(T_sim / Ts); % total number of data points
T_sim = N_sim * Ts;        % updated simulation time

% time
time = (0:N_sim-1).' * Ts;

% signal
out = 10.0 + ...
     2.0 * sin(2.0*pi *  12.5*time) + ...
     7.0 * sin(2.0*pi *  50.0*time) + ...
   0*9.0 * sin(2.0*pi * 600.0*time) + ...
    10.0 * 1.0/time(end) * time;

% add chirp signal
f0 = 1.0;            % start frequency
f1 = 0.8 / (2.0*Ts); % end   frequency
A = 20;
ind_chirp = time <= T_sim / 2;
time_chirp = time(ind_chirp);
t1 = time_chirp(end);      % chirp time
out(ind_chirp) = out(ind_chirp) + A * chirp(time_chirp, f0, t1, f1, 'linear', -90);
ind_chirp = time > T_sim / 2;
time_chirp = time(ind_chirp);
out(ind_chirp) = out(ind_chirp) + A * flipud(chirp(time_chirp, f1, time_chirp(end) - t1, f0, 'linear', -90));

% add noise, sqrt(var) * randn
variance = 100.0;
out_n = out + sqrt(variance) * randn(N_sim, 1);

N = 50;       % numbers of sdft samples
f_min = 150.0; % minimum tracking frequency
f_max = 400.0; % maximum
% f_max = 1.2 * f1;
epsilon = 1e-4;

df = 1/(N * Ts);       % SDFT frequency resolution
freq = (0:N-1).' * df; % frequency
ind_eval = 1:N/2 + 1;  % we only need to use N/2 data points
freq = freq(ind_eval);

fprintf('   --- SDFT Eval Script ---\n');
fprintf('    Sampling Time: %18.2f musec\n', 1e6 * Ts);
fprintf('    Sampling Frequency: %11.2f kHz\n', 1e-3 / Ts);
fprintf('    Theretical Buffer Length: %4d\n', N);
fprintf('    Actual Buffer Length: %7d\n', N/2 + 1);
fprintf('    Frequency Resolution: %10.2f Hz\n', df);


%%

% place holder for spectrogram
X_spg_eval   = zeros(N_sim-N+1, N/2 + 1);
X_w_spg_eval = zeros(N_sim-N+1, N/2 + 1);

f_max_eval   = zeros(N_sim-N+1, 1);
f_w_max_eval = zeros(N_sim-N+1, 1);

P_avg_eval   = zeros(N/2 + 1, 1);
P_w_avg_eval = zeros(N/2 + 1, 1);

cntr = 1;
for i = 1:N_sim
    [X, X_w, is_valid] = sdft_apply(out_n(i), N, epsilon);
    if (is_valid) % N_data-N+1 times valid, we have to fill the buffer first

        % spectrogram
        X_spg_eval(cntr,:)   = X.';
        X_w_spg_eval(cntr,:) = X_w.';

        % psd
        P_avg_eval   = P_avg_eval   + X .* conj(X) * 2;
        P_w_avg_eval = P_w_avg_eval + X_w .* conj(X_w) * 2;

        % evaluate max frequency
        % X_eval = X .* conj(X) * 2;
        X_eval = abs(X);
        f_max_eval(cntr) = fit_max_freq_parabola(X_eval, freq, N, f_min, f_max, df);

        % evaluate max frequency for windowed version
        % X_w_eval = X_w .* conj(X_w) * 2;
        X_w_eval = abs(X_w);
        f_w_max_eval(cntr) = fit_max_freq_parabola(X_w_eval, freq, N, f_min, f_max, df);

        % increment counter
        cntr = cntr + 1;
    end
end

% normalise psd
P_avg_eval   = P_avg_eval / cntr;
P_w_avg_eval = P_w_avg_eval / cntr;


%% compare result with direct fft

[X_fft, X_w_fft] = calc_fft(out_n(N_sim-N+1:N_sim));

N_comp = 10;
err   = X_fft(1:N_comp,:) - X(1:N_comp,:);
err_w = X_w_fft(1:N_comp,:) - X_w(1:N_comp,:);

fprintf('    Squared Error Norm First %d Data Points: %18.2e\n', N_comp, norm(err));
fprintf('    Squared Error Norm First %d Data Points Windowed: %9.2e\n', N_comp, norm(err_w));


%%

figure(1)
subplot(311)
plot(time, [out_n, out]), grid on
xlabel('Time (sec)')
title('FFT vs SDFT')
subplot(323)
plot(freq, abs([X_fft(ind_eval), X])), grid on
ylabel('Magnitude')
subplot(324)
plot(freq, abs([X_fft(ind_eval) - X])), grid on
ylabel('Magnitude Difference')
subplot(325)
plot(freq, real([X_fft(ind_eval), X])), grid on
xlabel('Frequency (Hz)'), ylabel('Real')
subplot(326)
plot(freq, imag([X_fft(ind_eval), X])), grid on
xlabel('Frequency (Hz)'), ylabel('Imag')

figure(2)
subplot(311)
plot(time, [out_n, out]), grid on
xlabel('Time (sec)')
title('FFT vs SDFT windowed')
subplot(323)
plot(freq, abs([X_w_fft(ind_eval), X_w])), grid on
ylabel('Magnitude')
subplot(324)
plot(freq, abs([X_w_fft(ind_eval) - X_w])), grid on
ylabel('Magnitude Difference')
subplot(325)
plot(freq, real([X_w_fft(ind_eval), X_w])), grid on
xlabel('Frequency (Hz)'), ylabel('Real')
subplot(326)
plot(freq, imag([X_w_fft(ind_eval), X_w])), grid on
xlabel('Frequency (Hz)'), ylabel('Imag')

figure(3)
subplot(211)
qmesh = pcolor(time(N:end), freq, abs(X_spg_eval).'); hold on
% plot(time(N:end), time(N:end) * ((f1 - f0) / t1) + f0, 'k')
plot(time(N:end), f_max_eval, 'k'), hold off
set(qmesh, 'EdgeColor', 'None');
title('SDFT vs. Time')
xlabel('Time (sec)'), ylabel('Frequency (Hz)')
colormap('jet')
set(gca, 'ColorScale', 'log')
subplot(212)
qmesh = pcolor(time(N:end), freq, abs(X_w_spg_eval).'); hold on
% plot(time(N:end), time(N:end) * ((f1 - f0) / t1) + f0, 'k')
plot(time(N:end), f_w_max_eval, 'k'), hold off
set(qmesh, 'EdgeColor', 'None');
title('SDFT vs. Time windowed')
xlabel('Time (sec)'), ylabel('Frequency (Hz)')
colormap('jet')
set(gca, 'ColorScale', 'log')


%%

% figure(4)
% plot(freq, [X_avg, X_w_avg]), grid on
% set(gca, 'YScale', 'log')
% xlabel('Frequency (Hz)') %, ylabel('Imag')
% title(sprintf("var = %0.2e, var(X) = %0.2e, var(Xw) = %0.2e", ...
%     variance, mean(X_avg), mean(X_w_avg) * 2.0 / 3.0))

Noverlap = N - 1;

P   = estimate_spectras(out_n, ones(N,1)          , Noverlap, N, Ts);
P_w = estimate_spectras(out_n, hann(N, 'periodic'), Noverlap, N, Ts);
P   = P / 2;
P_w = P_w / 2;

P_welch   = pwelch(out_n, ones(N,1)          , Noverlap, N, 1/Ts, 'power');
P_w_welch = pwelch(out_n, hann(N, 'periodic'), Noverlap, N, 1/Ts, 'power');

figure(5)
plot(freq, [P_welch, P_w_welch]), grid on, hold on
plot(freq, [P, P_w])
plot(freq, [P_avg_eval, P_w_avg_eval]), hold off
set(gca, 'YScale', 'log')
xlabel('Frequency (Hz)')
legend







return
%%

clc, clear all

syms x0 x1 x2 y0 y1 y2

M = [x0^2 x0 1; ...
     x1^2 x1 1; ...
     x2^2 x2 1]

theta = M^-1 * [y0; y1; y2]

a = simplify( theta(1) )
% -(x0*y1 - x1*y0 - x0*y2 + x2*y0 + x1*y2 - x2*y1)/((x0 - x1)*(x0 - x2)*(x1 - x2))
b = simplify( theta(2) )
% (x0^2*y1 - x1^2*y0 - x0^2*y2 + x2^2*y0 + x1^2*y2 - x2^2*y1)/((x0 - x1)*(x0 - x2)*(x1 - x2))
c = simplify( theta(3) )
% -(- y2*x0^2*x1 + y1*x0^2*x2 + y2*x0*x1^2 - y1*x0*x2^2 - y0*x1^2*x2 + y0*x1*x2^2)/((x0 - x1)*(x0 - x2)*(x1 - x2))

x_max = simplify( -b / (2 * a) )
% (x0^2*y1 - x1^2*y0 - x0^2*y2 + x2^2*y0 + x1^2*y2 - x2^2*y1) / (2*(x0*y1 - x1*y0 - x0*y2 + x2*y0 + x1*y2 - x2*y1))

%%

clc, clear all

squar_fun = @(a, b, c, x) a * x .* x + b * x + c;

a = -1;
b =  1;
c =  1;

x = (-1:0.01:1).';
y = squar_fun(a, b, c, x);

x0 = x(max(find(x <= -0.9)));
x1 = x(max(find(x <=  0.0)));
x2 = x(max(find(x <=  0.9)));

y0 = squar_fun(a, b, c, x0);
y1 = squar_fun(a, b, c, x1);
y2 = squar_fun(a, b, c, x2);

a_est = -(x0*y1 - x1*y0 - x0*y2 + x2*y0 + x1*y2 - x2*y1)/((x0 - x1)*(x0 - x2)*(x1 - x2))
b_est = (x0^2*y1 - x1^2*y0 - x0^2*y2 + x2^2*y0 + x1^2*y2 - x2^2*y1)/((x0 - x1)*(x0 - x2)*(x1 - x2))
c_est = -(- y2*x0^2*x1 + y1*x0^2*x2 + y2*x0*x1^2 - y1*x0*x2^2 - y0*x1^2*x2 + y0*x1*x2^2)/((x0 - x1)*(x0 - x2)*(x1 - x2))

% x_max_est = (x0^2*y1 - x1^2*y0 - x0^2*y2 + x2^2*y0 + x1^2*y2 - x2^2*y1) / (2*(x0*y1 - x1*y0 - x0*y2 + x2*y0 + x1*y2 - x2*y1))
% x_max_est = (x0^2*(y1 - y2) + x1^2*(y2 - y0) + x2^2*(y0 - y1)) / (2*(x0*(y1 - y2) + x1*(y2 - y0) + x2*(y0 - y1)))
den1 = x0 * (y1 - y2);
den2 = x1 * (y2 - y0);
den3 = x2 * (y0 - y1);
x_max_est = 0.5 * (x0*den1 + x1*den2 + x2*den3) / (den1 + den2 + den3)
y_max_est = squar_fun(a, b, c, x_max_est)

figure(99)
plot(x, y), grid on, hold on
plot([x0 x1 x2], [y0 y1 y2], 'bo')
plot(x_max_est, y_max_est, 'rx'), hold off
