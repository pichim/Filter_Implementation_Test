clc, clear variables
addpath iirfilter\
%%

% see: https://webaudio.github.io/Audio-EQ-Cookbook/audio-eq-cookbook.html

% second order lowpass

% omega = 2.0 * pi * fcut * Ts;
% sn = sin(omega);
% cs = cos(omega);
% k = 1.0 / (1.0 + D * sn);
% b0 = (1.0 - cs) / 2.0 * k;
% b1 = 2.0 * b0;
% b2 = b0;
% a1 = -2.0 * cs * k;
% a2 = (1.0 - D * sn) * k;

% notch

% omega = 2.0 * pi * fcut * Ts;
% sn = sin(omega);
% cs = cos(omega);
% b0 = 1.0 / (1.0 + D * sn);
% b1 = -2 * cs * b0;
% b2 = b0;
% a1 = b1;
% a2 = (1.0 - D * sn) * b0;

% leadlag2

% omegaZero = 2.0 * pi * fZero * Ts;
% snZero = sin(omegaZero);
% csZero = cos(omegaZero);
% omegaPole = 2.0 * pi * fPole * Ts;
% snPole = sin(omegaPole);
% csPole = cos(omegaPole);
% k0 = 1.0 / (1.0 + DPole * snPole);
% k1 = csPole - 1.0;
% k2 = k0 / (csZero - 1.0);
% b0 = (1.0 + DZero * snZero) * k1 * k2
% b1 = -2.0 * csZero * k1 * k2
% b2 = (1.0 - DZero * snZero) * k1 * k2
% a1 = -2.0 * csPole * k0
% a2 = (1.0 - DPole * snPole) * k0

%%

% Ts = 50e-6;
% 
% % fzll2 = 20.0;
% % Dzll2 = 0.08;
% % fpll2 = 3800.0;
% % Dpll2 = 0.12;
% 
% fpll2 = 20.0;
% Dpll2 = 0.08;
% fzll2 = 3800.0;
% Dzll2 = 0.12;
% 
% s = tf('s');
% 
% fZero = fzll2;
% DZero = Dzll2;
% fPole = fpll2;
% DPole = Dpll2;
% 
% % prewarp is done implicitly
% omegaZero = 2.0 * pi * fZero * Ts;
% snZero = sin(omegaZero);
% csZero = cos(omegaZero);
% omegaPole = 2.0 * pi * fPole * Ts;
% snPole = sin(omegaPole);
% csPole = cos(omegaPole);
% k0 = 1.0 / (1.0 + DPole*snPole);
% k1 = csPole - 1.0;
% k2 = k0 / (csZero - 1.0);
% 
% b0 = (1.0 + DZero * snZero) * k1 * k2
% b1 = -2.0 * csZero * k1 * k2
% b2 = (1.0 - DZero * snZero) * k1 * k2
% a1 = -2.0 * csPole * k0
% a2 = (1.0 - DPole*snPole) * k0
% 
% 
% Gd1 = tf([b0 b1 b2], [1 a1 a2], Ts)
% 
% wzll2 = 2*pi*fzll2;
% wpll2 = 2*pi*fpll2;
% Gc = (wpll2^2 / wzll2^2) * (s^2 + 2*Dzll2*wzll2*s + wzll2^2) / (s^2 + 2*Dpll2*wpll2*s + wpll2^2);
% 
% Gd2 = minreal( tf( get_leadlag2(fzll2, Dzll2, fpll2, Dpll2, Ts) ) )
% 
% figure(1)
% bode(Gc, Gd1, Gd2), grid on


%%

% Ts = 50e-6;
% 
% fzll2 = 20.0;
% Dzll2 = 0.08;
% fpll2 = 1000.0;
% Dpll2 = 0.12;
% 
% s = tf('s');
% 
% 
% fcut = fzll2;
% D = Dzll2;
% 
% % prewarp is done implicitly
% omega = 2.0 * pi * fcut * Ts;
% sn = sin(omega);
% cs = cos(omega);
% k = 1.0 / (1.0 + D*sn);
% b0 = (1.0 - cs) / 2.0 * k;
% b1 = 2.0 * b0;
% b2 = b0;
% a1 = -2.0 * cs * k;
% a2 = (1.0 - D*sn) * k;
% 
% GZero = tf([b0 b1 b2], [1 a1 a2], Ts);
% 
% 
% 
% fcut = fpll2;
% D = Dpll2;
% 
% % prewarp is done implicitly
% omega = 2.0 * pi * fcut * Ts;
% sn = sin(omega);
% cs = cos(omega);
% k = 1.0 / (1.0 + D*sn);
% b0 = (1.0 - cs) / 2.0 * k;
% b1 = 2.0 * b0;
% b2 = b0;
% a1 = -2.0 * cs * k;
% a2 = (1.0 - D*sn) * k;
% 
% GPole = tf([b0 b1 b2], [1 a1 a2], Ts);
% 
% 
% wzll2 = 2*pi*fzll2;
% wpll2 = 2*pi*fpll2;
% Gc = (wpll2^2 / wzll2^2) * (s^2 + 2*Dzll2*wzll2*s + wzll2^2) / (s^2 + 2*Dpll2*wpll2*s + wpll2^2);
% 
% Gd1 = tf( minreal(balreal(GPole/ GZero)) )
% 
% Gd2 = minreal( tf( get_leadlag2(fzll2, Dzll2, fpll2, Dpll2, Ts) ) )
% 
% figure(1)
% bode(Gc, Gd1, Gd2), grid on


%% notch

% Ts = 50e-6;
% 
% fn = 1.0e3;
% Dn = 0.1;
% 
% s = tf('s');
% 
% 
% fcut = fn;
% D = Dn;
% 
% % prewarp is done implicitly
% omega = 2.0 * pi * fcut * Ts;
% sn = sin(omega);
% cs = cos(omega);
% b0 = 1.0 / (1.0 + D*sn);
% b1 = -2 * cs * b0;
% b2 = b0;
% a1 = b1;
% a2 = (1.0 - D*sn) * b0;
% 
% Gd1 = tf([b0 b1 b2], [1 a1 a2], Ts)
% 
% wn = 2*pi*fn;
% Gc = (s^2 + wn^2) / (s^2 + 2*Dn*wn*s + wn^2);
% 
% Gd2 = minreal( tf( get_notch(fn, Dn, Ts) ) )
% 
% figure(1)
% bode(Gc, Gd1, Gd2), grid on

%%

% first order lowpass

clc, clear all

syms sn cs z

% 1 / (s + 1)
H = (1 + 2*z^-1 + z^-2) * (1 - cs) / ...
    ((1 + 2*z^-1 + z^-2) * (1 - cs) + (1 - z^-2)*sn)

H = simplify(H)

H = collect(H, z)
pretty(H)


%%
clc, clear all

Ts = 50e-6;
fcut = 100;
omega = 2.0 * pi * fcut * Ts;
sn = sin(omega);
cs = cos(omega);

b0 = 1 - cs;
b1 = 1 - cs;
a0 = sn - cs + 1;
a1 = 1 - sn - cs;

figure(1)
bode(tf(1, [1/(2*pi*fcut) 1]), tf([b0, b1], [a0, a1], Ts))


%%

% first order lowpass

clc, clear all

syms snZero csZero DZero snPole csPole DPole z

Hzero = (1 + 2*z^-1 + z^-2) * (1 - csZero) / ...
    ((1 + 2*z^-1 + z^-2) * (1 - csZero) + (1 - z^-2)*snZero)

Hpole = (1 + 2*z^-1 + z^-2) * (1 - csPole) / ...
    ((1 + 2*z^-1 + z^-2) * (1 - csPole) + (1 - z^-2)*snPole)

H = simplify(Hpole / Hzero)

H = collect(H, z)
pretty(H)


b0 = csPole + csZero - snZero - csPole*csZero + csPole*snZero - 1;
b1 = csPole + csZero + snZero - csPole*csZero - csPole*snZero - 1;
a0 = csPole + csZero - snPole - csPole*csZero + csZero*snPole - 1;
a1 = csPole + csZero + snPole - csPole*csZero - csZero*snPole - 1;

b0 = simplify(b0 / a0)

b1 = simplify(b1 / a0)

a1 = simplify(a1 / a0)

k0 = 1 / (snPole - csPole + 1);
k1 = k0 / (csZero - 1);
b0_ = -(1.0 - csPole) * (snZero - csZero + 1) * k1;
b1_ =  (1.0 - csPole) * (csZero + snZero - 1) * k1;
a1_ =  (1.0 - csPole - snPole) * k0;

simplify(b0 - b0_)
simplify(b1 - b1_)
simplify(a1 - a1_)

%%

% clc, clear all
% 
% syms Ts wZero wPole s z
% 
% H = (wPole / wZero) * (s + wZero) / (s + wPole)
% 
% H = subs(H, s, 2/Ts*(z-1) / (z+1))
% 
% H = collect(H, z)
% 
% b0 = (2*wPole + Ts*wPole*wZero);
% b1 = Ts*wPole*wZero - 2*wPole;
% a0 = (2*wZero + Ts*wPole*wZero);
% a1 = Ts*wPole*wZero - 2*wZero;
% 
% b0 = simplify(b0 / a0)
% 
% b1 = simplify(b1 / a0)
% 
% a1 = simplify(a1 / a0)
% 
% b0 = (wPole*(Ts*wZero + 2)) / (wZero*(Ts*wPole + 2));
% b1 = (wPole*(Ts*wZero - 2)) / (wZero*(Ts*wPole + 2));
% a1 = (Ts*wPole - 2) / (Ts*wPole + 2);
% 
% k = 1 / (Ts*wPole + 2)
% b0_ = (wPole*(Ts*wZero + 2)) / (wZero) * k;
% b1_ = (wPole*(Ts*wZero - 2)) / (wZero) * k;
% a1_ = (Ts*wPole - 2) * k;
% 
% simplify(b0 - b0_)
% simplify(b1 - b1_)
% simplify(a1 - a1_)


%%

% % leadlag2
% 
% clc, clear all
% 
% syms snZero csZero DZero snPole csPole DPole z
% 
% % 1 / (s^2 + s/Q + 1)
% HZero = (1 + 2*z^-1 + z^-2) * (1 - csZero) / ...
%     (2*(1 - 2*csZero*z^-1 + z^-2) + (1-z^-2)*snZero / (1 / (2*DZero)))
% 
% HPole = (1 + 2*z^-1 + z^-2) * (1 - csPole) / ...
%     (2*(1 - 2*csPole*z^-1 + z^-2) + (1-z^-2)*snPole / (1 / (2*DPole)))
% 
% 
% H = simplify(HPole / HZero)
% 
% H = collect(H, z)
% pretty(H)
% 
% b0 = csPole - DZero*snZero + DZero*csPole*snZero - 1
% b1 = 2*csZero - 2*csPole*csZero
% b2 = csPole + DZero*snZero - DZero*csPole*snZero - 1
% a0 = csZero - DPole*snPole + DPole*csZero*snPole - 1
% a1 = 2*csPole - 2*csPole*csZero
% a2 = csZero + DPole*snPole - DPole*csZero*snPole - 1
% 
% b0 = simplify(b0 / a0)
% 
% b1 = simplify(b1 / a0)
% 
% b2 = simplify(b2 / a0)
% 
% a1 = simplify(a1 / a0)
% 
% a2 = simplify(a2 / a0)
% 
% k0 = 1 / (1 + DPole*snPole);
% k1 = csPole - 1;
% k2 = k0 / (csZero - 1);
% 
% b0_ = ((DZero*snZero + 1)*k1) * k2
% b1_ = -(2*csZero*k1) * k2
% b2_ = -((DZero*snZero - 1)*k1) * k2
% a1_ = -(2*csPole) * k0
% a2_ = -(DPole*snPole - 1) * k0
% 
% simplify(b0 - b0_)
% simplify(b1 - b1_)
% simplify(b2 - b2_)
% simplify(a1 - a1_)
% simplify(a2 - a2_)


%%

% notch with tustin and prewarp

% clc, clear all
% 
% syms sn cs D z
% 
% % (s^2 + 1) / (s^2 + s/Q + 1)
% H = 2*(1 - 2*cs*z^-1 + z^-2) / ...
%     (2*(1 - 2*cs*z^-1 + z^-2) + (1-z^-2)*sn / (1 / (2*D)))
% 
% H = simplify(H)
% 
% H = collect(H, z)
% pretty(H)
% 
% b0 = 1
% b1 = - 2*cs
% b2 = b0
% a0 = (sn*D + 1)
% a1 = b1
% a2 = - sn*D + 1
% 
% b1 = simplify(b1 / a0)
% 
% a2 = simplify(a2 / a0)
% 
% b1 = -(2*cs)/(D*sn + 1)
% a2 = -(D*sn - 1)/(D*sn + 1)


%%

% second order lowpass with tustin and prewarp

% clc, clear all
% 
% syms sn cs D z
% 
% % 1 / (s^2 + s/Q + 1)
% H = (1 + 2*z^-1 + z^-2) * (1 - cs) / ...
%     (2*(1 - 2*cs*z^-1 + z^-2) + (1-z^-2)*sn / (1 / (2*D)))
% 
% H = simplify(H)
% 
% H = collect(H, z)
% pretty(H)
% 
% b0 = (1 - cs)
% b1 = 2 * b0
% b2 = b0
% a0 = 2*(1 + sn*D)
% a1 = -4*cs
% a2 = 2*(1 - sn*D)
% 
% b0 = simplify(b0 / a0)
% 
% a1 = simplify(a1 / a0)
% 
% a2 = simplify(a2 / a0)
% 
% b0 = -(cs - 1)/ 2 / (D*sn + 1)
% a1 = -(2*cs) / (D*sn + 1)
% a2 = -(D*sn - 1) / (D*sn + 1)

