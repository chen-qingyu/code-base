F = 2000;             % Sampling frequency
T = 1 / F;            % Sampling period
L = 200;              % Length of signal
t = (0 : L - 1) * T;  % Time vector

x1 = cos(2 * pi * 100 * t);
x2 = cos(2 * pi * 200 * t);
x3 = cos(2 * pi * 500 * t);

X = [x1; x2; x3];

for i = 1 : 3
    subplot(3, 2, 2 * i - 1);
    plot(t, X(i, 1 : L));
    title(['Row ', num2str(i), ' in the Time Domain']);
end

n = 2 ^ nextpow2(L);
dim = 2;
Y = fft(X, n, dim);
P2 = abs(Y / L);
P1 = P2( : , 1 : n / 2 + 1);
P1( : , 2 : end - 1) = 2 * P1( : , 2 : end - 1);

for i = 1 : 3
    subplot(3, 2, 2 * i)
    plot(0 : (F / n) : (F / 2 - F / n), P1(i, 1 : n / 2))
    title(['Row ', num2str(i), ' in the Frequency Domain'])
end
