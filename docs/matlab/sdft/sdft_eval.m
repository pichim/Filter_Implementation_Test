clc, clear all
addpath ..\iirfilter\
addpath ..\iirfilter\c_implementation\
addpath ..\lib
%%

% Notes:
% - Currently the current controller runs at 25 kHz
% - I assume the outher loops, so the vel and pos controller run at 5 kHz
% - Direct fft and sdft are equal only if epsilon is zero
% - Peak detection works best for abs(X) and not X*conj(X) = abs(X)^2

% TODO:
% - Develop better filter strategy to trak frequency peaks

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
    20.0 * sin(2.0*pi *   3.5*time) + ...
    0*7.0 * sin(2.0*pi *  50.0*time) + ...
    0*9.0 * sin(2.0*pi * 600.0*time) + ...
    30.0 * 1.0/time(end) * time;
% out = 0 * out;

% add additional sinus
ind = time >= 2.0;% & time <= 3.0;
out(ind) = out(ind) + ...
    20.0 * sin(2.0*pi * 291.0*time(ind)) + ...
    10.0 * sin(2.0*pi * 500.0*time(ind));

% add chirp signal
f0 = 1.0;            % start frequency
f1 = 0.6 / (2.0*Ts); % end   frequency
A = 40;
ind_chirp = time <= T_sim / 2;
time_chirp = time(ind_chirp);
t1 = time_chirp(end); % chirp time
out(ind_chirp) = out(ind_chirp) + A * chirp(time_chirp, f0, t1, f1, 'linear', -90);
ind_chirp = time > T_sim / 2;
time_chirp = time(ind_chirp);
out(ind_chirp) = out(ind_chirp) + A * flipud(chirp(time_chirp, f1, time_chirp(end) - t1, f0, 'linear', -90));

% add noise, sqrt(var) * randn
variance = 1.0;
out_n = out + sqrt(variance) * randn(N_sim, 1);

% sdft stuff
N = 100;       % numbers of sdft samples
N_peak = 3;    % number of peaks the algorithm tracks
ptn_ratio_min = 30;
f_min = 100.0; % minimum tracking frequency, hat to fit onto half bin
f_max = 600.0; % maximum
epsilon = 1e-4;


clc, clear all
load data_04.mat
Ts_fast = 1/20e3;
N_ds = 3;            % downsampling factor
Ts = N_ds * Ts_fast; % sampling time
out = resample(data.signals.values(:,6), 1, N_ds); % Downsample by N_ds, includes filtering
N_sim = length(out); % total number of data points
% add noise, sqrt(var) * randn
variance = 0.0;
out_n = out + sqrt(variance) * randn(N_sim, 1);
time = (0:N_sim-1).' * Ts;
T_sim = time(end);   % simulation time
% out = diff(out);
% out = [out(1); out];
% out_n = diff(out_n);
% out_n = [out_n(1); out_n];

% sdft stuff
N = 300;       % numbers of sdft samples
N_peak = 3;    % number of peaks the algorithm tracks
ptn_ratio_min = 30;
f_min = 1.0e3; % minimum tracking frequency, hat to fit onto half bin
f_max = 3.0e3; % maximum
epsilon = 1e-4;


clc, clear all
% load noSM_DC_Relay_02_50.mat
load SM50_30_DC_Relay_02_50_ds.mat
% load CB_DC_Relay_15_40_ds.mat
Ts_fast = 1/25e3;
N_ds = 5;            % downsampling factor
Ts = N_ds * Ts_fast; % sampling time
out = resample(omega, 1, N_ds);
N_sim = length(out); % total number of data points
% add noise, sqrt(var) * randn
variance = 0.0;
out_n = out + sqrt(variance) * randn(N_sim, 1);
time = (0:N_sim-1).' * Ts;
T_sim = time(end);   % simulation time

% sdft stuff
N = 100;       % numbers of sdft samples
N_peak = 3;    % number of peaks the algorithm tracks
ptn_ratio_min = 30;
f_min = 0.3e3; % minimum tracking frequency, hat to fit onto half bin
f_max = 1.1e3; % maximum
epsilon = 1e-4;


clc, clear all
load chirp_50Hz_to_1kHz_500_msec_1_A.mat
Ts_fast = 1/25e3;
N_ds = 5;            % downsampling factor
Ts = N_ds * Ts_fast; % sampling time
out = resample(omega, 1, N_ds);
N_sim = length(out); % total number of data points
% add noise, sqrt(var) * randn
variance = 0.0;
out_n = out + sqrt(variance) * randn(N_sim, 1);
time = (0:N_sim-1).' * Ts;
T_sim = time(end);   % simulation time

% sdft stuff
N = 100;       % numbers of sdft samples
N_peak = 1;    % number of peaks the algorithm tracks
ptn_ratio_min = 30;
f_min = 0.1e3; % minimum tracking frequency, hat to fit onto half bin
f_max = 1.0e3; % maximum
epsilon = 1e-4;


df = 1/(N * Ts);       % SDFT frequency resolution
freq = (0:N-1).' * df; % frequency
ind_eval = 1:N/2 + 1;  % we only need to use N/2 data points
freq = freq(ind_eval);

ind_min = ceil(f_min/df) + 1;
ind_max = floor(f_max/df) + 1;
f_min = (ind_min - 1) * df;
f_max = (ind_max - 1) * df;

% create iir filters
f_init = f_max; %(f_max - f_min) / 2.0 + f_min;
% f_cut  = 10.0;
% lowpass1 = get_iir_filter();
% lowpass1 = lowpass1_init(lowpass1, f_cut, Ts);
% lowpass1 = iir_filter_reset(lowpass1, f_init);
f_cut = 200.0;
knl1 = 2.0 * pi * f_cut;
knl2 = 0.0 * (0.9 * pi / Ts - knl1) / (2 * (f_max - f_min));

% filter spectral density over time
f_cut = inf * 1.0;
b0 = 1.0 - exp(-Ts * 2.0 * pi * f_cut);
a0 = b0 - 1.0;

D = sqrt(3)/2;
% create fading_notch_filter
for i = 1:N_peak
    fading_notch = get_fading_notch_filter();
    fading_notch = fading_notch_init(fading_notch, ...
                                     f_init, ...
                                     D, ...
                                     f_min, ...
                                     f_min + 50, ...
                                     Ts);
    fading_notches{i} = fading_notch;
end
clear fading_notch

fprintf('   --- SDFT Eval Script ---\n');
fprintf('    Sampling Time %24.2f musec\n', 1e6 * Ts);
fprintf('    Sampling Frequency %17.2f kHz\n', 1e-3 / Ts);
fprintf('    Theoretical Buffer Length %8d\n', N);
fprintf('    Actual Buffer Length %13d\n', N/2 + 1);
fprintf('    Frequency Resolution %16.2f Hz\n', df);
fprintf('    SDFT Min. Frequency %17.2f Hz\n', f_min);
fprintf('    SDFT Max. Frequency %17.2f Hz\n', f_max);


%%

X_spg_eval   = zeros(N_sim-N+1, N/2 + 1);
X_w_spg_eval = zeros(N_sim-N+1, N/2 + 1);

X_abs_avg_eval   = zeros(N/2 + 1, 1);
X_w_abs_avg_eval = zeros(N/2 + 1, 1);

P_avg_eval   = zeros(N/2 + 1, 1);
P_w_avg_eval = zeros(N/2 + 1, 1);

f_peak_eval   = zeros(N_sim-N+1, N_peak);
f_peak_f_eval = zeros(N_sim-N+1, N_peak);

ptn_ratio_eval   = zeros(N/2 + 1, N_peak);
X_peak_eval      = zeros(N/2 + 1, N_peak);
X_mean_rest_eval = zeros(N/2 + 1, 1);

clear sdft_apply
cntr = 1;
for i = 1:N_sim

    % update sdft
    [X, X_w, is_valid] = sdft_apply(out_n(i), N, epsilon, Ts);

    if (is_valid) % N_data-N+1 times valid, we have to fill the buffer first

        % spectras averaged filter
        if (cntr == 1)
            X_squared   = real(2 * X   .* conj(X  ));
            X_w_squared = real(2 * X_w .* conj(X_w));
        end
        X_squared   = b0 * real(2 * X   .* conj(X  )) - a0 * X_squared  ;
        X_w_squared = b0 * real(2 * X_w .* conj(X_w)) - a0 * X_w_squared;

                % spectrogram
        X_spg_eval(cntr,:)   = sqrt(X_squared  ).';
        X_w_spg_eval(cntr,:) = sqrt(X_w_squared).';

        % spectras averaged average
        X_abs_avg_eval   = X_abs_avg_eval   + abs(X)  ;
        X_w_abs_avg_eval = X_w_abs_avg_eval + abs(X_w);
    
        % psd averaged
        P_avg_eval   = P_avg_eval   + real(2 * X .* conj(X));
        P_w_avg_eval = P_w_avg_eval + real(2 * X_w .* conj(X_w));

        % % [f_peak_candidate, is_peak, ptn_ratio, X_peak, X_mean_rest] = ...
        %     % find_peak(X_w_eval, ind_min, ind_max, df, ptn_ratio_min);
        [f_peak_candidate, is_peak, ptn_ratio, X_peak, X_mean_rest] = ...
            find_peaks(X_w_squared, ind_min, ind_max, df, ptn_ratio_min, N_peak);
        ptn_ratio_eval(cntr, :) = ptn_ratio;
        X_peak_eval(cntr, :)    = X_peak;
        X_mean_rest_eval(cntr)  = X_mean_rest;

        % [f_peak_candidate, ind_sorted] = sort(f_peak_candidate, 'ascend');
        % is_peak = is_peak(ind_sorted);
        % ptn_ratio = ptn_ratio(ind_sorted);
        % X_peak = X_peak(ind_sorted);

        % [f_peak_candidate(1:sum(is_peak)), ind_sorted] = sort(f_peak_candidate(1:sum(is_peak)), 'ascend');
        % temp = ptn_ratio(1:sum(is_peak));
        % ptn_ratio(1:sum(is_peak)) = temp(ind_sorted);
        % temp = X_peak(1:sum(is_peak));
        % X_peak(1:sum(is_peak)) = temp(ind_sorted);
        % temp = is_peak(1:sum(is_peak));
        % is_peak(1:sum(is_peak)) = temp(ind_sorted);
        
        for j = 1:N_peak
            if (is_peak(j))
                f_peak_eval(cntr, j) = f_peak_candidate(j);
            else
                if (cntr == 1)
                    f_peak_eval(cntr, j) = f_init;
                else
                    f_peak_eval(cntr, j) = f_peak_eval(cntr-1, j);
                end
            end
        end

        % % lowpass filter
        % [lowpass1_w, val_f] = iir_filter_apply(lowpass1_w, f_w_peak_eval(cntr));
        % f_w_peak_f_eval(cntr) = val_f;
        if (cntr == 1)
            val_w_f_past = f_peak_eval(cntr, :);
        end
        val_f = nl_lowpass(f_peak_eval(cntr, :), val_w_f_past, knl1, knl2, Ts);
        val_w_f_past = val_f;
        f_peak_f_eval(cntr, :) = val_f;

        % increment counter
        cntr = cntr + 1;
    end
end

% normalise spectras averaged
X_abs_avg_eval   = X_abs_avg_eval / (cntr - 1);
X_w_abs_avg_eval = X_w_abs_avg_eval / (cntr - 1);

% normalise psd averaged
P_avg_eval   = P_avg_eval / (cntr - 1);
P_w_avg_eval = P_w_avg_eval / (cntr - 1);


%%

X_w_f_spg_eval = zeros(N_sim-N+1, N/2 + 1);

out_f = zeros(N_sim, 1);

val_f = out_n(1);

clear sdft_apply
cntr = 1;
for i = 1:N_sim
           
    % update sdft
    [~, X_w_f, is_valid] = sdft_apply(val_f, N, epsilon, Ts);

    if (is_valid) % N_data-N+1 times valid, we have to fill the buffer first

        % update fading notch
        [fading_notches{1}, val_f] = fading_notch_filter_apply(fading_notches{1}, f_peak_f_eval(cntr, 1), out_n(i));
        for j = 2:N_peak
            [fading_notches{j}, val_f] = fading_notch_filter_apply(fading_notches{j}, f_peak_f_eval(cntr, j), val_f);
        end
        out_f(i) = val_f;

        % spectrogram
        X_w_f_spg_eval(cntr,:) = X_w_f.';

        % increment counter
        cntr = cntr + 1;
    else
        % update fading notch
        [fading_notches{1}, val_f] = fading_notch_filter_apply(fading_notches{1}, f_init, out_n(i));
        for j = 2:N_peak
            [fading_notches{j}, val_f] = fading_notch_filter_apply(fading_notches{j}, f_init, val_f);
        end
    end
end

%% compare result with direct fft

[X_fft, X_w_fft] = calc_fft(out_n(N_sim-N+1:N_sim));

N_comp = 3;
err   = X_fft(1:N_comp,:) - X(1:N_comp,:);
err_w = X_w_fft(1:N_comp,:) - X_w(1:N_comp,:);

fprintf('    Err. First %d Points: %18.2e\n', N_comp, norm(err));
fprintf('    Err. First %d Points Windowed: %9.2e\n', N_comp, norm(err_w));


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
plot(time, [out_n, out, out_f]), grid on
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
subplot(311)
qmesh = pcolor(time(N:end), freq, abs(X_spg_eval).');
set(qmesh, 'EdgeColor', 'None');
title('SDFT vs. Time')
xlabel('Time (sec)'), ylabel('Frequency (Hz)')
colormap('jet')
set(gca, 'ColorScale', 'log')
subplot(312)
qmesh = pcolor(time(N:end), freq, abs(X_w_spg_eval).'); hold on
plot(time(N:end), f_peak_eval, 'k')
plot(time(N:end), f_peak_f_eval, 'Color', [0 0.5 0]), hold off
set(qmesh, 'EdgeColor', 'None');
title('SDFT vs. Time windowed')
xlabel('Time (sec)'), ylabel('Frequency (Hz)')
colormap('jet')
set(gca, 'ColorScale', 'log')
subplot(313)
qmesh = pcolor(time(N:end), freq, abs(X_w_f_spg_eval).'); hold on
plot(time(N:end), f_peak_eval, 'k')
plot(time(N:end), f_peak_f_eval, 'Color', [0 0.5 0]), hold off
set(qmesh, 'EdgeColor', 'None');
title('SDFT vs. Time windowed after Notch')
xlabel('Time (sec)'), ylabel('Frequency (Hz)')
colormap('jet')
set(gca, 'ColorScale', 'log')

figure(4)
subplot(311)
plot(time(N:end), X_mean_rest_eval), grid on
xlabel('Time (sec)'), ylabel('Noise Floor')
subplot(312)
plot(time(N:end), X_peak_eval), grid on
xlabel('Time (sec)'), ylabel('Peak')
subplot(313)
plot(time(N:end), (ptn_ratio_eval)), grid on
xlabel('Time (sec)'), ylabel('Peak to Noise Ratio')

% n = 3;
% N_overlap = n*N - 1;
% 
% figure(5)
% pwelch([out, out_n], ones(n*N,1), N_overlap, n*N, 1/Ts, 'power');
% 
% 
% return

%%

N_overlap = N - 1;

% % welch
% P   = estimate_spectras(out_n, ones(N,1)          , N_overlap, N, Ts);
% P_w = estimate_spectras(out_n, hann(N, 'periodic'), N_overlap, N, Ts);
% P   = P / 2;
% P_w = P_w / 2;

% welch matlab
P_welch   = pwelch(out_n, ones(N,1)          , N_overlap, N, 1/Ts, 'power');
P_w_welch = pwelch(out_n, hann(N, 'periodic'), N_overlap, N, 1/Ts, 'power');

figure(6)
% subplot(211)
plot(freq, [P_avg_eval, P_w_avg_eval]), grid on, hold on
% plot(freq, [P, P_w])
plot(freq, [P_welch, P_w_welch]), hold off
set(gca, 'YScale', 'log')
xlabel('Frequency (Hz)')
legend('P avg eval', 'Pw avgeval', ... % 'P', 'Pw', ...
    'P welch', 'Pw welch', ...
    'location', 'best')
% subplot(212)
% plot(freq, [X_abs_avg_eval, X_w_abs_avg_eval]), grid on
% set(gca, 'YScale', 'log')
% xlabel('Frequency (Hz)')
% legend('X_abs_avg_eval', 'X_w_abs_avg_eval', ...
%     'location', 'best')
