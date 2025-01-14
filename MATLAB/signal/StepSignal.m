t = -10 : 0.01 : 10;
ya = stepfun(t, 0);
plot(t, ya);

hold on;

k = -10 : 10;
yd = stepfun(k, 0);
stem(k, yd);

xlabel('t / k');
ylabel('f(t) / f[k]');
title('unit step signal');