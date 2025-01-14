a = -0.5;

t = 0 : 0.01 : 10;
ya = exp(a * t);
plot(t, ya);

hold on;

k = 0 : 10;
yd = a .^ k;
stem(k, yd);

xlabel('t / k');
ylabel('f(t) / f[k]');
title('exponential signal');