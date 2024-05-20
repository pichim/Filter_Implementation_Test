clc, clear variables
addpath iirfilter\
%%

data_raw = readmatrix("datafile.txt");

data.time = data_raw(:,1);
data.values = data_raw(:,2:end);           

Ts = mean(diff(data.time))

ind.exc    = [ 1,  4];
ind.freq   = [ 2,  5];
ind.sinarg = [ 3,  6];
ind.notch  = [ 7,  8];
ind.lp2    = [ 9, 10];
ind.lp1    = [11, 12];
ind.ll1    = [13, 14];
ind.pc1    = [15, 16];

figure(1)
subplot(311)
plot(data.time, data.values(:, ind.exc)), grid on, ylabel('exc')
subplot(312)
plot(data.time, data.values(:, ind.sinarg)), grid on, ylabel('sinarg (rad)')
subplot(313)
plot(data.time, data.values(:, ind.freq)), grid on, ylabel('fchirp (Hz)')


% frequency response estimation
Nest     = round(1.0 / Ts);
koverlap = 0.9;
Noverlap = round(koverlap * Nest);
window   = hann(Nest);

inp = data.values(:,ind.exc(1));
out = data.values(:,ind.notch(1));
[G, C] = estimate_frequency_response(inp, out, window, Noverlap, Nest, Ts);

opt = bodeoptions('cstprefs');
opt.MagUnits = 'abs';
opt.MagScale = 'linear';


%%

% #define NOTCH_F_CUT 1.0e3f
% #define NOTCH_D 0.1f
fn = 1.0e3;
Dn = 0.1;

figure(2)
plot(data.time, data.values(:, ind.notch)), grid on, ylabel('notch')

inp = data.values(:,ind.exc(1));
out = data.values(:,ind.notch(1));
[G, C] = estimate_frequency_response(inp, out, window, Noverlap, Nest, Ts);

figure(3)
subplot(211)
bode(G, get_notch(fn, Dn, Ts), 2*pi*G.Frequency(G.Frequency < 1/2/Ts)), grid on
subplot(212)
bodemag(C, 2*pi*C.Frequency(C.Frequency < 1/2/Ts), opt), grid on
set(gca, 'YScale', 'linear')


%%

% #define LOWPASS2_F_CUT 60.0f
% #define LOWPASS2_D (sqrtf(3.0f) / 2.0f)
flp2 = 60.0;
Dlp2 = sqrt(3.0) / 2.0;

figure(4)
plot(data.time, data.values(:, ind.lp2)), grid on, ylabel('notch')

inp = data.values(:,ind.exc(1));
out = data.values(:,ind.lp2(1));
[G, C] = estimate_frequency_response(inp, out, window, Noverlap, Nest, Ts);

figure(5)
subplot(211)
bode(G, get_lowpass2(flp2, Dlp2, Ts), 2*pi*G.Frequency(G.Frequency < 1/2/Ts)), grid on
subplot(212)
bodemag(C, 2*pi*C.Frequency(C.Frequency < 1/2/Ts), opt), grid on
set(gca, 'YScale', 'linear')


%%

% #define LOWPASS1_F_CUT 60.0f
flp1 = 60.0;

figure(6)
plot(data.time, data.values(:, ind.lp1)), grid on, ylabel('notch')

inp = data.values(:,ind.exc(1));
out = data.values(:,ind.lp1(1));
[G, C] = estimate_frequency_response(inp, out, window, Noverlap, Nest, Ts);

figure(7)
subplot(211)
bode(G, get_lowpass1(flp2, Ts), 2*pi*G.Frequency(G.Frequency < 1/2/Ts)), grid on
subplot(212)
bodemag(C, 2*pi*C.Frequency(C.Frequency < 1/2/Ts), opt), grid on
set(gca, 'YScale', 'linear')


%%

% #define LEADLAG1_F_ZERO 60.0f
% #define LEADLAG1_F_POLE 200.0f
fz1 = 60.0;
fp1 = 200.0;

figure(8)
plot(data.time, data.values(:, ind.ll1)), grid on, ylabel('notch')

inp = data.values(:,ind.exc(1));
out = data.values(:,ind.ll1(1));
[G, C] = estimate_frequency_response(inp, out, window, Noverlap, Nest, Ts);

figure(9)
subplot(211)
bode(G, get_leadlag1(fz1, fp1, Ts), 2*pi*G.Frequency(G.Frequency < 1/2/Ts)), grid on
subplot(212)
bodemag(C, 2*pi*C.Frequency(C.Frequency < 1/2/Ts), opt), grid on
set(gca, 'YScale', 'linear')


%%

% #define PHASECOMP1_F_CENTER 80.0f
% #define PHASECOMP1_PHASE_LIFT -45.0f
fc1 = 80.0;
phal1 = -45.0;

figure(10)
plot(data.time, data.values(:, ind.pc1)), grid on, ylabel('notch')

inp = data.values(:,ind.exc(1));
out = data.values(:,ind.pc1(1));
[G, C] = estimate_frequency_response(inp, out, window, Noverlap, Nest, Ts);

figure(11)
subplot(211)
bode(G, get_phase_comp(fc1, phal1, Ts), 2*pi*G.Frequency(G.Frequency < 1/2/Ts)), grid on
subplot(212)
bodemag(C, 2*pi*C.Frequency(C.Frequency < 1/2/Ts), opt), grid on
set(gca, 'YScale', 'linear')

