clc, clear variables
addpath iirfilter\
addpath iirfilter\c_implementation\
%%

Ts = 1e-4;

% chirp parameters
f_0 =   1.0;
f_1 = 200.0;
t_1 =  10.0;

% damping notch filter
D = 0.1;

% fading frequencies
f_fade_min = 100; % w = 0
f_fade_max = 150; % w = 1

%% bode diagram of fading notch

% G = (1-w) + w*Gn = 1 - w + w*Gn = 1 + w *(Gn - 1)

f_chirp = logspace(log10(f_fade_min), log10(f_fade_max), 15);
freq = logspace(log10(f_fade_min) - 0.1, log10(f_fade_max) + 0.1, 1e4);

figure(1)
for i = 1:length(f_chirp)
    [B, A] = get_notch_polynomials(f_chirp(i), D, Ts);
    if (f_chirp(i) < f_fade_min)
        G = tf(1, 1, Ts);
    elseif (f_chirp(i) > f_fade_max)
        G = tf(B, A, Ts);
    else
        w_i = (f_chirp(i) - f_fade_min) / (f_fade_max - f_fade_min);
        G = (1 - w_i) + w_i * tf(B, A, Ts);
    end
    bode(G, 2*pi*freq), grid on, hold on
end
title('Fading Notch')
hold off


%% simulating a fading notch filter applied to the chirp signal

time = (0:Ts:t_1).';
N = length(time);

input = chirp(time, f_0, time(end), f_1, 'linear', 90);
f_chirp = (f_1 - f_0) / t_1 * time + f_0;

% create iir filter
notch = get_iir_filter();
notch = notch_init(notch, 0.0, D, Ts);

% create fading_notch_filter
fading_notch = get_fading_notch_filter();
fading_notch = fading_notch_init(fading_notch, 0.0, D, f_fade_min, f_fade_max, Ts);


output = zeros(N,1);
weight = zeros(N,1);
output_fade = zeros(N,1);

for i = 1:N

    % apply iir filter
    notch = notch_update(notch, f_chirp(i), D, Ts);
    [notch, y_i] = iir_filter_apply(notch, input(i));
    output(i) = y_i;

    % calculate weight
    if (f_chirp(i) < f_fade_min)
        weight(i) = 0.0;
    elseif (f_chirp(i) > f_fade_max)
        weight(i) = 1.0;
    else
        w_i = (f_chirp(i) - f_fade_min) / (f_fade_max - f_fade_min);
        weight(i) = w_i;
    end

    % apply fading notch
    [fading_notch, y_fade_i] = fading_notch_filter_apply(fading_notch, f_chirp(i), input(i));
    output_fade(i) = y_fade_i;
end


%%

figure(2)
subplot(211)
plot(time, input), grid on
ylabel('Chirp Signal')
subplot(212)
plot(time, f_chirp), grid on
ylabel('Chirp Frequency'), xlabel('Time')

figure(3)
subplot(311)
plot(time, input), grid on
ylabel('Chirp Signal')
subplot(312)
plot(time, output), grid on
ylabel('Notch Filtered Signal')
subplot(313)
plot(time, output_fade), grid on
ylabel('Faded Notch Filtered Signal'), xlabel('Time')

figure(4)
subplot(211)
plot(f_chirp, output_fade), grid on
ylabel('Faded Notch Filtered Signal')
subplot(212)
plot(f_chirp, weight), grid on
ylabel('Weighting'), xlabel('Frequency')

