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
y_max_est = squar_fun(a_est, b_est, c_est, x_max_est)

figure(99)
plot(x, y), grid on, hold on
plot([x0 x1 x2], [y0 y1 y2], 'bo')
plot(x_max_est, y_max_est, 'rx'), hold off


%%

% clc, clear all
% 
% syms T s z Ts
% G = 1 / (T*s + 1)
% Gd = subs(G, s, (1 - z^-1)/Ts)
% collect(Gd, z)
% % (Ts*z) / ((T + Ts)*z - T)
% % Ts/(T + Ts) / (1 - T/(T + Ts) * z^-1)