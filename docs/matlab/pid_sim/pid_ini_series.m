clc, clear variables
addpath ../iirfilter/
%%

Ts = 50e-6;

Kp = 25.0;
Ki = Kp * (2*pi*15.0);

Tn = Kp / Ki;

fz = 20.0;
fp = 300.0;
ff = 500.0;

g_awr = 1.0;

% TODO: replace ss in case you change the behavior for the filters
Gpi = ss(tf([Kp + Ki*Ts, -Kp], [1, -1.0], Ts));
Gll1 = get_leadlag1(fz, fp, Ts);
GpidT1 = Gpi * Gll1;
Glp1 = get_lowpass1(ff, Ts);
GpidT2 = GpidT1 * Glp1;

s = tf('s');
Gpic = Kp + Ki/s;
Gll1c = (fp / fz) * (s + 2*pi*fz) / (s + 2*pi*fp);
GpidT1c = Gpic * Gll1c;
Glp1c = 2*pi*ff / (s + 2*pi*ff);
GpidT2c = GpidT1c * Glp1c;

figure(11)
bode(Gpic, GpidT1c, GpidT2c, ...
     Gpi , GpidT1 , GpidT2 , 2*pi*logspace(-3, log10(1/(2*Ts)), 1e3)), grid on

Pc = 10.0/s * ...
    (2.0*pi*fz*1.0) / (s + 2.0*pi*fz*1.0) * ...
    (2.0*pi*fp*1.0) / (s + 2.0*pi*fp*1.0);
P = c2d(Pc, Ts);

figure(22)
margin(P * GpidT2), grid on

S = feedback(1, P * GpidT2);
T = 1 - S;

z = zero(GpidT2c);
Gvc = z(1) * z(2) / ((s - z(1)) * (s - z(2)));
Gv = c2d(Gvc, Ts);

figure(33)
subplot(121)
step(T, T * Gv, 0.15), grid on
subplot(122)
bode(T, S), grid on

%%

u_max = 5.5;
u_min = -u_max;

