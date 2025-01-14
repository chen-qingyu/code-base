F = 1000;             % Sampling frequency
T = 1 / F;            % Sampling period
L = 1500;             % Length of signal
t = (0 : L - 1) * T;  % Time vector

% signal
S = cos(2 * pi * 120 * t);
% noise
X = S + randn(size(t));

subplot(2, 1, 1);
plot(t, X);
title('Signal in Time Domain');
xlabel('t / s');
ylabel('X(t)');

Y = fft(X);
P2 = abs(Y / L);
P1 = P2(1 : L / 2 + 1);
P1(2 : end - 1) = 2 * P1(2 : end - 1);

f = F * (0 : (L / 2)) / L;
subplot(2, 1, 2);
plot(f, P1);
title('Signal in Frequency Domain');
xlabel('f / Hz');
ylabel('|P1(f)|');
