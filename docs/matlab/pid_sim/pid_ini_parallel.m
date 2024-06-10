clc, clear variables
addpath iirfilter\
%%

Ts = 50e-6;

Kp_s = 25.0;
Ki_s = Kp_s * (2*pi*15.0);

% Tn = Kp / Ki;

fz_s = 20.0;
fp_s = 300.0;
ff = 500.0;

% convert parameter from series form (Gll1 * Gpi) to parallel form
Kp = (Ki_s*fp_s - Ki_s*fz_s + 2*pi*Kp_s*fp_s*fz_s)/(2*fp_s*fz_s*pi);
Ki = Ki_s;
Kd = -(Ki_s*fp_s - Ki_s*fz_s - 2*pi*Kp_s*fp_s^2 + 2*pi*Kp_s*fp_s*fz_s)/(4*fp_s^2*fz_s*pi^2);
fp = fp_s;

g_awr = 1.6;

z = tf('z', Ts);
Gd = (1 - z^-1) / Ts * get_lowpass1(fp, Ts);
GpidT1 = Kp + Ki * Ts / (1 - z^-1) + Kd * Gd;
Glp1 = get_lowpass1(ff, Ts);
GpidT2 = GpidT1 * Glp1;

s = tf('s');
Gdc = s * (2*pi*fp) / (s + 2*pi*fp);
GpidT1c = Kp + Ki/s + Kd * Gdc;
Glp1c = (2*pi*ff) / (s + 2*pi*ff);
GpidT2c = GpidT1c * Glp1c;

figure(1)
bode(GpidT1c, GpidT2c, ...
     GpidT1 , GpidT2 , 2*pi*logspace(-3, log10(1/(2*Ts)), 1e3)), grid on

Pc = 10.0/s * ...
    (2.0*pi*fz_s*1.0) / (s + 2.0*pi*fz_s*1.0) * ...
    (2.0*pi*fp_s*1.0) / (s + 2.0*pi*fp_s*1.0);
P = c2d(Pc, Ts);

figure(2)
margin(P * GpidT2), grid on

S = feedback(1, P * GpidT2);
T = 1 - S;

z = zero(GpidT2c);
Gvc = z(1) * z(2) / ((s - z(1)) * (s - z(2)));
Gv = c2d(Gvc, Ts);

figure(3)
subplot(121)
step(T, T * Gv, 0.15), grid on
subplot(122)
bode(T, S), grid on

%%

u_max = 5.5;
u_min = -u_max;


















