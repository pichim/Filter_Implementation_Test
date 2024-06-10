clc, clear variables
%%

syms Kp_p Ki_p Kd_p fp_p
syms Kp_s Ki_s fz_s fp_s
syms s

Gdc_p = s * (2*pi*fp_p) / (s + 2*pi*fp_p);
GpidT1_p = collect(Kp_p + Ki_p/s + Kd_p * Gdc_p, s)
% ((Kp_p + 2*Kd_p*fp_p*pi)*s^2 + (Ki_p + 2*Kp_p*fp_p*pi)*s + 2*Ki_p*fp_p*pi)/(s^2 + 2*fp_p*pi*s)

Gpi_s = Kp_s + Ki_s/s;
Gll1_s = (fp_s / fz_s) * (s + 2*pi*fz_s) / (s + 2*pi*fp_s);
GpidT1c = collect(Gpi_s * Gll1_s, s)
% (Kp_s*fp_s*s^2 + (Ki_s*fp_s + 2*Kp_s*fp_s*fz_s*pi)*s + 2*Ki_s*fp_s*fz_s*pi)/(fz_s*s^2 + 2*fp_s*fz_s*pi*s)

eqns = [(Kp_p + 2*Kd_p*fp_p*pi)  -  Kp_s*fp_s/fz_s == 0, ...
    (Ki_p + 2*Kp_p*fp_p*pi)  -  (Ki_s*fp_s + 2*Kp_s*fp_s*fz_s*pi)/fz_s == 0, ...
    2*Ki_p*fp_p*pi  -  2*Ki_s*fp_s*fz_s*pi/fz_s == 0, ...
    2*fp_p*pi  -  2*fp_s*fz_s*pi/fz_s == 0]

vars = [Kp_s Ki_s fz_s fp_s]
sol = solve(eqns, vars);
ind = 1;
sol.Kp_s(ind) % (Ki_p - 2*(Ki_p^2/4 - Ki_p*Kp_p*fp_p*pi - 4*Kd_p*Ki_p*fp_p^2*pi^2 + Kp_p^2*fp_p^2*pi^2)^(1/2) + 2*pi*Kp_p*fp_p)/(4*fp_p*pi)
sol.Ki_s(ind) % Ki_p
sol.fz_s(ind) % (Ki_p - 2*(Ki_p^2/4 - Ki_p*Kp_p*fp_p*pi - 4*Kd_p*Ki_p*fp_p^2*pi^2 + Kp_p^2*fp_p^2*pi^2)^(1/2) + 2*pi*Kp_p*fp_p)/(4*pi*(Kp_p + 2*pi*Kd_p*fp_p))
sol.fp_s(ind) % fp_p
ind = 2;
sol.Kp_s(ind) % (Ki_p + 2*(Ki_p^2/4 - Ki_p*Kp_p*fp_p*pi - 4*Kd_p*Ki_p*fp_p^2*pi^2 + Kp_p^2*fp_p^2*pi^2)^(1/2) + 2*pi*Kp_p*fp_p)/(4*fp_p*pi)
sol.Ki_s(ind) % Ki_p
sol.fz_s(ind) % (Ki_p + 2*(Ki_p^2/4 - Ki_p*Kp_p*fp_p*pi - 4*Kd_p*Ki_p*fp_p^2*pi^2 + Kp_p^2*fp_p^2*pi^2)^(1/2) + 2*pi*Kp_p*fp_p)/(4*pi*(Kp_p + 2*pi*Kd_p*fp_p))
sol.fp_s(ind) % fp_p

vars = [Kp_p Ki_p Kd_p fp_p]
sol = solve(eqns, vars);
ind = 1;
sol.Kp_p(ind) % (Ki_s*fp_s - Ki_s*fz_s + 2*pi*Kp_s*fp_s*fz_s)/(2*fp_s*fz_s*pi)
sol.Ki_p(ind) % Ki_s
sol.Kd_p(ind) % -(Ki_s*fp_s - Ki_s*fz_s - 2*pi*Kp_s*fp_s^2 + 2*pi*Kp_s*fp_s*fz_s)/(4*fp_s^2*fz_s*pi^2)
sol.fp_p(ind) % fp_s

