t = -10 : 0.01 : 10;
ya = sin(t);
plot(t, ya);

hold on;

k = -10 : 10;
yd = sin(k);
stem(k, yd);

xlabel('t / k');
ylabel('f(t) / f[k]');
title('sinusoidal signal');