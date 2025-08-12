clc, clear variables
addpath(fullfile('iirfilter'));
addpath(fullfile('lib'));
%%
% Notes:
% - Implementation of Otto and Michi are up to 5e-11 identical in Matlab
%   (double prescicion)
% - Prescision of Michis implementation is slightly better in terms of
%   computation an prescision


%% Ottos implementation

% Ts = 1/25e3;
% f1 = 0.2;
% f2 = 12500;
% Tm = 1/f1;
% 
% N = round(Tm/Ts);
% t = (0:N-1)'*Ts;
% c1 = 2*pi*Tm*f1 / log(f2/f1);
% c2 = log10(f2/f1)/Tm;
% 
% % double
% phi = c1 * (10 .^ (c2*t) - 1);
% yd = sin(phi);
% 
% % single
% phi = single(c1) * (single(single(10) .^ (single(c2)*single(t))) - single(1));
% ys = sin(phi);
% 
% figure(4)
% subplot(211)
% plot(t,ys-yd)
% subplot(212)
% plot(t,ys,t,yd)


%%

data_raw = readmatrix(fullfile('..', '..', 'output', 'data_chirp.txt'));

data.time = data_raw(:,1);
data.values = data_raw(:,2:end);           

Ts = floor(mean(diff(data.time)) * 1.0e6) * 1.0e-6

ind_exc     = 1;
ind_fchirp  = 2;
ind_sinarg  = 3;

% #define CHIRP_T1 5.0f
% #define CHIRP_F0 (1.0f / CHIRP_T1)
% #define CHIRP_F1 (1.0f / (2.0f * TS))
% #define CHIRP_OFFSET 5.0f
% #define CHIRP_AMPLITUDE 3.0f
% #define CHIRP_T_SETTLE 0.0f
chirp_t1 = 5.0;
chirp_f0 = (1.0 / chirp_t1);
chirp_f1 = (1.0 / (2.0 * Ts));
% chirp_offset = 5.0;
% chirp_amplitude = 3.0;
chirp_t_settle = 0.0;

[exc, fchirp, sinarg] = get_chirp_signals(chirp_f0, ...
    chirp_f1, ...
    chirp_t1, ...
    Ts);
Nzeros = round(chirp_t_settle/Ts) + 1;
exc    = [zeros(Nzeros, 1); exc   ];
fchirp = [zeros(Nzeros, 1); fchirp];
sinarg = [zeros(Nzeros, 1); sinarg];

% Ottos version --- starts
Tm = chirp_t1;
f1 = chirp_f0;
f2 = chirp_f1;

N = round(Tm/Ts);
t = (0:N-1)'*Ts;
c1 = 2*pi*Tm*f1 / log(f2/f1);
c2 = log10(f2/f1)/Tm;

% double
phi = c1 * (10 .^ (c2*t) - 1);
yd = sin(phi);
% Ottos version --- ends

% settle time is implemented in c to be at least one sample, does not
% affect c implementation
yd = [0;yd];

figure(1)
subplot(311)
plot(data.time, [exc, data.values(:, ind_exc), yd]), grid on, ylabel('exc')
subplot(312)
plot(data.time, [sinarg, data.values(:, ind_sinarg)]), grid on, ylabel('sinarg (rad)')
subplot(313)
plot(data.time, [fchirp, data.values(:, ind_fchirp)]), grid on, ylabel('fchirp (Hz)')
xlabel('Time (sec)')

figure(2)
subplot(311)
plot(data.time, [exc - data.values(:, ind_exc), exc - yd]), grid on, ylabel('exc')
subplot(312)
plot(data.time, [sinarg - data.values(:, ind_sinarg)]), grid on, ylabel('sinarg (rad)')
subplot(313)
plot(data.time, [fchirp - data.values(:, ind_fchirp)]), grid on, ylabel('fchirp (Hz)')
xlabel('Time (sec)')

% frequency response estimation
Nest     = round(1.0 / Ts);
koverlap = 0.5;
Noverlap = round(koverlap * Nest);
window   = hann(Nest);

figure(3)
pwelch([exc, data.values(:, ind_exc), yd], window, Noverlap, [], 1/Ts)
