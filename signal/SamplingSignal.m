t = -10 : 0.01 : 10;
ya = sinc(t / pi);
plot(t, ya);

hold on;

k = -10 : 10;
yd = sinc(k / pi);
stem(k, yd);

xlabel('t / k');
ylabel('f(t) / f[k]');
title('sampling signal');