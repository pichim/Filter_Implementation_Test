clc, clear variables
addpath iirfilter\
%%

data_raw = readmatrix("datafile.txt");

data.time = data_raw(:,1);
data.values = data_raw(:,2:end);           

Ts = mean(diff(data.time))

ind_exc    = [ 1,  4];
ind_freq   = [ 2,  5];
ind_sinarg = [ 3,  6];
ind_notch  = [ 7,  8];
ind_lp2    = [ 9, 10];
ind_lp1    = [11, 12];
ind_ll1    = [13, 14];
ind_pc1    = [15, 16];
ind_ll2    = [17, 18];

figure(1)
subplot(311)
plot(data.time, data.values(:, ind_exc)), grid on, ylabel('exc')
subplot(312)
plot(data.time, data.values(:, ind_sinarg)), grid on, ylabel('sinarg (rad)')
subplot(313)
plot(data.time, data.values(:, ind_freq)), grid on, ylabel('fchirp (Hz)')


% frequency response estimation
Nest     = round(1.0 / Ts);
koverlap = 0.9;
Noverlap = round(koverlap * Nest);
window   = hann(Nest);

inp = data.values(:,ind_exc(1));
out = data.values(:,ind_notch(1));
[G, C] = estimate_frequency_response(inp, out, window, Noverlap, Nest, Ts);

opt = bodeoptions('cstprefs');
opt.MagUnits = 'abs';
opt.MagScale = 'linear';


s = tf('s');


%%

% #define NOTCH_F_CUT 1.0e3f
% #define NOTCH_D 0.1f
fn = 1.0e3;
Dn = 0.1;

figure(2)
plot(data.time, data.values(:, ind_notch)), grid on, ylabel('notch')

inp = data.values(:,ind_exc(1));
out = data.values(:,ind_notch(1));
[G, C] = estimate_frequency_response(inp, out, window, Noverlap, Nest, Ts);

wn = 2*pi*fn;
Gc = (s^2 + wn^2) / (s^2 + 2*Dn*wn*s + wn^2);

figure(3)
subplot(211)
bode(G, get_notch(fn, Dn, Ts), Gc, 2*pi*G.Frequency(G.Frequency < 1/2/Ts)), grid on
subplot(212)
bodemag(C, 2*pi*C.Frequency(C.Frequency < 1/2/Ts), opt), grid on
set(gca, 'YScale', 'linear')


%%

% #define LOWPASS2_F_CUT 60.0f
% #define LOWPASS2_D (sqrtf(3.0f) / 2.0f)
flp2 = 60.0;
Dlp2 = sqrt(3.0) / 2.0;

figure(4)
plot(data.time, data.values(:, ind_lp2)), grid on, ylabel('notch')

inp = data.values(:,ind_exc(1));
out = data.values(:,ind_lp2(1));
[G, C] = estimate_frequency_response(inp, out, window, Noverlap, Nest, Ts);

wlp2 = 2*pi*flp2;
Gc = wlp2^2 / (s^2 + 2*Dlp2*wlp2*s + wlp2^2);

figure(5)
subplot(211)
bode(G, get_lowpass2(flp2, Dlp2, Ts), Gc, 2*pi*G.Frequency(G.Frequency < 1/2/Ts)), grid on
subplot(212)
bodemag(C, 2*pi*C.Frequency(C.Frequency < 1/2/Ts), opt), grid on
set(gca, 'YScale', 'linear')


%%

% #define LOWPASS1_F_CUT 60.0f
flp1 = 60.0;

figure(6)
plot(data.time, data.values(:, ind_lp1)), grid on, ylabel('notch')

inp = data.values(:,ind_exc(1));
out = data.values(:,ind_lp1(1));
[G, C] = estimate_frequency_response(inp, out, window, Noverlap, Nest, Ts);

wlp1 = 2*pi*flp1;
Gc = wlp1 / (s + wlp1);

figure(7)
subplot(211)
bode(G, get_lowpass1(flp2, Ts), Gc, 2*pi*G.Frequency(G.Frequency < 1/2/Ts)), grid on
subplot(212)
bodemag(C, 2*pi*C.Frequency(C.Frequency < 1/2/Ts), opt), grid on
set(gca, 'YScale', 'linear')


%%

% #define LEADLAG1_F_ZERO 60.0f
% #define LEADLAG1_F_POLE 200.0f
fz1 = 60.0;
fp1 = 200.0;

figure(8)
plot(data.time, data.values(:, ind_ll1)), grid on, ylabel('notch')

inp = data.values(:,ind_exc(1));
out = data.values(:,ind_ll1(1));
[G, C] = estimate_frequency_response(inp, out, window, Noverlap, Nest, Ts);

wz1 = 2*pi*fz1;
wp1 = 2*pi*fp1;
Gc = (wp1 / wz1) * (s + wz1) / (s + wp1);

figure(9)
subplot(211)
bode(G, get_leadlag1(fz1, fp1, Ts), Gc, 2*pi*G.Frequency(G.Frequency < 1/2/Ts)), grid on
subplot(212)
bodemag(C, 2*pi*C.Frequency(C.Frequency < 1/2/Ts), opt), grid on
set(gca, 'YScale', 'linear')


%%

% #define PHASECOMP1_F_CENTER 80.0f
% #define PHASECOMP1_PHASE_LIFT -45.0f
fc1 = 80.0;
phal1 = -45.0;

figure(10)
plot(data.time, data.values(:, ind_pc1)), grid on, ylabel('notch')

inp = data.values(:,ind_exc(1));
out = data.values(:,ind_pc1(1));
[G, C] = estimate_frequency_response(inp, out, window, Noverlap, Nest, Ts);

wc1 = 2*pi*fc1;
sinphi = sin(phal1*pi/180);
a = (1 - sinphi) / (1 + sinphi);
Gc = (1/sqrt(a)*s + wc1) / (sqrt(a)*s + wc1);

figure(11)
subplot(211)
bode(G, get_phase_comp(fc1, phal1, Ts), Gc, 2*pi*G.Frequency(G.Frequency < 1/2/Ts)), grid on
subplot(212)
bodemag(C, 2*pi*C.Frequency(C.Frequency < 1/2/Ts), opt), grid on
set(gca, 'YScale', 'linear')


%%

% #define LEADLAG2_F_ZERO 20.0f
% #define LEADLAG2_D_ZERO 0.08f
% #define LEADLAG2_F_POLE 1000.0f
% #define LEADLAG2_D_POLE 0.12f
fzll2 = 20.0;
Dzll2 = 0.08;
fpll2 = 1000.0;
Dpll2 = 0.12;

figure(12)
plot(data.time, data.values(:, ind_ll2)), grid on, ylabel('notch')

inp = data.values(:,ind_exc(1));
out = data.values(:,ind_ll2(1));
[G, C] = estimate_frequency_response(inp, out, window, Noverlap, Nest, Ts);

wzll2 = 2*pi*fzll2;
wpll2 = 2*pi*fpll2;
Gc = (wpll2^2 / wzll2^2) * (s^2 + 2*Dzll2*wzll2*s + wzll2^2) / (s^2 + 2*Dpll2*wpll2*s + wpll2^2);

figure(13)
subplot(211)
bode(G, get_leadlag2(fzll2, Dzll2, fpll2, Dpll2, Ts), Gc, 2*pi*G.Frequency(G.Frequency < 1/2/Ts)), grid on
subplot(212)
bodemag(C, 2*pi*C.Frequency(C.Frequency < 1/2/Ts), opt), grid on
set(gca, 'YScale', 'linear')

